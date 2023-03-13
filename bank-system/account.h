#pragma once
/*�����˻���ͷ�ļ�*/
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include "date.h"
#include "accumulator.h"
#include <string>  //�ַ���ͷ�ļ�
#include <istream>
#include <map>  //������������
#include <stdexcept>
//ǰ������
class Account;
//��Ŀ��¼��
class AccountRecord
{
private:
	//����
	Date date;
	//�˻�
	const Account* account; 
	// �˻����
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

// ���������������������ں��˻���¼����������б�
typedef std::multimap<Date, AccountRecord>RecordMap;
//�˻�����
class Account
{
public:
	std::string id; //�˻�Id�ַ���
	double balance;  //�˻����
	static double total;  //�����˻����ܽ�̬����
	static RecordMap recordMap;  //��Ŀ��¼
protected:
	//�ṩ��������õĹ��캯�������ڣ�idΪ�˻�
	Account(const Date& date, const std::string& id);
	//��¼һ���ˣ�dateΪ���ڣ�amountΪ��descΪ˵��
	void record(const Date& date, double amount, const std::string& desc);
	//���������Ϣ
	void error(const std::string& msg) const;
public:
	//��ȡ�˻�id
	const std::string& getId() const
	{
		return id;
	}
	//��ȡ�˻����
	double getBalance() const
	{
		return balance;
	}
	//��ȡ�˻��ܽ��
	static double getTotal()
	{
		return total;
	}
	//���麯����û�о���Ĳ������ݣ�Ҫ��������������Ҫ�����Լ��İ汾
	//�����ֽ�dateΪ���ڣ�amountΪ��descΪ����˵��
	virtual void deposit(const Date& date, double amount, const std::string& desc) = 0;
	//���麯����û�о���Ĳ������ݣ�Ҫ��������������Ҫ�����Լ��İ汾
	//ȡ���ֽ�dateΪ���ڣ�amountΪ��descΪ����˵��
	virtual void withdraw(const Date& date, double amount, const std::string& desc) = 0;
	//���㣨������Ϣ����ѵȣ���ÿ�½���һ�Σ�dateΪ��������
	virtual void settle(const Date& date) = 0;
	//��ʾ�˻���Ϣ
	virtual void show(std::ostream& out) const;
	//��ѯָ��ʱ���ڵ���Ŀ��¼����ʼDate������Date
	static void query(const Date& begin, const Date& end);

	
};
//��������: ��Account�������Account.show()
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
	//�����˻�������Date,�˻�Account��id���������
	SavingsAccount(const Date &date, const std::string &id, double rate);
	//��ȡ�����˻��Ĵ������
	double getRate() const
	{
		return rate;
	}
	// ��Ǯ: ����: ����Date,��������Ϣ
	void deposit(const Date &date, double amount,const std::string &desc);// �����ֽ�
	//ȡ��:����: ����Date,��������Ϣ
	void withdraw(const Date &date, double amount,const std::string &desc);//ȡ���ֽ�
	//������Ϣ:����:Date����
	void settle(const Date &date);
};
class CreditAccount : public Account  //�����˻���
{
private:
	Accumulator acc; //����������Ϣ���ۼ���
	//���ö��
	double credit;  
	double rate;  //Ƿ���������
	double fee;   //���ÿ����
	//��ȡǷ���
	double getDebt()   
	{ 
		//��ȡ�˻�Account����
		double balance = getBalance();  
		//���������0��ǷǮ������0�����򷵻�balance
		return (balance < 0 ? balance : 0);
	}
public:  //���캯��
	//���ÿ���:����:����Date,�˻�Account��id�����ö�ȣ�Ƿ�������ʣ����ÿ����
	CreditAccount(const Date& date, const std::string& id, double credit, double rate, double fee);
	//��ȡ���ÿ����
	double getCredit() const
	{
		return credit;
	}
	//��ȡ���ÿ�������
	double getRate() const
	{
		return rate;
	}
	//��ȡ���ÿ����
	double getFee() const
	{
		return fee;
	}
	//�������ÿ������ö�ȣ����˻����Ϊ���������ÿ�����
	double getAvailableCredit() const
	{
		if (getBalance() < 0)
			return credit + getBalance();
		else
			return credit;
	}
	//�����ֽ𣺲���:����Date,�˻�Account���������
	void deposit(const Date& date, double amount, const std::string& desc);
	//ȡ���ֽ𣬲�����ȡ������Date,ȡ���ȡ������
	void withdraw(const Date& date, double amount, const std::string& desc);
	//������Ϣ����ѣ�����Date����
	void settle(const Date& date);//������Ϣ����ѣ�ÿ��1�ŵ���һ�θú���
	// ����˻�id���˻����˻����
	void show() const;
	//�麯�����
	virtual void show(std::ostream& out) const;
};
//�˻��쳣������
class AccountException :public std::runtime_error
{
private:
	// �˻�
	const Account* account;
public:
	//���������е��쳣��Ϣ���Լ��˻�Account��
	AccountException(const Account* account, const std::string& msg)
		:runtime_error(msg), account(account)
	{

	}
	//����쳣�˻���
	const Account* getAccount() const
	{
		return account;
	}
};



#endif //_ACCOUNT_H_