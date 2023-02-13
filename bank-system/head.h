#pragma once
#include <iostream>
#include <cmath>
using namespace std;
class SavingsAccount  //存储账户类
{
public:
	SavingsAccount(int date, int id, double rate);
	int getId()
	{
		return id;
	}
	double getBalance()
	{
		return balance;
	}
	double getRate()
	{
		return rate;
	}
	void deposit(int date, double amount);// 存入现金
	void withdraw(int date, double amount);//取出现金
	//结算利息
	void settle(int date);
	//显示账户信息
	void show();
private:
	int id; //账号
	double balance; //余额
	double rate;   //存款的年利率
	int lastDate;  //上次变更余额的日期
	double accumulation; //余额按日累加之和
	//记录一笔账，date为日期，amount为金额，desc为说明
	void record(int date, double amount);
	//获取到指定日期为止的存款金额按日累积值
	double accumulate(int date) const
	{
		return accumulation + balance * (date - lastDate);
	}
};
//函数成员的实现
SavingsAccount::SavingsAccount(int date, int id, double rate) :id(id), balance(0), rate(rate), lastDate(date), accumulation(0)
{
	cout << date << "\t#" << id << "is created" << endl;
}
void SavingsAccount::record(int date, double amount)
{
	accumulation = accumulate(date); //获取到date日期为止的存款金额按日累积值
	lastDate = date;
	//floor函数用来取得不大于一个数的最大整数，在cmath头文件中，
	//ceil函数用来取得不小于一个数的最小整数
	amount = floor(amount * 100 + 0.5) / 100;  //保留小数点后两位，
	balance += amount;
	cout << date << "\t#" << id << "\t" << amount << "\t" << balance << endl;
}
void SavingsAccount::deposit(int date, double amount)
{
	record(date, amount); //记录一笔账
}
void SavingsAccount::withdraw(int date, double amount)
{
	if (amount > getBalance())
		cout << "Error: not enough money" << endl;
	else
		record(date, -amount);
}
void SavingsAccount::settle(int date)
{
	double interest = accumulate(date) * rate / 365; //计算年息
	if (interest != 0)
	{
		record(date, interest);
	}
	accumulation = 0;
}
void SavingsAccount::show()
{
	cout << "#" << id << "\tBalance:" << balance;
}