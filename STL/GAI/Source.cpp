#include <iostream>
#include <string>
#include <map>
#include <list>
#include <conio.h>
#include <conio.h>>
#include <Windows.h>

void add_protocol(std::map < std::string, std::list<std::string>>& base) {
	std::cout << "Добавить протокол:" << std::endl;
	std::cout << "------------------" << std::endl;
	std::pair < std::string, std::list<std::string>> temp;
	std::cout << "Введите номер ТС:" << std::endl; std::getline(std::cin, temp.first);
	std::string tag;
	std::cout << "Нарушение:" << std::endl; std::getline(std::cin, tag);
	temp.second.push_back(tag);
	base.insert(temp);
}

void print(std::map < std::string, std::list<std::string>>& base)
{
	for (std::pair<std::string, std::list<std::string>> i : base)
	{
		std::cout << i.first << "\t";
		for (std::string j : i.second)
		{
			std::cout << j << " ";
		}
	}
}

void main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::map<std::string, std::list<std::string>> gai{};

	add_protocol(gai);
	print(gai);



	print(gai);
}