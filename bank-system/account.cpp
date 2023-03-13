/*
project :类实现文件
*/
#include "account.h"
#include <iostream>
#include <cmath>
#include <utility>
using namespace std;
using namespace std::rel_ops;
//AccountRecord类的实现
AccountRecord::AccountRecord(const Date& date, const Account* account, double amount, double balance, const std::string& desc)
	:date(date), account(account), amount(amount), balance(balance), desc(desc)
{

}
void AccountRecord::show() const
{
	//date.show();
	cout <<date<< "\t#" << account->getId() << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}




//存款总金额全局变量
double Account::total = 0;
RecordMap Account::recordMap;
void Account::query(const Date& begin, const Date& end)
{
	if (begin <= end)
	{
		RecordMap::iterator iter1 = recordMap.lower_bound(begin);
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