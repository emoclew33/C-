#include <iostream>
#include <conio.h>
#define Escape 27
#define Enter 13
#define MIN_ENGIN_CONSUMPTION 3
#define MAX_ENGIN_CONSUMPTION 25
#define MIN_TANK_VOLUME 20
#define MAX_TANK_VOLUME 80
#define del std::cout << "\n--------------------------------------------------------------------\n";
//#define TANK_CHECK
//#define ENGINE_CHECK
#define CAR_CHECK

class Tank
{
	const unsigned int VOLUME;
	double fuel_level;
public:
	unsigned int get_VOLUME()const { return this->VOLUME; }
	double get_fuel_level()const { return fuel_level; }
	Tank(unsigned int volume) : VOLUME(volume >= MIN_TANK_VOLUME && volume <= MAX_TANK_VOLUME ? volume : 60) 
	{
		this->fuel_level = 0;
		std::cout << "Tank is ready" << std::endl;
	}
	~Tank()
	{
		std::cout << "Tank is over" << std::endl;
	}
	void info()const 
	{
		std::cout << "Tank volume:" << VOLUME << " liters\n" <<
					 "Fuel level: " << fuel_level << " liters\n";
	}
	void fill(double fuel_level)
	{
		if (fuel_level <= 0)return;
		if (this->fuel_level + fuel_level <= VOLUME)this->fuel_level += fuel_level;
		else this->fuel_level = VOLUME;
	}
};
class Engine
{
	double consumption; // расход на 100 км
	double consumption_per_second; //расход за одну секунду
	bool is_started; //двигатель заведен или заглушен
public:
	double get_consumption()const { return consumption; }
	double get_consumption_per_second()const { return consumption_per_second; }
	void set_consumption(double consumption)
	{
		if (consumption >= MIN_ENGIN_CONSUMPTION && consumption <= MAX_ENGIN_CONSUMPTION)
			this->consumption = consumption;
		else
			this->consumption = 10;
		this->consumption_per_second = this->consumption * 3e-5;
	}
	void start() { is_started = true; std::cout << "RRR - RR - RRR - RR" << std::endl; }
	void stop() { is_started = false; std::cout << "Cur - Chug" << std::endl; }
	bool started()const { return is_started; }
	void info()const 
	{ 
		std::cout << "consumption per 100 km: " << consumption << " liters\n" <<
			"consumption per second: " << consumption_per_second << " liters\n";
	}
	Engine(double consumption) 
	{ 
		set_consumption(consumption);
		is_started = false;
		std::cout << "Engine is ready" << std::endl;
	}
	~Engine()
	{
		std::cout << "Engine is over" << std::endl;
	}
};
class Car 
{
	Engine engine;
	Tank tank;
	bool driver_inside;
public:
	Car(double engine_consumption, unsigned int tank_volume)
		: engine(engine_consumption), tank(tank_volume)
	{
		std::cout << "your car is ready" << std::endl;
	}
	~Car()
	{
		std::cout << "car is over" << std::endl;
	}
	void get_in() 
	{
		driver_inside = true;
		panel();
	}
	void get_out() 
	{ 
		driver_inside = false; 
		system("CLS"); 
		std::cout << "you are out of your car" << std::endl;
	}
	void info()const
	{
		engine.info();
		tank.info();
	}
	void control_car()
	{
		std::cout << "press enter to get in" << std::endl;
		char key;
		do
		{
			del
			key = _getch();
			switch (key)
			{
			case Enter:
				if (driver_inside)get_out();
				else get_in();
				break; //вход и выход из машины
			case 'F':
			case 'f':
				double fuel;
				std::cout << "enter amount of fuel:"; std::cin >> fuel;
				tank.fill(fuel);
				break;
			case 'I':
			case 'i':
				this->info();
				break;
			case 'S':
			case 's':
				engine.started() ? engine.stop() : engine.start();
				break;
			default:
				break;
			}
		} while (key != Escape);
	}
	void panel()const
	{
		system("CLS");
		std::cout << "Fuel level: " << tank.get_fuel_level() << " liters\n" <<
			"Engine is " << (engine.started() ? "started" : "stop") << std::endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
#ifdef TANK_CHECK
	Tank tank(40);
	tank.info();
	int fuel;
	tank.info();
	while (true)
	{
		std::cout << "¬ведите обьем топлива: "; std::cin >> fuel;
		tank.fill(fuel);
		tank.info();
	}
#endif // TANK_CHECK
#ifdef ENGINE_CHECK
	Engine engine(10);
	engine.info();
#endif // ENGINE_CHECK
#ifdef CAR_CHECK
	Car bmw(12, 60);
	bmw.control_car();
#endif // CAR_CHECK

}