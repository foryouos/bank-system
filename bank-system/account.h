#pragma once
/*银行账户类头文件*/
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include "date.h"
#include "accumulator.h"
#include <string>  //字符串头文件
#include <istream>
#include <map>  //引出关联容器
#include <stdexcept>
//前置声明
class Account;
//账目记录类
class AccountRecord
{
private:
	//日期
	Date date;
	//账户
	const Account* account; 
	// 账户金额
	double amount;
	// 余额
	double balance;
	//描述
	std::string desc;
public:
	//构造函数
	AccountRecord(const Date& date, const Account* account, double amount, double balance, const std::string& desc);
	//输出当前记录
	void show() const;
};

// 创建关联容器，建立日期和账户记录类的已排序列表
typedef std::multimap<Date, AccountRecord>RecordMap;
//账户父类
class Account
{
public:
	std::string id; //账户Id字符串
	double balance;  //账户余额
	static double total;  //所有账户的总金额静态变量
	static RecordMap recordMap;  //账目记录
protected:
	//提供派生类调用的构造函数：日期，id为账户
	Account(const Date& date, const std::string& id);
	//记录一笔账，date为日期，amount为金额，desc为说明
	void record(const Date& date, double amount, const std::string& desc);
	//报告错误信息
	void error(const std::string& msg) const;
public:
	//获取账户id
	const std::string& getId() const
	{
		return id;
	}
	//获取账户余额
	double getBalance() const
	{
		return balance;
	}
	//获取账户总金额
	static double getTotal()
	{
		return total;
	}
	//纯虚函数，没有具体的操作内容，要求各派生类根据需要定义自己的版本
	//存入现金，date为日期，amount为金额，desc为款项说明
	virtual void deposit(const Date& date, double amount, const std::string& desc) = 0;
	//纯虚函数，没有具体的操作内容，要求各派生类根据需要定义自己的版本
	//取出现金，date为日期，amount为金额，desc为款项说明
	virtual void withdraw(const Date& date, double amount, const std::string& desc) = 0;
	//结算（计算利息、年费等），每月结算一次，date为结算日期
	virtual void settle(const Date& date) = 0;
	//显示账户信息
	virtual void show(std::ostream& out) const;
	//查询指定时间内的账目记录，开始Date，结束Date
	static void query(const Date& begin, const Date& end);

	
};
//内联重载: 将Account输出调用Account.show()
inline std::ostream& operator<<(std::ostream& out, const Account& account)
{
	account.show(out);
	return out;
}

class SavingsAccount : public Account  //存储账户类
{
private:
	Accumulator acc;  //辅助计算利息的累加器
	double rate;	//存款的年利率
public:
	//储蓄账户，日期Date,账户Account的id，存款利率
	SavingsAccount(const Date &date, const std::string &id, double rate);
	//获取储蓄账户的存款利率
	double getRate() const
	{
		return rate;
	}
	// 存钱: 参数: 日期Date,金额，描述信息
	void deposit(const Date &date, double amount,const std::string &desc);// 存入现金
	//取款:参数: 日期Date,金额，描述信息
	void withdraw(const Date &date, double amount,const std::string &desc);//取出现金
	//结算利息:参数:Date日期
	void settle(const Date &date);
};
class CreditAccount : public Account  //信用账户类
{
private:
	Accumulator acc; //辅助计算利息的累加器
	//信用额度
	double credit;  
	double rate;  //欠款的日利率
	double fee;   //信用卡年费
	//获取欠款额
	double getDebt()   
	{ 
		//获取账户Account的余额，
		double balance = getBalance();  
		//如果余额大于0不欠钱，返回0，否则返回balance
		return (balance < 0 ? balance : 0);
	}
public:  //构造函数
	//信用卡类:参数:日期Date,账户Account：id，信用额度，欠款日利率，信用卡年费
	CreditAccount(const Date& date, const std::string& id, double credit, double rate, double fee);
	//获取信用卡额度
	double getCredit() const
	{
		return credit;
	}
	//获取信用卡日利率
	double getRate() const
	{
		return rate;
	}
	//获取信用卡年费
	double getFee() const
	{
		return fee;
	}
	//返回信用卡还可用额度，若账户余额为负，用信用卡补上
	double getAvailableCredit() const
	{
		if (getBalance() < 0)
			return credit + getBalance();
		else
			return credit;
	}
	//存入现金：参数:日期Date,账户Account金额，存款描述
	void deposit(const Date& date, double amount, const std::string& desc);
	//取出现金，参数：取款日期Date,取款金额，取款描述
	void withdraw(const Date& date, double amount, const std::string& desc);
	//结算利息和年费，参数Date日期
	void settle(const Date& date);//结算利息和年费，每月1号调用一次该函数
	// 输出账户id，账户金额，账户余额
	void show() const;
	//虚函数输出
	virtual void show(std::ostream& out) const;
};
//账户异常处理类
class AccountException :public std::runtime_error
{
private:
	// 账户
	const Account* account;
public:
	//传递运行中的异常信息，以及账户Account类
	AccountException(const Account* account, const std::string& msg)
		:runtime_error(msg), account(account)
	{

	}
	//获得异常账户类
	const Account* getAccount() const
	{
		return account;
	}
};



#endif //_ACCOUNT_H_