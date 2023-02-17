#pragma once
/*类定义头文件*/
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include "date.h"
#include "accumulator.h"
#include <string>
class Account
{
public:
	std::string id; //账户
	double balance;  //余额
	static double total;  //所有账户的总金额
protected:
	//提供派生类调用的构造函数，id为账户
	Account(const Date& date, const std::string& id);
	//记录一笔账，date为日期，amount为金额，desc为说明
	void record(const Date& date, double amount, const std::string& desc);
	//报告错误信息
	void error(const std::string& msg) const;
public:
	const std::string& getId() const
	{
		return id;
	}
	double getBalance() const
	{
		return balance;
	}
	static double getTotal()
	{
		return total;
	}
	//显示账户信息
	void show() const;
};


class SavingsAccount : public Account  //存储账户类
{
private:
	Accumulator acc;  //辅助计算利息的累加器
	double rate;	//存款的年利率
public:
	SavingsAccount(const Date &date, const std::string &id, double rate);

	double getRate() const
	{
		return rate;
	}
	void deposit(const Date &date, double amount,const std::string &desc);// 存入现金
	void withdraw(const Date &date, double amount,const std::string &desc);//取出现金
	//结算利息
	void settle(const Date &date);
};
class CreditAccount : public Account  //信用账户类
{
private:
	Accumulator acc; //辅助计算利息的累加器
	double credit;  //信用额度
	double rate;  //欠款的日利率
	double fee;   //信用卡年费
	//获取欠款额
	double getDebt()   
	{ 
		double balance = getBalance();  
		return (balance < 0 ? balance : 0);
	}
public:  //构造函数
	CreditAccount(const Date& date, const std::string& id, double credit, double rate, double fee);
	double getCredit() const
	{
		return credit;
	}
	double getRate() const
	{
		return rate;
	}
	double getFee() const
	{
		return fee;
	}
	double getAvailableCredit() const
	{
		if (getBalance() < 0)
			return credit + getBalance();
		else
			return credit;
	}
	//存入现金
	void deposit(const Date& date, double amount, const std::string& desc);
	//取出现金
	void withdraw(const Date& date, double amount, const std::string& desc);
	void settle(const Date& date);//结算利息和年费，每月1号调用一次该函数
	void show() const;
};
#endif //_ACCOUNT_H_