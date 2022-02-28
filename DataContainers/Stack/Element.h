#pragma once 
#include "stdfix.h"


template<typename T>class Element
{
	T Data;	//Значение элемента
	Element<T>* pNext;//указатель на шаблонный элемент
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr);
	~Element();
    friend class Stack;
};
