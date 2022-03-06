#include <iostream>

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
		{
			std::cout << "ElementC:\t" << this << std::endl;
		}
		
		~Element()
		{
		
			std::cout << "ElementD:\t" << this << std::endl;
		}
		bool is_leaf()const { return pLeft == pRight; }
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* get_root()const
	{
		return Root;
	}
	Tree()
	{
		this->Root = nullptr;
		std::cout << "TreeC:\t" << this << std::endl;
	}
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			insert(*it, Root);
		}
	}
	Tree(const Tree& other) : Tree()
	{
		copy(other.Root);
		std::cout << "CopyConstr:\t " << this << std::endl;
	}
	~Tree()
	{
		clear(Root);
		std::cout << "TreeD:\t" << this << std::endl;
	}
	void insert(int Data) { return insert(Data, Root); }
	void print()const { print(Root); std::cout << std::endl; }
	void copy(Element* Root)
	{
		if (Root == nullptr)return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
	}
	int minValue()const { return minValue(Root); }
	int maxValue()const { return maxValue(Root); }
	int size()const { return size(Root); }
	int sum()const { return sum(Root); }
	double avg()const { return (double)sum(Root) / size(Root); }
	void clear()
	{ 
		clear(Root); 
		Root = nullptr;
	}
	void erase(int Data) { erase(Data, Root); }
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		std:: cout << Root->Data << "\t";
		print(Root->pRight);
	}
	int minValue(Element* Root)const
	{
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int size(Element* Root)const
	{
		return Root == nullptr ? 0 : size(Root->pLeft) + size(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (size(Root->pLeft) > size(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
};

class UniqueTree : public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if(Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK
int main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	/*int n;
std::cout << "Введите размер дерева: "; std::cin >> n;
Tree tree;
for (int i = 0; i < n; i++)
{
	tree.insert(rand() % 100);
}
tree.print();
std::cout << std::endl;
std::cout << tree.size() << std::endl;*/
#endif // BASE_CHECK

	Tree tree = { 50, 25, 75, 16, 32, 64, 80 };
	tree.print();
	int value; 
	std::cout << "Enter remove element: "; std::cin >> value;
	tree.erase(value);
	tree.print();
}






















/*
*	Если у какого то элемента нет леврнр или правого потомка то кго соответствующий указатель будет указывать на ноль

		Удаление жэлементов из дерева.
	1. У удаляемого элемента нет потомков.
	2. У удаляемого элемента есть потомки.
	Элемент не имеющий потомков называют "Листком" 
*/