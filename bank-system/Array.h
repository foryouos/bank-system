#pragma once
#ifndef ARRAY_H
#define ARRAY_H
#include <cassert>
// ������ģ�棬��̬����
template <class T>
class Array
{
private:
	T* list; //T���ͣ����ڴ�Ŷ�̬����������ڴ��׵�ַ
	int size;  //�����С(Ԫ�ظ���)
public:
	Array(int sz = 50);  //���캯��
	Array(const Array<T>& a); //��ֵ���캯��
	~Array(); //��������
	Array<T>& operator = (const Array<T>& rhs);
	T& operator [] (int i);  //����"[]"ʹArray���������C++��ͨ���������
	const T& operator [] (int i) const; //"[]"��������const����
	operator T* ();//����T*���͵�ת����ʹArray������� �𵽶�C++��ͨ���������
	operator const T* () const; //ʹT*����ת�����������const������
	int getSize() const;  //ȡ����Ĵ�С
	void resize(int sz);// �޸�����Ĵ�С
};

//���캯��
template<class T>
Array<T>::Array(int sz)
{
	assert(sz >= 0);  //Ԫ�ش�Ǹ�
	size = sz; 
	list = new T[size];  //��̬����size��T���͵�Ԫ�ؿռ�
}

//��������
template <class T>
Array<T>::~Array()
{
	delete[] list;
}
//���ƹ��캯��
template <class T>
Array<T>::Array(const Array<T>& a)
{
	size = a.size;
	list = new T[size];
	for (int i = 0; i < size; i++)
	{
		list[i] = a.list[i];
	}
}

//���ء�=���������������rhs��ֵ���� ����ʵ�ֶ���֮������帳ֵ
template <class T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)   //��һ��Array���������ͷ���ֵ���ڶ���ΪȡArray����
{
	if (&rhs != this)
	{
		//����������������С��rhs��С��ͨ������ɾ������ԭ���ڴ棬Ȼ�����·���
		if (size != rhs.size)
		{
			delete[] list;
			size = rhs.size;
			list = new T[size]; //���·���size��Ԫ�ص��ڴ�
		}
		//�Ӷ���rhs���Ƶ�����Ԫ�ص�������
		for (int i = 0; i < size; i++)
		{
			list[i] = rhs.list[i];
		}
	}
	return *this;
}
//�����±������,ʵ������ͨ����һ��ͨ���±����Ԫ�أ����Ҿ���Խ���鹦��
template <class T>
T& Array<T>::operator[] (int n)
{
	assert(n >= 0 && n < size);  //����±��Ƿ�Խ��
	return list[n];  //�����±�Ϊn������Ԫ��
}


template <class T>
const T& Array<T>::operator[] (int n) const
{
	assert(n >= 0 && n < size);  //����±��Ƿ�Խ��
	return list[n];  //�����±�Ϊn������Ԫ��
}

//����ָ��ת�����������Array��Ķ�����ת��ΪT���͵�ָ�룬
//ָ��ǰ�����е�˽�����飬
//�����������ͨ�����׵�ַһ��ʹ��Array��Ķ�����
template<class T>
Array<T>::operator T* ()
{
	return list;  //���ص�ǰ������˽��������׵�ַ
}
template<class T>
Array<T>::operator const T* () const
{
	return list;  //���ص�ǰ������˽��������׵�ַ
}

//ȡ��ǰ����Ĵ�С
template <class T>
int Array<T>::getSize() const
{
	return size;
}
//�������С�޸�Ϊsz
template <class T>
void Array<T>::resize(int sz)
{
	assert(sz >= 0); //���sz�Ƿ�Ǹ�
	if (sz == size) //���ָ���Ĵ�С��ԭ�д�Сһ����ʲôҲ����
		return;
	T* newlist = new T[size]; //�����µ������ڴ�
	int n = (sz < size) ? sz : size; //��sz��size��С��һ��ֵ��ֵ��n
	//��ԭ��������ǰn��Ԫ�ظ��Ƶ���������
	for (int i = 0; i < n; i++)
	{
		newlist[i] = list[i];
	}
	delete[] list;  //ɾ��ԭ����
	list = newlist; //ʹlistָ��������
	size = sz;

}




#endif // !ARRAY_H
