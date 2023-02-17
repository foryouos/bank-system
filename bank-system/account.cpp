/*
project :��ʵ���ļ�
*/
#include "account.h"
#include <iostream>
#include <cmath>
using namespace std;

double SavingsAccount::total = 0;
//Account�ຯ����Ա��ʵ��
Account::Account(const Date& date, const string& id)
	:id(id), balance(0)
{
	date.show();
	cout << "\t#" << id << " created" << endl;
}
void Account::record(const Date& date, double amount, const string& desc)
{
	
	amount = floor(amount * 100 + 0.5) / 100;  //����С�������λ��
	balance += amount;
	total += amount;
	date.show();
	cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}
void Account::show() const
{
	cout << "#" << id << "\tBalance:" << balance;
}
void Account::error(const string& msg) const
{
	cout << "Erroe(#" << id << "):" << msg << endl;
}

//SavingsAccount���ʵ��
SavingsAccount::SavingsAccount(const Date& date, const string& id, double rate)
	:Account(date, id), rate(rate), acc(date, 0)
{

}

void SavingsAccount::deposit(const Date& date, double amount,const string &desc)
{
	record(date, amount,desc); //��¼һ����
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
	double interest = acc.getSum(date) * rate / date.distance(Date(date.getYear()-1,1,1)); //������Ϣ
	if (interest != 0)
	{
		record(date, interest,"interest");
	}
	acc.reset(date, getBalance());
}
//CreditAccount ����غ�����ʵ��
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
void CreditAccount::show() const
{
	Account::show();
	cout << "\tAvailable credit:" << getAvailableCredit();
}