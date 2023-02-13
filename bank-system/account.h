#pragma once
/*类定义头文件*/
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_


class SavingsAccount  //存储账户类
{
public:
	SavingsAccount(int date, int id, double rate);
	int getId() const
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

	static double total;		//所有账户的总金额，静态

	//获取到指定日期为止的存款金额按日累积值
	double accumulate(int date) const
	{
		return accumulation + balance * (date - lastDate);
	}
};

#endif //_ACCOUNT_H_