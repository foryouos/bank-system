#pragma once
/*������ͷ�ļ�,���������ļ����д���*/
#ifndef _DATE_H_
#define _DATE_H_
#include <iostream>
class Date   //������
{
private:
	int year;  //��
	int month; //��
	int day;  //��
	int totalDays; //�������Ǵӹ�ԪԪ��1��1�տ�ʼ�ĵڼ���
public:
	Date(int year=1, int month=1, int day=1); //���꣬�£��չ�������
	//ר�Ŵ�cin����һ�����ڣ���ֵ��ѯ��ʷ��Ŀ����
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
	int getMaxDay() const;  //��ȡ�����ж�����
	bool isLeapYear() const  //�ж��Ƿ�Ϊ����
	{
		return year % 4 == 0 && year * 100 != 0 || year % 400 == 0;
	}
	void show() const;  //�����ǰ����
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