#pragma once
/*�ඨ��ͷ�ļ�*/
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include "date.h"
#include <string>

class SavingsAccount  //�洢�˻���
{
private:
	std::string id; //�˺�
	double balance; //���
	double rate;   //����������
	Date lastDate;  //�ϴα����������
	double accumulation; //�����ۼ�֮��
	//��¼һ���ˣ�dateΪ���ڣ�amountΪ��descΪ˵��
	void record(const Date& date, double amount, const std::string& desc);

	static double total;		//�����˻����ܽ���̬
	//���������Ϣ
	void error(const std::string& msg) const;
	//��ȡ��ָ������Ϊֹ�Ĵ������ۻ�ֵ
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
	void deposit(const Date &date, double amount,const std::string &desc);// �����ֽ�
	void withdraw(const Date &date, double amount,const std::string &desc);//ȡ���ֽ�
	//������Ϣ
	void settle(const Date &date);
	//��ʾ�˻���Ϣ
	void show() const;

};

#endif //_ACCOUNT_H_