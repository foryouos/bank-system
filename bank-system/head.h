#pragma once
#include <iostream>
#include <cmath>
using namespace std;
class SavingsAccount  //�洢�˻���
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
	void deposit(int date, double amount);// �����ֽ�
	void withdraw(int date, double amount);//ȡ���ֽ�
	//������Ϣ
	void settle(int date);
	//��ʾ�˻���Ϣ
	void show();
private:
	int id; //�˺�
	double balance; //���
	double rate;   //����������
	int lastDate;  //�ϴα����������
	double accumulation; //�����ۼ�֮��
	//��¼һ���ˣ�dateΪ���ڣ�amountΪ��descΪ˵��
	void record(int date, double amount);
	//��ȡ��ָ������Ϊֹ�Ĵ������ۻ�ֵ
	double accumulate(int date) const
	{
		return accumulation + balance * (date - lastDate);
	}
};
//������Ա��ʵ��
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