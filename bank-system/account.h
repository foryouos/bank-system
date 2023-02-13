#pragma once
/*�ඨ��ͷ�ļ�*/
#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_


class SavingsAccount  //�洢�˻���
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

	static double total;		//�����˻����ܽ���̬

	//��ȡ��ָ������Ϊֹ�Ĵ������ۻ�ֵ
	double accumulate(int date) const
	{
		return accumulation + balance * (date - lastDate);
	}
};

#endif //_ACCOUNT_H_