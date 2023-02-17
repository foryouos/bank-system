/*
Project:������������ļ�
environment��Visual studio 2022
*/
#include "account.h"
#include <iostream>
using namespace std;
int main(void)
{
	Date date(2008, 11, 1); //��ʼ����
	
	//���������˻�
	SavingsAccount accounts[] = //������
	{
		SavingsAccount(date, "03755217", 0.015),
		SavingsAccount(date, "02342342", 0.015)
	};
	//���ÿ��˻�
	CreditAccount ca(date, "C5392394", 10000, 0.0005, 50);
	const int n = sizeof(accounts) / sizeof(SavingsAccount);  //�˻�����
	//������Ŀ
	accounts[0].deposit(Date(2008,11,5), 5000,"salary");   //��Ӵ��
	ca.withdraw(Date(2008, 11, 15), 2000, "buy a cell");  //���ÿ�����
	accounts[1].deposit(Date(2008, 11, 25), 10000,"sell stock 0323");
	//�������ÿ�
	ca.settle(Date(2008, 12, 1));
	//12���˻�
	accounts[0].deposit(Date(2008, 12, 5), 5500,"salary");
	accounts[1].withdraw(Date(2008, 12, 20), 4000,"buy a laptop");  //ȡ��
	//���������˻�����������˻���Ϣ
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		accounts[i].settle(Date(2009, 1, 1)); //������Ϣ
		accounts[i].show();
		cout << endl;
	}
	ca.show();
	cout << endl;
	cout << "Total :" << SavingsAccount::getTotal() << endl;
	return 0;
}