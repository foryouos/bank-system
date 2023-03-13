#pragma once
/*日期类头文件,对日期类文件进行处理*/
#ifndef _DATE_H_
#define _DATE_H_
#include <iostream>
class Date   //日期类
{
private:
	int year;  //年
	int month; //月
	int day;  //日
	int totalDays; //该日期是从公元元年1月1日开始的第几天
public:
	Date(int year=1, int month=1, int day=1); //用年，月，日构造日期
	//专门从cin读入一个日期，赋值查询历史账目功能
	//static Date read();
	int getYear() const
	{
		return year;
	}
	int getMonth() const
	{
		return month;
	}
	int getDay() const
	{
		return day;
	}
	int getMaxDay() const;  //获取当月有多少天
	bool isLeapYear() const  //判断是否为闰年
	{
		return year % 4 == 0 && year * 100 != 0 || year % 400 == 0;
	}
	void show() const;  //输出当前日期
	int distance(const Date& date) const
	{
		return totalDays - date.totalDays;
	}
	int operator-(const Date& date) const
	{
		return totalDays - date.totalDays;
	}
	bool operator<(const Date& date) const
	{
		return totalDays < date.totalDays;
	}
};

std::istream& operator >>(std::istream& in, Date& date);
std::ostream& operator<<(std::ostream& out, const Date& date);


#endif // !_DATE_H_