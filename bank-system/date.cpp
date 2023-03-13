/*������ʵ�ֺ���*/
#include "date.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>  //��׼���ͷ,��ͷ�ļ��Ǵ�������һ����
using namespace std;
namespace  //ʹ��namespaceʹ����Ķ���ֻ���ڵ�ǰ�ļ�����Ч
{
	//�洢ƽ����ÿ����1��֮ǰ�ж����죬Ϊ����getMaxDay������ʵ�֣�
	const int DAYS_BEFORE_MONTH[] = { 0,31,59,90,120,151,181,212,143,273,304,334,365 };
}

Date::Date(int year, int month, int day) :year(year), month(month), day(day)
{
	if (day <= 0 || day > getMaxDay())
	{
		throw runtime_error("Invalid date"); //Date�����쳣��ֱ��ʹ�ñ�׼����⹹���쳣�׳�
	}
	//��һ��Ϊ�˼�����������������·ݺ������������Ҫ��һ
	int years = year - 1;
	//����������
	totalDays = years * 365 + years / 4 - years / 100 + years / 400 + DAYS_BEFORE_MONTH[month - 1] + day;
	//��������겢���·ݴ�Լ2��������+1
	if (isLeapYear() && month > 2)
		totalDays++;
}
//���������������
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
//���Date����-��-��
void Date::show() const
{
	cout << getYear() << "-" << getMonth() << "-" << getDay();
}
istream& operator>>(istream& in, Date& date) //istreamͨ��������
{
	int year, month, day;
	char c1, c2;
	cout << "���������ʽΪ:2019-01-01" << endl;
	in >> year >> c1 >> month >> c2 >> day;
	//����������жϣ���û�а��ո�ʽ�����ش���
	if (c1 != '-' || c2 != '-')
		//����������ʱ�����쳣��
		throw runtime_error("Bad time format"); 

	//�����õ���ȷ���ڷ��ظ�date��ָ��
	date = Date(year, month, day);

	//�����û������� �˴�
	return in;  
}
//�������������ʹdate���ձ�׼��ʽ���
ostream& operator << (ostream& out, const Date& date) //ostreamͨ�������
{
	out << date.getYear() << "-" << date.getMonth() << "-" << date.getDay();
	return out;
}