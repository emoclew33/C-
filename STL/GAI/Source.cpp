#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
#include <algorithm>
#include<Windows.h>

#include"Crime.h"

#define del "\n------------------------------------------------------------------\n"


void add(std::map<std::string, std::list<Crime>>& base);
void print(const std::map<std::string, std::list<Crime>>& base);
void print(const std::map<std::string, std::list<Crime>>& base, const std::string& licence_plate);
void print(const std::map<std::string, std::list<Crime>>& base, const std::string& first_plate, const std::string& last_plate);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
void load(std::map<std::string, std::list<Crime>>& base, const std::string& filename);

void main()
{
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::map<std::string, std::list<Crime>> base/* =
	{
		{"a777km", {Crime(1, "улица Ленина"), Crime(2, "ул. Фрунзе")}},
		{"a557ab", {Crime(5, "ул. Космонавтов")}},
		{"a001a", {Crime(4, "перекресток Ленина и Октябрьской"), Crime(3, "ул. Октябрьская")}}
	}*/;
	load(base, "base.txt");
	load(base, "base.txt");
	load(base, "base.txt");
	//print(base);
	//save(base, "base.txt");
	//add(base);
	print(base);
	/*std::string licence_plate;
	std::cout << "Введите номер ТС:"; std::cin >> licence_plate;
	print(base, licence_plate);*/
	std::string first, last;
	std::cout << "ВВедите начальный номерной знак: "; std::cin >> first;
	std::cout << "ВВедите конечный номерной знак: "; std::cin >> last;
	print(base, first, last);
	
}

void add(std::map<std::string, std::list<Crime>>& base)
{
	std::string licence_plate;
	int id;
	std::string place;
	std::cout << "Введите номер автомобиля: "; std::cin >> licence_plate;
	std::cout << "Введите правонарушение (номер статьи): "; std::cin >> id;
	std::cout << "Введите место проишествия: ";
	std::cin.clear();
	std::cin.ignore();
	std::getline(std::cin, place);
	//base[licence_plate].push_back(Crime(id, place));
	std::map<std::string, std::list<Crime>>::iterator it = base.find(licence_plate);
	if (it != base.end())
	{
		it->second.push_back(Crime(id, place));
	}
	else
	{
		base.insert(std::pair<std::string, std::list<Crime>>(licence_plate, { Crime(id, place) }));
	}
}
void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		//cout << std::left;
		std::cout << it->first + ":\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			std::cout << "\t" << *jt << ";\n";
		}
		std::cout << del;
	}
}
void print(const std::map<std::string, std::list<Crime>>& base, const std::string& first_plate, const std::string& last_plate)
{
	try
	{
		for (
			std::map<std::string, std::list<Crime>>::const_iterator it = base.lower_bound(first_plate);
			it != base.upper_bound(last_plate);
			++it
			)
		{
			std::cout << it->first << ":\n";
			for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
			{
				std::cout << *jt << std::endl;
			}
			std::cout << del;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
void print(const std::map<std::string, std::list<Crime>>& base, const std::string& licence_plate)
{
	try
	{
		std::cout << licence_plate << ":\n";
		for (
			std::list<Crime>::const_iterator it = base.at(licence_plate).begin();
			it != base.at(licence_plate).end();
			++it
			)
			std::cout << *it << std::endl;
	}
	catch (...)
	{
		std::cerr << "В базе нет такого номера" << std::endl;
	}
}
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::pair<std::string, std::list<Crime>> i : base)
	{
		fout << i.first << ":\t";
		for (Crime j : i.second)
		{
			fout << j << ", ";
		}
		fout.seekp(-2, std::ios::cur);	//сдвигаем курсор на 2 позиции влево
		fout << ";\n";
	}
	fout.close();
	std::string command = std::string("start notepad ") + filename;
	system(command.c_str());
	//c_str() возвращает C-string (NULL Terminated Line)
}
void load(std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string licence_plate;
			int id;
			std::string place;
			std::string crimes;
			std::getline(fin, licence_plate, ':');
			std::getline(fin, crimes);
			if (crimes.empty())continue;

			char* sz_crimes = new char[crimes.size() + 1]{};
			std::strcpy(sz_crimes, crimes.c_str());
			char sz_delimeters[] = ",;";
			for (char* pch = strtok(sz_crimes, sz_delimeters); pch; pch = strtok(NULL, sz_delimeters))
			{
				//atoi() - ASCII-string to int
				while (*pch == ' ')pch++;//пока строка начинается с символа ' ', смещаем начало строки на 1 сипвол впрваво.
				id = std::atoi(pch);//берем номер правонарушения, преобразуем его в целочисленный формат.
				pch = std::strchr(pch, ' ') + 1;//для того чтобы убрать id из строки, находим пробел в строке и смещаем начао строки на сивол, следующий за пробелом.
				if (
					std::find(base[licence_plate].begin(), base[licence_plate].end(), Crime(id, pch)) 
					== base[licence_plate].end()
					)
					base[licence_plate].push_back(Crime(id, pch));
			}
			delete[] sz_crimes;

			/*if (crimes.find(',') != std::string::npos)
			{
				for (int start = 0, end = crimes.find(','); end != std::string::npos; start = end)
				{
					end = crimes.find(',', start + 1);
					place = crimes.substr(start + 1, end);
					place.erase(0, place.find_first_not_of(' '));
					id = std::stoi(place.substr(0, place.find_first_of(' ')));
					place.erase(0, place.find_first_of(' ') + 1);
					base[licence_plate].push_back(crime(id, place));
				}
			}
			else
			{
				id = std::stoi(crimes.substr(0, crimes.find_first_of(' ')));
				crimes.erase(0, crimes.find_first_of(' '));
				base[licence_plate].push_back(crime(id, crimes));
			}*/
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << std::endl;
	}
}


/*
*		 [] - Оператор квадратные скобки, принимает ключ, и возвращает значение соответствующее этому ключу.
*	Если заданого ключа нет в контейнере, то оператор квадратные скобки добавляет новый элемент с заданым ключом.
*		Метод .at() - метод at принимет ключ и возвращает значение соответствующее заданому ключу.
	Если заданый ключ отсутствует в контейнере, то метод at()	бросает исключение out_of_range exception
	Как оператор квадратные скопки [], так и .at() возвращают значение по ссылке (&). Метод atявляется константным, поэтому может вызван для константного контейнера.
	Оператор   [] не возможно вызвать для кконстантного контейнера. По-скольку нет константного кземпляра этого оператора.
	
*/













