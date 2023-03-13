/*
project :Account账户类实现文件cpp
*/
#include "account.h"
#include <iostream>
#include <cmath>
#include <utility>
using namespace std;
using namespace std::rel_ops;
//AccountRecord类的实现：参数日期Date,账户Account类，金额，余额，描述信息
AccountRecord::AccountRecord(const Date& date, const Account* account, double amount, double balance, const std::string& desc)
	:date(date), account(account), amount(amount), balance(balance), desc(desc)
{

}
// 展现出账户记录类的账户时间，Id，存款金额，余额（算上信用卡)，描述信息
void AccountRecord::show() const
{
	//date.show();
	cout <<date<< "\t#" << account->getId() << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}




//存款总金额全局变量(所有账户）
double Account::total = 0;
// Account类中的账户记录
RecordMap Account::recordMap;
//账户记录查询实现，参数:开始Date,结束Date
void Account::query(const Date& begin, const Date& end)
{
	//从开始到结尾遍历输出
	if (begin <= end)
	{
		//lower_bound返回指向首个不小于给定键的元素的迭代器
		RecordMap::iterator iter1 = recordMap.lower_bound(begin);
		//upper_bound返回指向首个大于给定键的元素的迭代器
		RecordMap::iterator iter2 = recordMap.upper_bound(end);
		for (RecordMap::iterator iter = iter1; iter != iter2; ++iter)
		{
			iter->second.show();
		}
	}
}




//Account类函数成员的实现
Account::Account(const Date& date, const string& id)
	:id(id), balance(0)
{
	date.show();
	cout << date<<"\t#" << id << " created" << endl;
}
void Account::record(const Date& date, double amount, const string& desc)
{

	amount = floor(amount * 100 + 0.5) / 100;  //保留小数点后两位，
	balance += amount;
	total += amount;
	date.show();
	cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}
void Account::show(ostream &out) const
{
	cout << "#" << id << "\tBalance:" << balance;
}
//void Account::error(const string& msg) const
//{
//	cout << "Erroe(#" << id << "):" << msg << endl;
//}

//SavingsAccount类的实现
SavingsAccount::SavingsAccount(const Date& date, const string& id, double rate)  //时间，账户，利率
	:Account(date, id), rate(rate), acc(date, 0)
{

}

void SavingsAccount::deposit(const Date& date, double amount,const string &desc)
{
	record(date, amount,desc); //记录一笔账
	acc.change(date, getBalance());
}
void SavingsAccount::withdraw(const Date& date, double amount,const string& desc)
{
	if (amount > getBalance())
	{
		cout << "Error: not enough money" << endl;
	}
	else
	{
		record(date, -amount, desc);
		acc.change(date, getBalance());
	}
		
}
void SavingsAccount::settle(const Date& date)
{
	double interest = acc.getSum(date) * rate / date.distance(Date(date.getYear()-1,1,1)); //计算年息
	if (interest != 0)
	{
		record(date, interest,"interest");
	}
	acc.reset(date, getBalance());
}
//CreditAccount 类相关函数的实现
CreditAccount::CreditAccount(const Date& date, const string& id, double credit, double rate, double fee)
	:Account(date,id),credit(credit),rate(rate),fee(fee),acc(date,0)
{

}
void CreditAccount::deposit(const Date& date, double amount, const string& desc)
{
	record(date, amount, desc);
	acc.change(date, getDebt());
}
void CreditAccount::withdraw(const Date& date, double amount, const string& desc)
{
	if (amount - getBalance() > credit)
	{
		error("nt enough credit");
	}
	else
	{
		record(date, -amount, desc);
		acc.change(date, getDebt());
	}
}
void CreditAccount::settle(const Date& date)
{
	double interest = acc.getSum(date) * rate;
	if (interest != 0)
		record(date, interest, "interest");
	if (date.getMonth() == 1)
		record(date, -fee, "annual fee");
	acc.reset(date, getDebt());
}
void CreditAccount::show(ostream& out) const
{
	Account::show(out);
	cout << "\tAvailable credit:" << getAvailableCredit();
}


//异常
void Account::error(const string& msg) const
{
	throw AccountException(this, msg);
}