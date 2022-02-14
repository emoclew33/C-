#include <iostream>
using namespace std;
#define tab "\t"
#define delimetr cout << "\n******************************\n";
  

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
	}*Head, * Tail;
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
	}
	~List() { while (Head)pop_front(); }	//- Heap error

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
			for (int i = size - 1; i > index; i--) Temp = Temp->pPrev;
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
			for (int i = size - 1; i > index; i--)Temp = Temp->pPrev;
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		Temp = nullptr;
		size--;
	}

	//**************	methods		****************
	
	void print() const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	void reverse_print() const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev) 
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;

	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	delimetr
	list.reverse_print();
	delimetr
	list.insert(222222, 3);
	list.reverse_print();
	delimetr
	list.erase(3);
	list.reverse_print();
}











// ***************************************************************************	ПЛЮСЫ
//Двусвязный список это набор элементов в произвольных областях памяти которая хранит 
// адрес не только следующего но предыдущего элемента
// что позволяет, перемещатся по списку в обоих направлениях, как от начала до конца, 
// так и от конца к началу.
// Что теоретически в 2 раза уменьшает время доступа к элументам списка
// следовательно в 2 раза повышая производительность при доступе к элементам списка.
// 
// ***************************************************************************	МИНУСЫ
// Но двусвязный список занимает больше памяти, чем односвязный
// 
// *************************************************************************** 
// 
// у двухсвязного списка есть не только голова которая дает прямой доступ к началу списка,
//  но и хвост - который дает доступ к последнему элементу списка
// когда двузсвящный список пуст, его голова и хвост указывают на 0
// Когда в списке появдяется первый элемент, он является единственным элементом списка 
// и это элемент одновременно является и первым и последним элементом списка с какой стороны не посмотреть
// 
// ***************************************************************************
// Голова и хвост могут содержать один и тот же адресс в 2-х случаях:
//	-список пуст
//	-в списке 1 элемент
// Ткаой список еще называют	-	 ВЫРОЖДЕННЫМ
// ***************************************************************************
//