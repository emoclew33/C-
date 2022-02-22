#pragma once
#include "stdfix.h"

template <typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
		friend class Iterator;
		friend class ReverseIterator;
	}*Head, * Tail;
	size_t size;
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr);
		~BaseIterator();
		bool operator!=(const BaseIterator& other)const;
		bool operator==(const BaseIterator& other)const;
		const T& operator*()const;
		operator bool()const;
	};
public:
	class ConstIterator : public BaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReversIterator : public BaseIterator
	{
	public:
		ConstReversIterator(Element* Temp = nullptr);
		~ConstReversIterator();
		ConstReversIterator& operator++();
		ConstReversIterator operator++(int);
		ConstReversIterator& operator--();
		ConstReversIterator operator--(int);
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		T& operator*();
	};
	class ReversIterator : public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp);
		~ReversIterator();
		T& operator*();
	};
	Iterator begin();
	Iterator end();
	ReversIterator rbegin();
	ReversIterator rend();
	const ConstIterator const cbegin();
	const ConstIterator const cend();
	const ConstReversIterator const crbegin();
	const ConstReversIterator const crend();

	List();
	List(const std::initializer_list<T>& il);
	~List();

	//**************	adding elements		****************

	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, size_t index);

	//**************	remove elements		****************

	void pop_front();
	void pop_back();
	void erase(size_t index);

	//**************	methods		****************

	void print() const;
	void reverse_print() const;
};