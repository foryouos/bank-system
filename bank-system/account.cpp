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





//Account账户类构造函数
Account::Account(const Date& date, const string& id)
	:id(id), balance(0)
{
	//date.show();
	cout << date<<"\t#" << id << " created" << endl;
}
//记账:参数:Date时间，amount金额，记账描述
void Account::record(const Date& date, double amount, const string& desc)
{

	amount = floor(amount * 100 + 0.5) / 100;  //保留小数点后两位，
	balance += amount; //余额增加
	total += amount;  //账户总额增加
	//date.show();  //输出时间
	//将添加的数据存入账目记录类
	AccountRecord record(date, this, amount, balance, desc);
	//将数据插入到关联容器内部，，date为主键 
	recordMap.insert(make_pair(date, record));
	record.show();
	//cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}
//显示账户信息
void Account::show(ostream &out) const
{
	cout << "#" << id << "\tBalance:" << balance;
}


//SavingsAccount类的实现，参数:Date时间，Account的ID，利率
SavingsAccount::SavingsAccount(const Date& date, const string& id, double rate)  //时间，账户，利率
	:Account(date, id), rate(rate), acc(date, 0)
{

}
//存钱：参数：时间，金额，描述信息
void SavingsAccount::deposit(const Date& date, double amount,const string &desc)
{
	record(date, amount,desc); //记录一笔账
	//调佣accumulator函数，更新值，变更当前的时间，还有值
	acc.change(date, getBalance());
}
//取钱
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
// 计算利息:传递时间Date
void SavingsAccount::settle(const Date& date)
{
	double interest = acc.getSum(date) * rate / date.distance(Date(date.getYear()-1,1,1)); //计算年息
	if (interest != 0)
	{
		//将利息记账
		record(date, interest,"interest");
	}
	//初始化，日期，数值，累加器清零
	acc.reset(date, getBalance());
}
//CreditAccount 类默认构造函数的实现
CreditAccount::CreditAccount(const Date& date, const string& id, double credit, double rate, double fee)
	:Account(date,id),credit(credit),rate(rate),fee(fee),acc(date,0)
{

}
//存入信用卡
void CreditAccount::deposit(const Date& date, double amount, const string& desc)
{
	record(date, amount, desc);
	acc.change(date, getDebt());
}
//取出信用卡金额
void CreditAccount::withdraw(const Date& date, double amount, const string& desc)
{
	if (amount - getBalance() > credit)
	{
		error("nt enough credit");
	}
	else
	{
		//使用负数 ，减
		record(date, -amount, desc);
		acc.change(date, getDebt());
	}
}
//结算信用卡的利息
void CreditAccount::settle(const Date& date)
{
	double interest = acc.getSum(date) * rate;
	if (interest != 0)
		record(date, interest, "interest");
	if (date.getMonth() == 1)
		record(date, -fee, "annual fee");
	acc.reset(date, getDebt());
}
//输出，包括信用卡额度
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