#include <iostream>
#include <array>
#include <vector>
#include <deque>
#include <set>
#include <map>

#define tab "\t"

//#define ARRAY
//#define VECTOR
//#define DEQUE
//#define SET
#define MAP

void main()
{
	setlocale(LC_ALL, "");
#ifdef ARRAY
	std::array<int, 5> arr = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < arr.size(); i++) { std::cout << arr[i] << _tab; }
#endif // ARRAY
#ifdef VECTOR	
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	for (int i : vec) { std::cout << i << tab; }
	std::cout << "\nSize:		" << vec.size() << std::endl;
	std::cout << "Max size:		" << vec.max_size() << std::endl;
	std::cout << "Capacity:		" << vec.capacity() << std::endl;
	vec.assign({ 1,2,4,8,10,12,14 });
	for (int i : vec)std::cout << i << tab;
	int index; int value; 
	std::cout << "Введите индекс добавляемого значения: "; std::cin >> index;
	std::cout << "Введите значения: "; std::cin >> value;
	//std::vector<int>::const_iterator position = vec.begin() + index;
	vec.insert(vec.begin()+index, value);
	for (int i : vec)std::cout << i << tab;

#endif // VECTOR
#ifdef DEQUE
	std::vector<int> vec;
	std::deque<int> deque;
	vec.push_back(1);
	deque.push_front(1);
#endif // DEQUE
#ifdef SET
	std::set<int> myset = { 50,25,75,16,32,64,80,5,50 };
	for (int i : myset) { std::cout << i << tab; }
	std::cout << std::endl;
	int value;
	std::cout << "Введите добовляемое значение: "; std::cin >> value;
	myset.insert(value);
	for (int i : myset) { std::cout << i << tab; }
	std::cout << "Введите удаляемое значение: "; std::cin >> value;
	myset.erase(value);
	for (int i : myset) { std::cout << i << tab; }
	std::cout << std::endl;
	for (std::set<int>::iterator it = myset.lower_bound(25); it != myset.upper_bound(75); it++)
	{
		std::cout << *it << tab;
	}
	std::cout << std::endl;
	for (std::set<int>::iterator it = myset.find(25); it != myset.find(75); it++)
	{
		std::cout << *it << tab;
	}
#endif // SET
#ifdef MAP
	std::map<int, std::string> week =
	{
		std::pair<int, std::string>(0, "Sunday"),
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(4, "Tursday"),
		{5, "Friday" },
		{6, "Saturday" }
	};
	/*for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); it++)
	{
		std::cout << it->first << tab << it->second << std::endl;
	}*/
	for (std::pair<int, std::string> i : week)
	{
		std::cout << i.first << tab << i.second << std::endl;
	}
	
#endif // MAP


}



















/*		STL -  Standart Template Libary (Стандартная шаблонная библиотека)
*	STL представляет собой набор алгоритмов, контейнеров и прочих сущностей для работы с данными.
*	абсолютно все сущности являются шаблонными, работают с любыми типами данных.
*		
*		Ключевым понятием STL, является контейнер. Контейнер - это обьект, который организует хранение других обьектов в памяти.
*	Контейнеры бывают:
*		- Последовательные контейнеры (Sequence containers) - для хранения данных исподьзуют линейные структуры данных, 
*	такие как списки и массивы. Array, Vector, Deque, List, Forward_List.
*		- Асоциативные контейнеры (Associative containers) - хранят данные в виде бинарного дерева (BinaryTree).
*	Map и Set - уникальные деревья, а Multimap и Multiset - не уникальные.
*		- Контейнеры адапторы (Adaptor containers) - Steck, Queue, Priority_Queue.
*		- (Hash tables) - unordered_map, unordered_set, unordered_multimap, unordered_multiset.
*	
*		У каждого контейнера есть свой набор итераторов, который зависит в первую очередь от того, 
*	что является контейнер однонаправленный или двунаправленным.
* 
*		Array - это контейнер, который хранит данные в виде статического массива.
*		Vector - это контейнер, который хранит данные в виде динамического массива.
*		Deque - double ended queue - Двунаправленная очередь - это контейнер который хранит данные в виде списка динамических массивов.
*	В отличии от Vector`a, он не переопределяет уже выделенную память, 
*	а выделяет еще одну область в памяти, там где это возможно и связывает выделенные области памяти в список.
*	Как для пользователя, в отличии от Vector`a, Deque позволяет добавлять в начало контейнера, а не только в конец.
*	Не смотря на то, что Deque хранит даные в произвольных областях памяти, в нем можно использовать арифметику указателей.
*	По-скольку, он организует переход, по указаному масиву.
*		Map - это контейнер, который хранит значения в виде бинарного дерева поиска.
*	Каждым элементом mapявляется пара которая хранит:
*		-ключ (key)
*		-значение (value)
*	Ключ и значение могут быть любого типа.
*	
* 
* 
*		Для того что бы поймать исключение, его должен кто то бросить. Бросить исколючение можно при помощи ключевого слова throw.
*	throw value;
*	throw "My exeption";
*	Обычно исключение бросает какая-то функция. 
*		Метод what класса std::exception возвращает сообщение об ошибке. 
*/

