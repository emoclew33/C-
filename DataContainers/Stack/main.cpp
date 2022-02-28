#include "stdfix.h" 
#include "Element.h"
#include "Element.cpp"

template<typename T>
class Stack
{
    Element<T>* Head;
    size_t size;
    void pop_front();
public:
    Stack();
    ~Stack();
    void push(T Data);
    void pop();
    T top();
    bool empty();
};



int main() {
  
  setlocale(LC_ALL,"rus");
  Stack<int> steсk; 
 
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


template<typename T>Stack<T>::Stack()
{
    Head = nullptr;
    size = 0;
}
template<typename T>void Stack<T>::pop_front()
{
    if (Head == nullptr)return;
	Element<T>* Erased = Head;
	Head = Erased->pNext;
	delete Erased;
	size--;
}

template<typename T>Stack<T>::~Stack(){ while (Head)pop_front(); }

template<typename T>void Stack<T>::push(T Data)
{
    if(Head == nullptr)
    {
        Head = new Element<T>(Data, Head);
	    size++;
    }
    else
    {
        Element<t>* Temp = Head;
        while(Temp->pNext)Temp = Temp->pNext;
        Temp->pNext = new Element<T>(Data);
        size++;
    }
}

template<typename T>void Stack<T>::pop()
{
    if (Head == nullptr)return;
	if (Head->pNext == nullptr)return pop_front();
	Element<T>* Temp = Head;
	while (Temp->pNext->pNext)Temp = Temp->pNext;
	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}

template<typename T>T Stack<T>::top()
{
    if (Head == nullptr)return 0;
    Element<T>* Temp = Head;
    while(Temp->pNext)Temp = Temp->pNext;
    return Temp->Data;
}
template<typename T>bool Stack<T>::empty()
{
    if (Head == nullptr)return false;
    return true;
}

