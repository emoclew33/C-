#include <iostream>
#include <array>
#include <vector>

#define _tab "\t"

//#define _ARRAY_
#define _VECTOR_
#define __

void main()
{
	setlocale(LC_ALL, "");
#ifdef _ARRAY_
	std::array<int, 5> arr = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < arr.size(); i++) { std::cout << arr[i] << _tab; }
#endif // _ARRAY_
#ifdef _VECTOR_	
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };
	for (int i : vec) { std::cout << i << _tab; }
	std::cout << "\nSize:		  " << vec.size() << std::endl;
	std::cout << "Max size:		" << vec.max_size() << std::endl;
	std::cout << "Capacity:		" << vec.capacity() << std::endl;
#endif // _VECTOR_


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
* 
* 
* 
* 
* 
* 
* 
* 
*		Array - это контейнер, который хранит данные в виде статического массива.
*		Vector - это контейнер, который хранит данные в виде динамического массива.
*/

