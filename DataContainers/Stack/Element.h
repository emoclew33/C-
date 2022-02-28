#pragma once 
#include "stdfix.h"


class Element
{
	int Data;	//Значение элемента
	Element* pNext;//указатель на шаблонный элемент
	static int count;
public:
	Element(int Data, Element* pNext = nullptr);
	~Element();
    friend class Stack;
};
