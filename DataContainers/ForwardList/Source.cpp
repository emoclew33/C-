#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;	//�������� ��������
	Element* pNext;//����� ���������� ��������
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstrcutor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestrcutor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList//����������� (����������������) ������
{
	Element* Head;	//������ ������ - ��������� �� ��������� ������� ������.
public:
	ForwardList()
	{
		Head = nullptr;//���� ������ ��������� �� 0, �� ������ ����.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//					Addigng elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);//������� ����� ������� � �������� � ���� �������� Data
		New->pNext = Head;	//���������� ����� ������� � ������ ������
		Head = New;	//��������� ������ �� ����� �������
	}

	void push_back(int Data)
	{
		if (Head == nullptr)    return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)    Temp = Temp->pNext; //���� �� 0, ���� �� ����� ������						 	
		Temp->pNext = new Element(Data);
	}
	//					Delete elements:
	void pop_front()
	{
		Element* rmHead = Head;
		Head = Head->pNext;
		delete rmHead;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Element* buff = Temp->pNext;
			if (buff->pNext == NULL) break;
			Temp = Temp->pNext;
		}

		delete Temp->pNext;
		Temp->pNext = nullptr;
	}

	//					Methods:
	void print()const
	{
		int a = 2;
		int* pa = &a;
		Element* Temp = Head;	//Temp - ��� ��������.
		//�������� - ��� ���������, ��� ������ �������� ����� �������� ������ 
		//� ��������� ��������� ������.
		while (Temp)//���� �������� �������� ��������� �����.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//������� �� ��������� �������
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 10);
	}
	list.print();
	list.push_back(11);
	list.print();
	list.pop_front();
	list.pop_back();
	list.print();
}