#pragma once
#ifndef ARRAY_H
#define ARRAY_H
#include <cassert>
// 数组类模版，动态数组
template <class T>
class Array
{
private:
	T* list; //T类型，用于存放动态分配的数组内存首地址
	int size;  //数组大小(元素个数)
public:
	Array(int sz = 50);  //构造函数
	Array(const Array<T>& a); //赋值构造函数
	~Array(); //析构函数
	Array<T>& operator = (const Array<T>& rhs);
	T& operator [] (int i);  //重载"[]"使Array对象可以起到C++普通数组的作用
	const T& operator [] (int i) const; //"[]"运算符针对const重载
	operator T* ();//重载T*类型的转换，使Array对象可以 起到对C++普通数组的作用
	operator const T* () const; //使T*类型转换操作符针对const的重载
	int getSize() const;  //取数组的大小
	void resize(int sz);// 修改数组的大小
};

//构造函数
template<class T>
Array<T>::Array(int sz)
{
	assert(sz >= 0);  //元素大非负
	size = sz; 
	list = new T[size];  //动态分配size个T类型的元素空间
}

//析构函数
template <class T>
Array<T>::~Array()
{
	delete[] list;
}
//复制构造函数
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

//重载“=”运算符，将对象rhs赋值给本 对象，实现对象之间的整体赋值
template <class T>
Array<T>& Array<T>::operator=(const Array<T>& rhs)   //第一个Array是数组类型返回值，第二个为取Array类中
{
	if (&rhs != this)
	{
		//如果本对象中数组大小与rhs大小不通过，则删除数组原有内存，然后重新分配
		if (size != rhs.size)
		{
			delete[] list;
			size = rhs.size;
			list = new T[size]; //重新分配size个元素的内存
		}
		//从对象rhs复制到数组元素到本对象
		for (int i = 0; i < size; i++)
		{
			list[i] = rhs.list[i];
		}
	}
	return *this;
}
//重载下标运算符,实现与普通数组一样通过下标访问元素，并且具有越界检查功能
template <class T>
T& Array<T>::operator[] (int n)
{
	assert(n >= 0 && n < size);  //检查下标是否越界
	return list[n];  //返回下标为n的数组元素
}


template <class T>
const T& Array<T>::operator[] (int n) const
{
	assert(n >= 0 && n < size);  //检查下标是否越界
	return list[n];  //返回下标为n的数组元素
}

//重载指针转换运算符，将Array类的对象名转换为T类型的指针，
//指向当前对象中的私有数组，
//因而可以像普通数组首地址一样使用Array类的对象名
template<class T>
Array<T>::operator T* ()
{
	return list;  //返回当前对象中私有数组的首地址
}
template<class T>
Array<T>::operator const T* () const
{
	return list;  //返回当前对象中私有数组的首地址
}

//取当前数组的大小
template <class T>
int Array<T>::getSize() const
{
	return size;
}
//将数组大小修改为sz
template <class T>
void Array<T>::resize(int sz)
{
	assert(sz >= 0); //检查sz是否非负
	if (sz == size) //检查指定的大小与原有大小一样，什么也不做
		return;
	T* newlist = new T[size]; //申请新的数组内存
	int n = (sz < size) ? sz : size; //将sz与size较小的一个值赋值给n
	//将原有数组中前n个元素复制到新数组中
	for (int i = 0; i < n; i++)
	{
		newlist[i] = list[i];
	}
	delete[] list;  //删除原数组
	list = newlist; //使list指向新数组
	size = sz;

}




#endif // !ARRAY_H
