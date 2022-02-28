#include <iostream>

class Tree
{
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
		friend class Tree;
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
	~Tree()
	{
		std::cout << "TreeD:\t" << this << std::endl;
	}

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
};

int main()
{
	setlocale(LC_ALL, "");
	int n;
	std::cout << "Введите размер дерева: "; std::cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.get_root());
	}
	tree.print(tree.get_root());
	std::cout << std::endl;
}






















/*
*	Если у какого то элемента нет леврнр или правого потомка то кго соответствующий указатель будет указывать на ноль



*/