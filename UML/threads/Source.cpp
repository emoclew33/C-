#include <iostream>
#include <thread>
using namespace std::chrono_literals;

bool finish = false;

void hello()
{
	while (!finish)
	{
		std::cout << "+ ";
		std::this_thread::sleep_for(100ms);
	}
}
void world()
{
	while (!finish)
	{
		std::cout << "- ";
		std::this_thread::sleep_for(100ms);
	}
}
void main()
{
	setlocale(LC_ALL, "");
	//инициализация потоков при обьявлении:
	/*std::thread hello_thread(hello); 
	std::thread world_thread(world);*/

	//обьявление потоков:
	std::thread hello_thread;
	std::thread world_thread;

	//инициализация потоков после обьявления:
	hello_thread = std::thread(hello);
	world_thread = std::thread(world);

	std::cin.get(); //ожидает нажатия enter
	finish = true;

	hello_thread.join();
	world_thread.join();
}