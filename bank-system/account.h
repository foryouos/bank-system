#pragma once
/*类定义头文件*/
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include "date.h"
#include <string>

class SavingsAccount  //存储账户类
{
private:
	std::string id; //账号
	double balance; //余额
	double rate;   //存款的年利率
	Date lastDate;  //上次变更余额的日期
	double accumulation; //余额按日累加之和
	//记录一笔账，date为日期，amount为金额，desc为说明
	void record(const Date& date, double amount, const std::string& desc);

	static double total;		//所有账户的总金额，静态
	//报告错误信息
	void error(const std::string& msg) const;
	//获取到指定日期为止的存款金额按日累积值
	double accumulate(const Date& date) const
	{
		return accumulation + balance * date.distance(lastDate);
	}
public:
	SavingsAccount(const Date &date, const std::string &id, double rate);
	SavingsAccount();
	const std::string &getId() const
	{
		return id;
	}
	double getBalance() const
	{
		return balance;
	}
	double getRate() const
	{
		return rate;
	}
	static double getTotal()
	{
		return total;
	}
	void deposit(const Date &date, double amount,const std::string &desc);// 存入现金
	void withdraw(const Date &date, double amount,const std::string &desc);//取出现金
	//结算利息
	void settle(const Date &date);
	//显示账户信息
	void show() const;

};

#endif //_ACCOUNT_H_