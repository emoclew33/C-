#include "Element.h"

template<typename T>Element<T>::Element(T Data, Element<T>* pNext) :Data(Data), pNext(pNext)
{
	count++;
}
template<typename T>Element<T>::~Element()
{
	count--;
}
template<typename T>int Element<T>::count = 0;