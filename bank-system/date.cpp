/*日期类实现函数*/
#include "date.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>  //标准库表头,此头文件是错误处理库的一部分
using namespace std;
namespace  //使用namespace使下面的定义只能在当前文件中有效
{
	//存储平年中每个月1日之前有多少天，为便于getMaxDay函数的实现，
	const int DAYS_BEFORE_MONTH[] = { 0,31,59,90,120,151,181,212,143,273,304,334,365 };
}

Date::Date(int year, int month, int day) :year(year), month(month), day(day)
{
	if (day <= 0 || day > getMaxDay())
	{
		throw runtime_error("Invalid date"); //Date发生异常，直接使用标准程序库构造异常抛出
	}
	//减一是为了计算总天数，会加上月份和天数，年份日要减一
	int years = year - 1;
	//计算总天数
	totalDays = years * 365 + years / 4 - years / 100 + years / 400 + DAYS_BEFORE_MONTH[month - 1] + day;
	//如果是瑞年并且月份大约2，总天数+1
	if (isLeapYear() && month > 2)
		totalDays++;
}
//返回这月最大天数
int Date::getMaxDay() const 
{
	if (isLeapYear() && month == 2)
	{
		return 29;
	}
	else
	{
		return DAYS_BEFORE_MONTH[month] - DAYS_BEFORE_MONTH[month - 1];
	}
}
//输出Date的年-月-日
void Date::show() const
{
	cout << getYear() << "-" << getMonth() << "-" << getDay();
}
istream& operator>>(istream& in, Date& date) //istream通用输入流
{
	int year, month, day;
	char c1, c2;
	cout << "类似输入格式为:2019-01-01" << endl;
	in >> year >> c1 >> month >> c2 >> day;
	//对输入进行判断，若没有按照格式，返回错误
	if (c1 != '-' || c2 != '-')
		//可用于运行时检测的异常类
		throw runtime_error("Bad time format"); 

	//将所得的正确日期返回给date，指针
	date = Date(year, month, day);

	//返回用户的输入 此处
	return in;  
}
//虫重载输出流，使date按照标准格式输出
ostream& operator << (ostream& out, const Date& date) //ostream通用输出流
{
	out << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
	return out;
}