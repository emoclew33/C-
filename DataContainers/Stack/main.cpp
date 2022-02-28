#include "stdfix.h" 
#include "Element.h"
#include "Element.cpp"


class Stack
{
    Element* Head;
    size_t size;
    void pop_front();
public:
    Stack();
    ~Stack();
    void push(int Data);
    void pop();
    int top();
    bool empty();
};



int main() {
  
 
  Stack steсk; 
 
  std::cout << "Enter size stack: " << std::endl; 
  int size; std::cin >> size;
  std::cout << "Enter numbers: " << std::endl; 
  for(int i = 0; i < size; i++)
  {
      int temp; std::cin >> temp;
      steсk.push(temp);
  }
  if (steсk.empty()) std::cout << "Stack is not empty ";  
 
  std::cout << "Top element of the stack: " << steсk.top() << std::endl;
  std::cout << "Remove the top element" << std::endl;
 
  steсk.pop();
  std::cout << "Top element of the stack: : " << steсk.top(); 
  return 0;
}


Stack::Stack()
{
    Head = nullptr;
    size = 0;
}
void Stack::pop_front()
{
    if (Head == nullptr)return;
	Element* Erased = Head;
	Head = Erased->pNext;
	delete Erased;
	size--;
}

Stack::~Stack(){ while (Head)pop_front(); }

void Stack::push(int Data)
{
    if(Head == nullptr)
    {
        Head = new Element(Data, Head);
	    size++;
    }
    else
    {
        Element* Temp = Head;
        while(Temp->pNext)Temp = Temp->pNext;
        Temp->pNext = new Element(Data);
        size++;
    }
}

void Stack::pop()
{
    if (Head == nullptr)return;
	if (Head->pNext == nullptr)return pop_front();
	Element* Temp = Head;
	while (Temp->pNext->pNext)Temp = Temp->pNext;
	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}

int Stack::top()
{
    if (Head == nullptr)return 0;
    Element* Temp = Head;
    while(Temp->pNext)Temp = Temp->pNext;
    return Temp->Data;
}
bool Stack::empty()
{
    if (Head == nullptr)return false;
    return true;
}

