/*
project :��ʵ���ļ�
*/
#include "account.h"
#include <iostream>
#include <cmath>
using namespace std;
//������Ա��ʵ��
double SavingsAccount::total = 0;
SavingsAccount::SavingsAccount(int date, int id, double rate) :id(id), balance(0), rate(rate), lastDate(date), accumulation(0)
{
	cout << date << "\t#" << id << "is created" << endl;
}
void SavingsAccount::record(int date, double amount)
{
	accumulation = accumulate(date); //��ȡ��date����Ϊֹ�Ĵ������ۻ�ֵ
	lastDate = date;
	//floor��������ȡ�ò�����һ�����������������cmathͷ�ļ��У�
	//ceil��������ȡ�ò�С��һ��������С����
	amount = floor(amount * 100 + 0.5) / 100;  //����С�������λ��
	balance += amount;
	total += amount;
	cout << date << "\t#" << id << "\t" << amount << "\t" << balance << endl;
}
void SavingsAccount::deposit(int date, double amount)
{
	record(date, amount); //��¼һ����
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
	double interest = accumulate(date) * rate / 365; //������Ϣ
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
