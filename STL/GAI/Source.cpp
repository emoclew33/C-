#include <iostream>
#include <string>
#include <map>
#include <list>
#include <Windows.h>
#include <fstream>

#include "Crime.h"

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map < std::string, std::list<Crime>>& base);
void add(std::map < std::string, std::list<Crime>>& base);

void main()
{
	setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::map < std::string, std::list<Crime>> base =
	{
		{"a777km", {Crime(1, "Улица Ленина"), Crime(2, "улица Фрундзе")}},
		{"a557ab", {Crime(5, "Улица Космонавтов")}},
		{"a001a", {Crime(4, "перекресток Ленина"), Crime(2, "улица октябрьская")}},
	};
	print(base);
	add(base);
	print(base);
	save(base);

}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		std::cout << it->first + ":\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{

			std::cout << "\t" << *jt << ";\n";
		}
		std::cout << "---------------------------------------------\n";
	}
}
void save(const std::map < std::string, std::list<Crime>>& base)
{
	std::string path;
	std::cout << "Введите имя файла:"; std::cin >> path;
	std::ofstream fout(path);
	for (const std::pair<std::string, std::list<Crime>>& i : base)
	{
		fout << i.first + ":\t";
		for (const Crime& j : i.second)
		{

			fout << j << " ";
		}
		fout << "\n";
	}
	fout.close();
}
void add(std::map < std::string, std::list<Crime>>& base)
{
	size_t id;
	std::string place, licence_plate;
	std::cout << "Введите номер автомобился: "; std::cin >> licence_plate;
	std::cout << "Введите правонарушение(номер статьи): "; std::cin >> id;
	std::cout << "Введите место происшедствия:";
	std::cin.clear();
	std::cin.ignore();
	std::getline(std::cin, place);
	base[licence_plate].push_back(Crime(id, place));
}


/*
*		 [] - Оператор квадратные скобки, принимает ключ, и возвращает значение соответствующее этому ключу.
*	Если хаданого ключа нет в еонтейнера, то оператор квадратные скобки добавляет новый элемент с заданым ключом.
*		Метод .at() - метод at принимет ключ и возвращает значение соответствующее заданому ключу.
	Если заданый ключ отсутствует в контейнере, то метод at()	бросает исключение out_of_range exception
	Как оператор квадратные скопки [], так и .at() возвращают значение по ссылке (&). Метод atявляется константным, поэтому может вызван для константного контейнера.
	Оператор   [] не возможно вызвать для кконстантного контейнера. По-скольку нет константного кземпляра этого оператора.
	
*/













