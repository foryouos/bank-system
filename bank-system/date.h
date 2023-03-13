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
	

	//��ȡDate�������
	int getYear() const
	{
		return year;
	}
	//��ȡDate�����·�
	int getMonth() const
	{
		return month;
	}
	//��ȡDate������
	int getDay() const
	{
		return day;
	}
	//��ȡDate���µ�����
	int getMaxDay() const; 
	// �ж�Date�����Ƿ�������
	bool isLeapYear() const  //�ж��Ƿ�Ϊ����
	{
		return year % 4 == 0 && year * 100 != 0 || year % 400 == 0;
	}
	//���Date����
	void show() const; 
	//���Data�ӹ�ԪԪ��1��1�յ�Ŀǰdate������
	int distance(const Date& date) const
	{
		return totalDays - date.totalDays;
	}
	//����Date֮ǰ�ġ�-���ţ��ù�ԪԪ�굽Ŀǰ���������
	int operator-(const Date& date) const
	{
		return totalDays - date.totalDays;
	}
	//����Date֮��ġ�<"�ţ�����ԶԪ�굽Ŀǰdate�����ڼ���
	bool operator<(const Date& date) const
	{
		return totalDays < date.totalDays;
	}
};
//����Date�����룬��ʽ�����ڸ�ʽ��year-month-day
std::istream& operator >>(std::istream& in, Date& date);
//����Date�����,��ʽ�����ڸ�ʽ��year-month-day
std::ostream& operator<<(std::ostream& out, const Date& date);


#endif // !_DATE_H_