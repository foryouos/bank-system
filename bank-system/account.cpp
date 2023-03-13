/*
project :Account�˻���ʵ���ļ�cpp
*/
#include "account.h"
#include <iostream>
#include <cmath>
#include <utility>
using namespace std;
using namespace std::rel_ops;
//AccountRecord���ʵ�֣���������Date,�˻�Account�࣬����������Ϣ
AccountRecord::AccountRecord(const Date& date, const Account* account, double amount, double balance, const std::string& desc)
	:date(date), account(account), amount(amount), balance(balance), desc(desc)
{

}
// չ�ֳ��˻���¼����˻�ʱ�䣬Id���������������ÿ�)��������Ϣ
void AccountRecord::show() const
{
	//date.show();
	cout <<date<< "\t#" << account->getId() << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}




//����ܽ��ȫ�ֱ���(�����˻���
double Account::total = 0;
// Account���е��˻���¼
RecordMap Account::recordMap;





//Account�˻��๹�캯��
Account::Account(const Date& date, const string& id)
	:id(id), balance(0)
{
	//date.show();
	cout << date<<"\t#" << id << " created" << endl;
}
//����:����:Dateʱ�䣬amount����������
void Account::record(const Date& date, double amount, const string& desc)
{

	amount = floor(amount * 100 + 0.5) / 100;  //����С�������λ��
	balance += amount; //�������
	total += amount;  //�˻��ܶ�����
	//date.show();  //���ʱ��
	//����ӵ����ݴ�����Ŀ��¼��
	AccountRecord record(date, this, amount, balance, desc);
	//�����ݲ��뵽���������ڲ�����dateΪ���� 
	recordMap.insert(make_pair(date, record));
	record.show();
	//cout << "\t#" << id << "\t" << amount << "\t" << balance << "\t" << desc << endl;
}
//��ʾ�˻���Ϣ
void Account::show(ostream &out) const
{
	cout << "#" << id << "\tBalance:" << balance;
}


//SavingsAccount���ʵ�֣�����:Dateʱ�䣬Account��ID������
SavingsAccount::SavingsAccount(const Date& date, const string& id, double rate)  //ʱ�䣬�˻�������
	:Account(date, id), rate(rate), acc(date, 0)
{

}
//��Ǯ��������ʱ�䣬��������Ϣ
void SavingsAccount::deposit(const Date& date, double amount,const string &desc)
{
	record(date, amount,desc); //��¼һ����
	//��Ӷaccumulator����������ֵ�������ǰ��ʱ�䣬����ֵ
	acc.change(date, getBalance());
}
//ȡǮ
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
// ������Ϣ:����ʱ��Date
void SavingsAccount::settle(const Date& date)
{
	double interest = acc.getSum(date) * rate / date.distance(Date(date.getYear()-1,1,1)); //������Ϣ
	if (interest != 0)
	{
		//����Ϣ����
		record(date, interest,"interest");
	}
	//��ʼ�������ڣ���ֵ���ۼ�������
	acc.reset(date, getBalance());
}
//CreditAccount ��Ĭ�Ϲ��캯����ʵ��
CreditAccount::CreditAccount(const Date& date, const string& id, double credit, double rate, double fee)
	:Account(date,id),credit(credit),rate(rate),fee(fee),acc(date,0)
{

}
//�������ÿ�
void CreditAccount::deposit(const Date& date, double amount, const string& desc)
{
	record(date, amount, desc);
	acc.change(date, getDebt());
}
//ȡ�����ÿ����
void CreditAccount::withdraw(const Date& date, double amount, const string& desc)
{
	if (amount - getBalance() > credit)
	{
		error("nt enough credit");
	}
	else
	{
		//ʹ�ø��� ����
		record(date, -amount, desc);
		acc.change(date, getDebt());
	}
}
//�������ÿ�����Ϣ
void CreditAccount::settle(const Date& date)
{
	double interest = acc.getSum(date) * rate;
	if (interest != 0)
		record(date, interest, "interest");
	if (date.getMonth() == 1)
		record(date, -fee, "annual fee");
	acc.reset(date, getDebt());
}
//������������ÿ����
void CreditAccount::show(ostream& out) const
{
	Account::show(out);
	cout << "\tAvailable credit:" << getAvailableCredit();
}


//�쳣
void Account::error(const string& msg) const
{
	throw AccountException(this, msg);
}

//�˻���¼��ѯʵ�֣�����:��ʼDate,����Date
void Account::query(const Date& begin, const Date& end)
{
	//�ӿ�ʼ����β�������
	if (begin <= end)
	{
		//lower_bound����ָ���׸���С�ڸ�������Ԫ�صĵ�����
		RecordMap::iterator iter1 = recordMap.lower_bound(begin);
		//upper_bound����ָ���׸����ڸ�������Ԫ�صĵ�����
		RecordMap::iterator iter2 = recordMap.upper_bound(end);
		for (RecordMap::iterator iter = iter1; iter != iter2; ++iter)
		{
			iter->second.show();
		}
	}
}