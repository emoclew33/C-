#include <iostream>

#define tab "\t"
#define delimetr std::cout << "\n******************************\n";

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev) {}
		~Element() {}
		friend class List;
		friend class Iterator;
		friend class ReverseIterator;
	}*Head, * Tail;
	size_t size;
public:
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr) : Temp(Temp) {}
		virtual ~BaseIterator() {}

		//**************	BaseIterator operators		****************

		virtual int& operator*() { return Temp->Data; }
		bool operator==(const BaseIterator& other) const { return this->Temp == other.Temp; }
		bool operator!=(const BaseIterator& other) const { return this->Temp != other.Temp; }
		operator bool()const { return Temp; }
	};
	class Iterator : public BaseIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : BaseIterator(Temp) {}
		~Iterator() {}

		//**************	Iterator operators		****************

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator& operator++(int)
		{
			Iterator old = *this;
			//Temp = Temp->pNext;
			++* this;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator& operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
	};
	class ReverseIterator : public BaseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : BaseIterator(Temp) {}
		~ReverseIterator() {}

		//**************	ReverseIterator operators		****************

		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator& operator++(int)
		{
			ReverseIterator old = *this;
			++* this;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator& operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
	};
	class ConstIterator : public Iterator
	{
	public:
		ConstIterator(Element* Temp) : Iterator(Temp) {}
		~ConstIterator() {}
		const int& operator*()const { return Temp->Data; }
	};
	class ConstReverseIterator : public ReverseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) : ReverseIterator(Temp) {}
		~ConstReverseIterator() {}
		const int& operator*() const { return Temp->Data; }
	};
	Iterator		begin() { return Head; }
	Iterator		end() { return nullptr; }
	ReverseIterator rbegin() { return Tail; }
	ReverseIterator rend() { return nullptr; }
	const ConstIterator const cbegin() { return Head; }
	const ConstIterator const cend() { return nullptr; }
	const ConstReverseIterator const crbegin() { return Tail; }
	const ConstReverseIterator const crend() { return nullptr; }
	List()
	{
		Head = Tail = nullptr;
		size = 0;
	}
	List(const std::initializer_list<int>& il) : List()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	~List() { while (Tail)pop_back(); }

	//**************	adding elements		****************

	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Element* New;
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr) return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Data, size_t index)
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

	void pop_front()
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
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr || Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	void erase(size_t index)
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

	void print() const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			std::cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
	}
	void reverse_print() const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			std::cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	List list = { 3, 5, 8, 13, 21 };
	for (List::ConstIterator it = list.cbegin(); it; ++it)
	{
		std::cout << *it << tab;
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