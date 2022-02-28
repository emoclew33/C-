#include "Element.h"

Element::Element(int Data, Element* pNext) :Data(Data), pNext(pNext)
{
	count++;
}
Element::~Element()
{
	count--;
}
int Element::count = 0;