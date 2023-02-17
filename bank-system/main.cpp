/*
Project:存款类主函数文件
environment：Visual studio 2022
*/
#include "account.h"
#include <iostream>
using namespace std;
int main(void)
{
	Date date(2008, 11, 1); //起始日期
	
	//建立几个账户
	SavingsAccount accounts[] = //类数组
	{
		SavingsAccount(date, "03755217", 0.015),
		SavingsAccount(date, "02342342", 0.015)
	};
	//信用卡账户
	CreditAccount ca(date, "C5392394", 10000, 0.0005, 50);
	const int n = sizeof(accounts) / sizeof(SavingsAccount);  //账户总数
	//几笔账目
	accounts[0].deposit(Date(2008,11,5), 5000,"salary");   //添加存款
	ca.withdraw(Date(2008, 11, 15), 2000, "buy a cell");  //信用卡消费
	accounts[1].deposit(Date(2008, 11, 25), 10000,"sell stock 0323");
	//结算信用卡
	ca.settle(Date(2008, 12, 1));
	//12月账户
	accounts[0].deposit(Date(2008, 12, 5), 5500,"salary");
	accounts[1].withdraw(Date(2008, 12, 20), 4000,"buy a laptop");  //取款
	//结算所有账户并输出各个账户信息
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		accounts[i].settle(Date(2009, 1, 1)); //计算年息
		accounts[i].show();
		cout << endl;
	}
	ca.show();
	cout << endl;
	cout << "Total :" << SavingsAccount::getTotal() << endl;
	return 0;
}