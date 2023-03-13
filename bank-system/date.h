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
	

	//获取Date日期年份
	int getYear() const
	{
		return year;
	}
	//获取Date日期月份
	int getMonth() const
	{
		return month;
	}
	//获取Date日期天
	int getDay() const
	{
		return day;
	}
	//获取Date当月的天数
	int getMaxDay() const; 
	// 判断Date日期是否是闰年
	bool isLeapYear() const  //判断是否为闰年
	{
		return year % 4 == 0 && year * 100 != 0 || year % 400 == 0;
	}
	//输出Date日期
	void show() const; 
	//输出Data从公元元年1月1日到目前date的天数
	int distance(const Date& date) const
	{
		return totalDays - date.totalDays;
	}
	//重载Date之前的“-”号，用公元元年到目前的日期相减
	int operator-(const Date& date) const
	{
		return totalDays - date.totalDays;
	}
	//重载Date之间的“<"号，用永远元年到目前date的日期计算
	bool operator<(const Date& date) const
	{
		return totalDays < date.totalDays;
	}
};
//重载Date类输入，格式化日期格式：year-month-day
std::istream& operator >>(std::istream& in, Date& date);
//重载Date类输出,格式化日期格式：year-month-day
std::ostream& operator<<(std::ostream& out, const Date& date);


#endif // !_DATE_H_