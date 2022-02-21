#include <iostream>
#include <string>

#define tab "\t"
#define delimetr std::cout << "\n******************************\n";
template <typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev) {}
		~Element() {}
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
		BaseIterator(Element* Temp = nullptr) : Temp(Temp){}
		~BaseIterator() {}
		bool operator!=(const BaseIterator& other)const { return this->Temp != other.Temp; }
		bool operator==(const BaseIterator& other)const { return this->Temp == other.Temp; }
		const T& operator*()const { return Temp->Data; }
		operator bool()const { return Temp; }
	};
public:
	class ConstIterator : public BaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) : BaseIterator(Temp) {}
		~ConstIterator() {}
		ConstIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator& operator++(int)
		{
			ConstIterator old = *this;
			++* this;
			return old;
		}
		ConstIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator& operator--(int)
		{
			ConstIterator old = *this;
			--* this;
			return old;
		}
	};
	class ConstReversIterator : public BaseIterator
	{
	public:
		ConstReversIterator(Element* Temp = nullptr) : BaseIterator(Temp) {}
		~ConstReversIterator() {}
		ConstReversIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReversIterator operator++(int)
		{
			ConstReversIterator old = *this;
			++* this;
			return old;
		}
		ConstReversIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstReversIterator operator--(int)
		{
			ConstReversIterator old = *this;
			--* this;
			return old;
		}
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*() { return BaseIterator::Temp->Data; }
	};
	class ReversIterator : public ConstReversIterator
	{
	public:
		ReversIterator(Element* Temp) : ConstReversIterator(Temp) {}
		~ReversIterator() {}
		T& operator*() { return BaseIterator::Temp->Data; }
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

void main()
{
	setlocale(LC_ALL, "");
	/*List<int> list = { 3, 5, 8, 13, 21 };
	for (List<int>::ConstIterator it = list.cbegin(); it; ++it)
	{
		std::cout << *it << tab;
	}*/

	/*List<double> d_list = { 2.5, 3.14, 5.2, 8.3};
	for (double i : d_list)std::cout << i << tab; std::cout << std::endl;
	for (List<double>::ReversIterator it = d_list.rbegin(); it; ++it)
	{
		std::cout << *it << tab;
	}*/

	List<std::string> s_list = { "Have", "a", "nice ", "day" };
	for(std::string i : s_list)std::cout << i << tab;
	std::cout << std::endl;
	for (List<std::string>::ReversIterator it = s_list.rbegin(); it!=s_list.rend(); ++it)
	{
		std::cout << *it << tab;
	}
}

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












// ************************************		ПЛЮСЫ	 ****************************************	
// 
//Двусвязный список это набор элементов в произвольных областях памяти которая хранит 
// адрес не только следующего но предыдущего элемента
// что позволяет, перемещатся по списку в обоих направлениях, как от начала до конца, 
// так и от конца к началу.
// Что теоретически в 2 раза уменьшает время доступа к элументам списка
// следовательно в 2 раза повышая производительность при доступе к элементам списка.
// 
// ************************************		МИНУСЫ		*************************************
// 
// Но двусвязный список занимает больше памяти, чем односвязный
// 
// ******************************************************************************************
// 
// у двухсвязного списка есть не только голова которая дает прямой доступ к началу списка,
//  но и хвост - который дает доступ к последнему элементу списка
// когда двузсвящный список пуст, его голова и хвост указывают на 0
// Когда в списке появдяется первый элемент, он является единственным элементом списка 
// и это элемент одновременно является и первым и последним элементом списка с какой стороны не посмотреть
// 
// *****************************************************************************************
// Голова и хвост могут содержать один и тот же адресс в 2-х случаях:
//	-список пуст
//	-в списке 1 элемент
// Ткаой список еще называют	-	 ВЫРОЖДЕННЫМ
// *****************************************************************************************
//