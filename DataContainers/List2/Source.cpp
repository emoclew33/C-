#include "stdfix.h"
#include "List2.h"
#include "List2.cpp"

void main()
{
	setlocale(LC_ALL, "");
	

	List<std::string> s_list = { "Have", "a", "nice ", "day" };
	for(std::string i : s_list)std::cout << i << tab;
	std::cout << std::endl;
	for (List<std::string>::ReversIterator it = s_list.rbegin(); it!=s_list.rend(); ++it)
	{
		std::cout << *it << tab;
	}
}


