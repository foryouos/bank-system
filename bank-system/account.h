#pragma once
/*�ඨ��ͷ�ļ�*/
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include "date.h"
#include "accumulator.h"
#include <string>
#include <istream>
#include <map>
#include <stdexcept>
//ǰ������
class Account;
//��Ŀ��¼
class AccountRecord
{
private:
	//����
	Date date;
	//�˻�
	const Account* account; 
	//���
	double amount;
	// ���
	double balance;
	//����
	std::string desc;
public:
	//���캯��
	AccountRecord(const Date& date, const Account* account, double amount, double balance, const std::string& desc);
	//�����ǰ��¼
	void show() const;
};


typedef std::multimap<Date, AccountRecord>RecordMap;
//�˻���
class Account
{
public:
	std::string id; //�˻�
	double balance;  //���
	static double total;  //�����˻����ܽ��
	static RecordMap recordMap;  //��Ŀ��¼
protected:
	//�ṩ��������õĹ��캯����idΪ�˻�
	Account(const Date& date, const std::string& id);
	//��¼һ���ˣ�dateΪ���ڣ�amountΪ��descΪ˵��
	void record(const Date& date, double amount, const std::string& desc);
	//���������Ϣ
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
	//�����ֽ�dateΪ���ڣ�amountΪ��descΪ����˵��
	virtual void deposit(const Date& date, double amount, const std::string& desc) = 0;
	//ȡ���ֽ�dateΪ���ڣ�amountΪ��descΪ����˵��
	virtual void withdraw(const Date& date, double amount, const std::string& desc) = 0;
	//���㣨������Ϣ����ѵȣ���ÿ�½���һ�Σ�dateΪ��������
	virtual void settle(const Date& date) = 0;
	//��ʾ�˻���Ϣ

	//��ʾ�˻���Ϣ
	//void show() const;
	virtual void show(std::ostream& out) const;
	//��ѯָ��ʱ���ڵ���Ŀ��¼
	static void query(const Date& begin, const Date& end);

	
};

inline std::ostream& operator<<(std::ostream& out, const Account& account)
{
	account.show(out);
	return out;
}

class SavingsAccount : public Account  //�洢�˻���
{
private:
	Accumulator acc;  //����������Ϣ���ۼ���
	double rate;	//����������
public:
	SavingsAccount(const Date &date, const std::string &id, double rate);

	double getRate() const
	{
		return rate;
	}
	void deposit(const Date &date, double amount,const std::string &desc);// �����ֽ�
	void withdraw(const Date &date, double amount,const std::string &desc);//ȡ���ֽ�
	//������Ϣ
	void settle(const Date &date);
};
class CreditAccount : public Account  //�����˻���
{
private:
	Accumulator acc; //����������Ϣ���ۼ���
	double credit;  //���ö��
	double rate;  //Ƿ���������
	double fee;   //���ÿ����
	//��ȡǷ���
	double getDebt()   
	{ 
		double balance = getBalance();  
		return (balance < 0 ? balance : 0);
	}
public:  //���캯��
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
	//�����ֽ�
	void deposit(const Date& date, double amount, const std::string& desc);
	//ȡ���ֽ�
	void withdraw(const Date& date, double amount, const std::string& desc);
	void settle(const Date& date);//������Ϣ����ѣ�ÿ��1�ŵ���һ�θú���
	void show() const;
	virtual void show(std::ostream& out) const;
};

class AccountException :public std::runtime_error
{
private:
	const Account* account;
public:
	AccountException(const Account* account, const std::string& msg)
		:runtime_error(msg), account(account)
	{

	}
	const Account* getAccount() const
	{
		return account;
	}
};



#endif //_ACCOUNT_H_