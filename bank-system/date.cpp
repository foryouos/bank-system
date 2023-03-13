/*日期类实现函数*/
#include "date.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>  //错误
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
	int years = year - 1;
	totalDays = years * 365 + years / 4 - years / 100 + years / 400 + DAYS_BEFORE_MONTH[month - 1] + day;
	if (isLeapYear() && month > 2)
		totalDays++;
}
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
void Date::show() const
{
	cout << getYear() << "-" << getMonth() << "-" << getDay();
}
//Date Date::read()
//{
//	int year, month, day;
//	char c1, c2;
//	cout << "分别输入年份，月份，日期" << endl;
//	cin >> year >> c1 >> month >> c2 >> day;
//	return Date(year, month, day);
//}
istream& operator>>(istream& in, Date& date)
{
	int year, month, day;
	char c1, c2;
	cout << "类似输入格式为:2019-01-01" << endl;
	in >> year >> c1 >> month >> c2 >> day;
	if (c1 != '-' || c2 != '-')
		throw runtime_error("Bad time format");


	date = Date(year, month, day);
	return in;
}
ostream& operator << (ostream& out, const Date& date)
{
	out << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
	return out;
}