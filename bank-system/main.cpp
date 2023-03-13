/*
Project:������������ļ�
environment��Visual studio 2022
*/
#include "account.h"
#include "Array.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct deleter
{
	template<class T>void operator() (T* p)
	{
		delete p;
	}
};

//�����࣬�����洢�˻��б�ʹ�������
class Controller
{
private:
	Date date;  //��ǰ����
	vector<Account*>accounts; //�˻��б�
	bool end;  //�û��ǹ��������˳�����
public:
	Controller(const Date& date) :date(date), end(false)
	{

	}
	~Controller();
	const Date& getDate() const
	{
		return date;
	}
	bool isEnd() const
	{
		return end;
	}
	//ִ��һ��������ظ������Ƿ�ı��˵�ǰ״̬(���Ƿ���Ҫ���������)
	bool runCommand(const string& cmdLine);
};
Controller::~Controller()
{
	for_each(accounts.begin(), accounts.end(), deleter());
}
bool Controller::runCommand(const string& cmdLine)
{
	istringstream str(cmdLine);
	char cmd, type;
	int index, day;
	double amount, credit, rate, fee;
	string id, desc;
	Account* account;
	Date date1, date2;
	str >> cmd;
	switch (cmd)
	{
	case 'a':	//�����˻�
		str >> type >> id;
		if (type == 's')
		{
			str >> rate;
			account = new SavingsAccount(date, id, rate);
		}
		else
		{
			str >> credit >> rate >> fee;
			account = new CreditAccount(date, id, credit, rate, fee);
		}
		accounts.push_back(account);
		return true;
	case 'd':	//�����ֽ�
		str >> index >> amount;
		getline(str, desc);
		accounts[index]->deposit(date, amount, desc);
		return true;
	case 'w':	//ȡ���ֽ�
		str >> index >> amount;
		getline(str, desc);
		accounts[index]->withdraw(date, amount, desc);
		return true;
	case 's':	//��ѯ���˻���Ϣ
		for (size_t i = 0; i < accounts.size(); i++)
			cout << "[" << i << "] " << *accounts[i] << endl;
		return false;
	case 'c':	//�ı�����
		str >> day;
		if (day < date.getDay())
			cout << "You cannot specify a previous day";
		else if (day > date.getMaxDay())
			cout << "Invalid day";
		else
			date = Date(date.getYear(), date.getMonth(), day);
		return true;
	case 'n':	//�����¸���
		if (date.getMonth() == 12)
			date = Date(date.getYear() + 1, 1, 1);
		else
			date = Date(date.getYear(), date.getMonth() + 1, 1);
		for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
			(*iter)->settle(date);
		return true;
	case 'q':	//��ѯһ��ʱ���ڵ���Ŀ
		str >> date1 >> date2;
		Account::query(date1, date2);
		return false;
	case 'e':	//�˳�
		end = true;
		return false;
	}
	cout << "Inavlid command: " << cmdLine << endl;
	return false;
}



int main(void)
{
	Date date(2008, 11, 1); //��ʼ����
	Controller controller(date);
	string cmdLine;
	const char* FILE_NAME = "commands.txt";
	ifstream fileIn(FILE_NAME); //�Զ�ģʽ���ļ�

	if (fileIn)
	{	//��������򿪣���ִ���ļ��е�ÿһ������
		while (getline(fileIn, cmdLine))
		{
			try
			{
				controller.runCommand(cmdLine);
			}
			catch (exception& e)
			{
				cout << "Bad line in" << FILE_NAME << ":" << cmdLine << endl;
				cout << "Error:" << e.what() << endl;
				return 1;
			}
		}
			
		fileIn.close();	//�ر��ļ�
	}

	ofstream fileOut(FILE_NAME, ios_base::app);	//��׷��ģʽ
	cout << "(a)add account \n(d)deposit \n(w)withdraw \n(s)show \n(c)change day \n(n)next month \n(q)query \n(e)exit" << endl;
	while (!controller.isEnd())
	{	//�ӱ�׼����������ִ�У�ֱ���˳�
		cout << controller.getDate() << "\tTotal: " << Account::getTotal() << "\tcommand> ";
		string cmdLine;
		getline(cin, cmdLine);
		try
		{
			if (controller.runCommand(cmdLine))
				fileOut << cmdLine << endl;	//������д���ļ�
		}
		catch (AccountException& e)
		{
			cout << "Erroe(#" << e.getAccount()->getId() << "):" << e.what() << endl;
		}
		catch (exception& e)
		{
			cout << "Error: " << e.what() << endl;
		}
		
	}
	return 0;
	

	//Array<Account*>accounts(0); //�����˻����飬Ԫ�ظ���Ϊ0
	//vector<Account*>accounts; 

	//cout << "(a) add account \n(d) deposit \n(w�� withdraw \n(s) show \n(c) change day \n(n) next month \n(e)exit" << endl;

	//char cmd;
	//do
	//{
	//	//��ʾ���ں��ܽ��
	//	cout << "\tTotal :" << Account::getTotal() << "\t\ncommand>";  //����ܽ��
	//	//�˻�����  sΪ�����
	//	char type;  
	//	// �����ţ�����
	//	int index, day;
	//	// �����ö�ȣ������ʣ����
	//	double amount, credit, rate, fee;  
	//	// desc������Ϣ
	//	string id, desc;
	//	Account* account;
	//	Date date1, date2;
	//	cin >> cmd;  //�����û�������벻ͬ�Ĺ���
	//	switch (cmd)
	//	{
	//	case 'a':  //����˻�
	//		cout << "�ֱ����롰�˻�����(sΪ���)���˻�id��" << endl;
	//		cin >> type >> id;  //�������ͣ����ÿ����ߴ洢��sΪ�洢�����˻�id
	//		if (type == 's')
	//		{
	//			cout << "���롰���ʡ�" << endl;
	//			cin >> rate;  //��������
	//			account = new SavingsAccount(date, id, rate);  //ʱ�䣬�˻�������
	//		}
	//		else
	//		{
	//			cout << "�ֱ����롰���ö�ȣ������ʣ���ѡ�" << endl;
	//			cin >> credit >> rate >> fee;  //���ö�ȣ������ʣ����
	//			account = new CreditAccount(date, id, credit, rate, fee); //ʱ�䣬�˻�������
	//		}
	//		//accounts.resize(accounts.getSize() + 1); //�������¶����С
	//		//accounts[accounts.getSize() - 1] = account; //���µ����鸳ֵ������
	//		accounts.push_back(account);
	//		break;  //���������ļ���ִ��
	//	case 'd': //�����ֽ�
	//		//�˺��������ͽ��
	//		cout << "�����˻������ţ����" << endl;
	//		cin >> index >> amount;
	//		//����������Ϣ
	//		cout << "����������Ϣ:";
	//		getline(cin, desc);
	//		accounts[index]->deposit(date, amount, desc);  //�����index��Ӧ������ȥ��ȡ
	//		break;


	//	case 'w':  //ȡ���ֽ�
	//		cout << "���������ţ���ȡ���Ľ��" << endl;
	//		cin >> index >> amount;
	//		cout << "����������Ϣ:";
	//		getline(cin, desc);
	//		accounts[index]->withdraw(date, amount, desc);
	//		break;

	//	case 's':
	//		for (int i = 0; i < accounts.size(); i++)
	//		{
	//			cout << "[" << i << "]";
	//			accounts[i]->show();
	//			cout << endl;
	//		}
	//		break;
	//	case 'c':  //�ı�����
	//		cout << "������Ҫ�ı�����Ϊ:";
	//		cin >> day;
	//		if (day < date.getDay())
	//			cout << "You cannot specify a previous day";
	//		else if(day>date.getMaxDay())
	//		{
	//			cout << "Invalid day";
	//		}
	//		else
	//		{
	//			date = Date(date.getYear(), date.getMonth(), day);
	//		}
	//		break;
	//	case 'n': //�����¸���
	//		if (date.getMonth() == 12)
	//			date = Date(date.getYear() + 1, 1, 1);
	//		else
	//			date = Date(date.getYear(), date.getMonth() + 1, 1);
	//		for (vector<Account *>::iterator iter = accounts.begin();iter!=accounts.end();++iter)
	//		{
	//			/*accounts[i]->settle(date);*/
	//			(*iter)->settle(date);
	//		}
	//		break;
	//	case 'q':  //��ѯһ��ʱ���ڵ���Ŀ
	//		date1 = Date::read();
	//		date2 = Date::read();
	//		Account::query(date1, date2);
	//		break;
	//	default:
	//		break;
	//	}
	//} while (cmd!='e');
	////for (int i = 0; i < accounts.getSize(); i++)
	////{
	////	delete accounts[i];
	////}
	//for_each(accounts.begin(), accounts.end(), deleter());
	//return 0;

	
}