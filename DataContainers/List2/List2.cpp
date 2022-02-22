#include "List2.h"

//**************	List		****************

template<typename T>typename List<T>::Iterator List<T>::begin() { return Head; }
template<typename T>typename List<T>::Iterator List<T>::end() { return nullptr; }
template<typename T>typename List<T>::ReversIterator List<T>::rbegin() { return Tail; }
template<typename T>typename List<T>::ReversIterator List<T>::rend() { return nullptr; }
template<typename T>typename const List<T>::ConstIterator const List<T>::cbegin() { return Head; }
template<typename T>typename const List<T>::ConstIterator const List<T>::cend() { return nullptr; }
template<typename T>typename const List<T>::ConstReversIterator const List<T>::crbegin() { return Tail; }
template<typename T>typename const List<T>::ConstReversIterator const List<T>::crend() { return nullptr; }

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) : List()
{
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>List<T>::~List() { while (Tail)pop_back(); }

//**************	adding elements		****************

template<typename T>
void List<T>::push_front(T Data)
{
	(Head == nullptr && Tail == nullptr)
		? Head = Tail = new Element(Data)
		: Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template<typename T>
void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr) return push_front(Data);
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T>
void List<T>::insert(T Data, size_t index)
{
	if (index > size)return;
	if (index == 0)return push_front(Data);
	if (index == size)return push_back(Data);
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; i++) Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - 2 - index; i++) Temp = Temp->pPrev;
	}
	Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	Temp->pPrev = Temp->pPrev->pNext;
	size++;
}

//**************	remove elements		****************

template<typename T>
void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template<typename T>
void List<T>::pop_back()
{
	if (Head == nullptr && Tail == nullptr || Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template<typename T>
void List<T>::erase(size_t index)
{
	if (index > size)return;
	if (Head == nullptr && Tail == nullptr || Head == Tail || index == 0)return pop_front();
	if (index == size - 1)return pop_back();
	Element* Temp;
	if (index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - 2 - index; i++)Temp = Temp->pPrev;
	}
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	delete Temp;
	size--;
}

//**************	methods		****************

template<typename T>
void List<T>::print() const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		std::cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
}
template<typename T>
void List<T>::reverse_print() const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		std::cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
	}
}

//**************	Element		****************

template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) : Data(Data), pNext(pNext), pPrev(pPrev) {}
template<typename T>List<T>::Element::~Element() {}

//**************	BaseIterator		****************

template<typename T>List<T>::BaseIterator::BaseIterator(Element* Temp) : Temp(Temp) {}
template<typename T>List<T>::BaseIterator::~BaseIterator() {}

template<typename T>List<T>::BaseIterator::operator bool()const { return Temp; }
template<typename T>bool List<T>::BaseIterator::operator==(const BaseIterator& other)const { return this->Temp == other.Temp; }
template<typename T>bool List<T>::BaseIterator::operator!=(const BaseIterator& other)const { return this->Temp != other.Temp; }
template<typename T>const T& List<T>::BaseIterator::operator*()const { return Temp->Data; }

//**************	ConstIterator		****************

template<typename T>List<T>::ConstIterator::ConstIterator(Element* Temp) : BaseIterator(Temp) {}
template<typename T>List<T>::ConstIterator::~ConstIterator() {}

template<typename T>
typename List<T>::ConstIterator::ConstIterator& List<T>::ConstIterator::operator++()
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}
template<typename T>
typename List<T>::ConstIterator::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	++* this;
	return old;
}
template<typename T>
typename List<T>::ConstIterator::ConstIterator& List<T>::ConstIterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>
typename List<T>::ConstIterator::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	--* this;
	return old;
}

//**************	ConstReversIterator		****************

template<typename T>List<T>::ConstReversIterator::ConstReversIterator(Element* Temp) : BaseIterator(Temp) {}
template<typename T>List<T>::ConstReversIterator::~ConstReversIterator() {}

template<typename T>
typename List<T>::ConstReversIterator::ConstReversIterator& List<T>::ConstReversIterator::operator++()
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>
typename List<T>::ConstReversIterator::ConstReversIterator List<T>::ConstReversIterator::operator++(int)
{
	ConstReversIterator old = *this;
	++* this;
	return old;
}
template<typename T>
typename List<T>::ConstReversIterator::ConstReversIterator& List<T>::ConstReversIterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}
template<typename T>
typename List<T>::ConstReversIterator::ConstReversIterator List<T>::ConstReversIterator::operator--(int)
{
	ConstReversIterator old = *this;
	--* this;
	return old;
}

//**************	Iterator		****************

template<typename T>List<T>::Iterator::Iterator(Element* Temp) : ConstIterator(Temp) {} 
template<typename T>List<T>::Iterator::~Iterator() {}				

template<typename T>T& List<T>::Iterator::operator*() { return BaseIterator::Temp->Data; }

//**************	ReversIterator		****************

template<typename T>List<T>::ReversIterator::ReversIterator(Element* Temp) : ConstReversIterator(Temp) {}
template<typename T>List<T>::ReversIterator::~ReversIterator() {}

template<typename T>T& List<T>::ReversIterator::operator*() { return BaseIterator::Temp->Data; }

