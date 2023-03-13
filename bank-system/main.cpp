/*
Project:存款类主函数文件
environment：Visual studio 2022
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
//释放空间结构体，用于析构函数
struct deleter
{
	template<class T>void operator() (T* p)
	{
		delete p;
	}
};

//建立类，用来存储账户列表和处理命令
class Controller
{
private:
	Date date;  //当前日期
	vector<Account*>accounts; //账户列表
	bool end;  //用户是够输入了退出命令
public:
	//存储用户数据，参数:Date时间
	Controller(const Date& date) :date(date), end(false)
	{

	}
	//析构函数
	~Controller();
	//返回当前的时间
	const Date& getDate() const
	{
		return date;
	}
	//bool值，返回是否结束
	bool isEnd() const
	{
		return end;
	}
	//执行一条命令，返回该命令是否改变了当前状态(即是否需要保存该命令)
	bool runCommand(const string& cmdLine);
};
//释放从账户开始到结束的所有内存
Controller::~Controller()
{
	//for_each遍历:开始，结束，执行
	//按照顺序应用给定的函数对象f到接引到范围[first,last]中每个迭代器的结果
	for_each(accounts.begin(), accounts.end(), deleter());
}
bool Controller::runCommand(const string& cmdLine)
{
	/*
	* 指令内容
	* a s S3755217 0.015
	* a s 02342342 0.015
	* a c C5392394 10000 0.0005 50
	* c 5
	
	*/
	//读取是有顺序要求的，根据指针向后，异常赋值
	//第一个赋值给cmd判断进入那个case开面
	//后面根据不同case依次赋值
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
	case 'a':	//增加账户
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
	case 'd':	//存入现金
		str >> index >> amount;
		getline(str, desc);
		accounts[index]->deposit(date, amount, desc);
		return true;
	case 'w':	//取出现金
		str >> index >> amount;
		getline(str, desc);
		accounts[index]->withdraw(date, amount, desc);
		return true;
	case 's':	//查询各账户信息
		for (size_t i = 0; i < accounts.size(); i++)
			cout << "[" << i << "] " << *accounts[i] << endl;
		return false;
	case 'c':	//改变日期
		str >> day;
		if (day < date.getDay())
			cout << "You cannot specify a previous day";
		else if (day > date.getMaxDay())
			cout << "Invalid day";
		else
			date = Date(date.getYear(), date.getMonth(), day);
		return true;
	case 'n':	//进入下个月
		if (date.getMonth() == 12)
			date = Date(date.getYear() + 1, 1, 1);
		else
			date = Date(date.getYear(), date.getMonth() + 1, 1);
		for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
			(*iter)->settle(date);
		return true;
	case 'q':	//查询一段时间内的账目
		str >> date1 >> date2;
		Account::query(date1, date2);
		return false;
	case 'e':	//退出
		end = true;
		return false;
	}
	cout << "Inavlid command: " << cmdLine << endl;
	return false;
}



int main(void)
{
	Date date(2022,11,1); //起始日期
	cout << "输出化本地化数据库数据" << endl;
	//	初始化命令
	Controller controller(date);
	string cmdLine;
	//打开文件名称
	const char* FILE_NAME = "commands.txt";
	ifstream fileIn(FILE_NAME); //以读模式打开文件

	if (fileIn) //直到执行到没有指令
	{	//如果正常打开，就执行文件中的每一条命令
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
			
		fileIn.close();	//关闭文件
	}
	//初始化指令结束

	//追加模式写入
	ofstream fileOut(FILE_NAME, ios_base::app);	//以追加模式
	//选择框
	cout << "\n\n\t\t***由于银行信息系统使用命令行存储数据形式，请严格按照输入格式进行输入:***" << endl;
	cout << "\t\t\t\t******命令选项*******"
		<<"\n\t\t\t\t\t(a)add account: a s S3755217 0.015      //a代表添加用户，s代表储蓄卡，c代表信用卡，S3755217为账户id，0.015为利率 "
		<<"\n\t\t\t\t\t(d)deposit    ：d 0 5000 salary          //d代表存钱，0代表第0个账户，5000代表金额，salary为存储说明"
		<< "\n\t\t\t\t\t(w)withdraw ： w 2 2000 buy a cell     //w为取钱，2代表第二个账户，2000金额，buy a cell说明"
		<<"\n\t\t\t\t\t(s)show      ： s                        //查看账户"
		<< "\n\t\t\t\t\t(c)change day ：c 15                   //c为改变日期，15为日 "
		<< "\n\t\t\t\t\t(n)next month ：n                       //进入下一个月"
		<<"\n\t\t\t\t\t(q)query      ：q 2022-11-01 2022-12-01   //遍历从11月1号到12月1号的账目数据"
		<<"\n\t\t\t\t\t(e)exit        ：e                       //退出" 
		<< endl;
	while (!controller.isEnd())
	{	//从标准输入读入命令并执行，直到退出
		cout << controller.getDate() << "\tTotal: " << Account::getTotal() << "\t\t\t\t\ncommand> ";
		cout << "命令输入规范：" << endl;
		string cmdLine;
		//读入命令，和文件存储格式相同
		getline(cin, cmdLine);
		try
		{
			//执行命令
			if (controller.runCommand(cmdLine))
				//并记录文件内容
				fileOut << cmdLine << endl;	//将命令写入文件
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
	

	//Array<Account*>accounts(0); //创建账户数组，元素个数为0
	//vector<Account*>accounts; 

	//cout << "(a) add account \n(d) deposit \n(w） withdraw \n(s) show \n(c) change day \n(n) next month \n(e)exit" << endl;

	//char cmd;
	//do
	//{
	//	//显示日期和总金额
	//	cout << "\tTotal :" << Account::getTotal() << "\t\ncommand>";  //输出总金额
	//	//账户类型  s为储蓄卡，
	//	char type;  
	//	// 索引号，日期
	//	int index, day;
	//	// 金额，信用额度，日利率，年费
	//	double amount, credit, rate, fee;  
	//	// desc描述信息
	//	string id, desc;
	//	Account* account;
	//	Date date1, date2;
	//	cin >> cmd;  //根据用户输入进入不同的功能
	//	switch (cmd)
	//	{
	//	case 'a':  //添加账户
	//		cout << "分别输入“账户类型(s为储蓄卡)，账户id”" << endl;
	//		cin >> type >> id;  //存入类型，信用卡或者存储卡s为存储卡，账户id
	//		if (type == 's')
	//		{
	//			cout << "输入“利率”" << endl;
	//			cin >> rate;  //存入利率
	//			account = new SavingsAccount(date, id, rate);  //时间，账户，利率
	//		}
	//		else
	//		{
	//			cout << "分别输入“信用额度，日利率，年费”" << endl;
	//			cin >> credit >> rate >> fee;  //信用额度，日利率，年费
	//			account = new CreditAccount(date, id, credit, rate, fee); //时间，账户，信用
	//		}
	//		//accounts.resize(accounts.getSize() + 1); //数组重新定义大小
	//		//accounts[accounts.getSize() - 1] = account; //将新的数组赋值给数组
	//		accounts.push_back(account);
	//		break;  //否则会下面的继续执行
	//	case 'd': //存入现金
	//		//账号索引，和金额
	//		cout << "输入账户索引号，金额" << endl;
	//		cin >> index >> amount;
	//		//输入描述信息
	//		cout << "输入描述信息:";
	//		getline(cin, desc);
	//		accounts[index]->deposit(date, amount, desc);  //会根据index对应的类型去存取
	//		break;


	//	case 'w':  //取出现金
	//		cout << "输入索引号，和取出的金额" << endl;
	//		cin >> index >> amount;
	//		cout << "输入描述信息:";
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
	//	case 'c':  //改变日期
	//		cout << "输入你要改变日期为:";
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
	//	case 'n': //进入下个月
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
	//	case 'q':  //查询一段时间内的账目
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