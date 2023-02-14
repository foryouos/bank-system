/*
project :类实现文件
*/
#include "account.h"
#include <iostream>
#include <cmath>
using namespace std;

double SavingsAccount::total = 0;
//函数成员的实现
SavingsAccount::SavingsAccount(const Date &date, const string &id, double rate)
	:id(id), balance(0), rate(rate), lastDate(date), accumulation(0)
{
	date.show();
	cout <<"\t#" << id << "is created" << endl;
}
void SavingsAccount::record(const Date& date, double amount,const string &desc)
{
	accumulation = accumulate(date); //获取到date日期为止的存款金额按日累积值
	lastDate = date;
	//floor函数用来取得不大于一个数的最大整数，在cmath头文件中，
	//ceil函数用来取得不小于一个数的最小整数
	amount = floor(amount * 100 + 0.5) / 100;  //保留小数点后两位，
	balance += amount;
	total += amount;
	date.show();
	cout << "\t#" << id << "\t" << amount << "\t" << balance <<"\t"<<desc<< endl;
}
void SavingsAccount::error(const string& msg) const
{
	cout << "Erroe(#" << id << "):" << msg << endl;
}

void SavingsAccount::deposit(const Date& date, double amount,const string &desc)
{
	record(date, amount,desc); //记录一笔账
}
void SavingsAccount::withdraw(const Date& date, double amount,const string& desc)
{
	if (amount > getBalance())
		cout << "Error: not enough money" << endl;
	else
		record(date, -amount,desc);
}
void SavingsAccount::settle(const Date& date)
{
	double interest = accumulate(date) * rate / 365; //计算年息
	if (interest != 0)
	{
		record(date, interest,"interest");
	}
	accumulation = 0;
}
void SavingsAccount::show() const
{
	cout << "#" << id << "\tBalance:" << balance;
}
