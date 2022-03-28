#include <iostream>
#include <conio.h>
#include <thread>
#include <Windows.h>

using namespace std::chrono_literals;

#define _MIN_TANK_VOLUME_ 20
#define _MAX_TANK_VOLUME_ 80

enum Color 
{
	RED = 0xCF,
	GREEN = 0xAF
};

void color_text(std::string text, Color color_number)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color_number);
	std::cout << text;
	SetConsoleTextAttribute(hConsole, 0x07);
}

class Tank
{
	const unsigned int VOLUME;
	double fuel_level;
public:
	unsigned int get_VOLUME()const { return this->VOLUME; }
	double get_fuel_level()const { return fuel_level; }
	Tank(unsigned int volume) : VOLUME(volume >= _MIN_TANK_VOLUME_ && volume <= _MAX_TANK_VOLUME_ ? volume : 60)
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
	double give_fuel(double amount)
	{
		if (fuel_level - amount > 0)fuel_level -= amount;
		else fuel_level = 0;
		return fuel_level;
	}

};

#define _MIN_ENGIN_CONSUMPTION_ 3
#define _MAX_ENGIN_CONSUMPTION_ 25
#define _DEFAULT_ENGIN_CONSUPTION_ 10

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
		if (consumption >= _MIN_ENGIN_CONSUMPTION_ && consumption <= _MAX_ENGIN_CONSUMPTION_)
			this->consumption = consumption;
		else
			this->consumption = _DEFAULT_ENGIN_CONSUPTION_;
		this->consumption_per_second = this->consumption * 3e-5;
	}
	void start() { is_started = true; }
	void stop() { is_started = false; }
	bool started()const { return is_started; }
	void correct_consumption(int speed)
	{
		if (speed >= 1 && speed <= 60 || speed >= 101 && speed <= 140)
			consumption_per_second = 0.002;
		if (speed >= 61 && speed <= 100)consumption_per_second = .0014;
		if (speed >= 141 && speed <= 200)consumption_per_second = .0025;
		if (speed >= 201 && speed <= 250)consumption_per_second = .003;
		if (speed == 0) consumption_per_second = .0003;
	}
	void info()const
	{
		std::cout << "Consumption per 100 km: " << consumption << " liters\n" <<
			"Consumption per second: " << consumption_per_second << " liters\n";
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


#define Escape 27
#define Enter 13
#define _MAX_SPEED_LOW_LIMIT_ 150
#define _MAX_SPEED_HIGH_LIMIT_ 300
#define _DEFAULT_MAX_SPEED_ 250

class Car
{
	int speed;
	Tank tank;
	Engine engine;
	bool driver_inside;
	const unsigned int MAX_SPEED;
	int accelleration; //ускорение
	struct Control
	{
		std::thread panel_thread;// отображение панели приборов
		std::thread free_wheeling_thread;
		std::thread engine_idle_thread; //холостой ход двигателя
	}control;
public:
	Car(double engine_consumption, unsigned int tank_volume, int max_speed = _DEFAULT_MAX_SPEED_, int accelleration = 10) :
		engine(engine_consumption), tank(tank_volume), 
		MAX_SPEED(max_speed >= _MAX_SPEED_LOW_LIMIT_ && max_speed <= _MAX_SPEED_HIGH_LIMIT_ ? max_speed : _DEFAULT_MAX_SPEED_),
		speed(NULL)
	{
		driver_inside = false;
		this->accelleration = accelleration >= 5 && accelleration <= 25 ? accelleration : 12;
		std::cout << "Your car is ready" << std::endl;
	}
	~Car()
	{
		std::cout << "Car is over" << std::endl;
	}
	void get_in()
	{
		driver_inside = true;
		//panel();
		control.panel_thread = std::thread(&Car::panel, this);
	}
	void get_out()
	{
		driver_inside = false;
		if (control.panel_thread.joinable())control.panel_thread.join();
		system("CLS");
		std::cout << "You are out of your car" << std::endl;
	}
	int get_speed() { return speed; }
	void info()const
	{
		engine.info();
		tank.info();
	}
	void start_engine()
	{
		if (driver_inside && tank.get_fuel_level())
		{
			engine.start();
			control.engine_idle_thread = std::thread(&Car::engine_idle, this);
		}
	}
	void stop_engine()
	{
		engine.stop();
		if (control.engine_idle_thread.joinable())control.engine_idle_thread.join();
	}
	void control_car()
	{

		std::cout << "\n Enter - сесть/выйти из машины\n" <<
			" F - заправить\n" <<
			" I - запустить двигатель\n" <<
			" W - газ\n" <<
			" Escape - завершение программы\n";
		char key;
		do
		{
			key = _getch();
			switch (key)
			{
			case Enter:
				if (driver_inside)get_out();
				else get_in();
				break; //вход и выход из машины
			case 'F':case 'f':
				if (driver_inside && speed == 0)
				{
					std::cout << "Для того что бы заправиться нужно выйти из машины" << std::endl;
					std::cout << "Как поняли? (нажмите  Enter)" << std::endl;
				}
				else
				{
					double amount;
					std::cout << "Введите литраж: "; std::cin >> amount;
					tank.fill(amount);
					std::cout << "Заправка завершена" << std::endl;
				}
				break;
			case Escape:
				//if()
				stop_engine();
				get_out();
				break;
			case 'i':case 'I':
				if (engine.started())stop_engine();
				else start_engine();
				break;
			case 'w':case 'W': 
				if (driver_inside && engine.started())
				{
					if (speed < MAX_SPEED)speed += accelleration;
					if (speed > MAX_SPEED)speed = MAX_SPEED;
					if (!control.free_wheeling_thread.joinable())
						control.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
					std::this_thread::sleep_for(1s);
				}
				break;
			case 's':case 'S':
				if (driver_inside && speed > 0)
				{
					speed -= accelleration;
					if (speed < 0)speed = 0;
					std::this_thread::sleep_for(1s);
				}   
				break;
			default:
				break;
			}
			if (tank.get_fuel_level() == 0)stop_engine();
			if (speed == 0 && control.free_wheeling_thread.joinable())
				control.free_wheeling_thread.join();
		} while (key != Escape);
	}
	void panel()const
	{
		while (driver_inside)
		{
			system("CLS");
			std::cout << "Speed: " << speed << " km/h" << std::endl;
			std::cout << "Fuel level: " << tank.get_fuel_level() << " liters\t";
			if (tank.get_fuel_level() <= 5)
			{
				color_text(" LOW FUEL ", Color::RED);
			}
			std::cout << "\nEngine is "; 
			if (engine.started())
			{
				color_text("Started", Color::GREEN);
			}
			else 
			{
				color_text("stop", Color::RED);
			}
			std::cout << std::endl;
			std::cout << "consumption per second :" << engine.get_consumption_per_second() << " l/s\n";
			std::this_thread::sleep_for(1s);
		}
	}
	void engine_idle()
	{
		while (engine.started() && tank.give_fuel(engine.get_consumption_per_second()))
		{
			std::this_thread::sleep_for(1s);
		}
	}
	void free_wheeling()
	{
		while (speed > 0)
		{
			speed < 0 ? speed = 0 : speed--;
			std::this_thread::sleep_for(1s);
			engine.correct_consumption(speed);
		}
	}
	void accellerate()
	{
		
		if (engine.started() && speed < MAX_SPEED)
		{
			speed += accelleration;
			if (speed > MAX_SPEED)speed = MAX_SPEED;
			if(!control.free_wheeling_thread.joinable())
				control.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
			std::this_thread::sleep_for(1s);
		}
	}
	void slow_down()
	{
		if (driver_inside && speed > 0)
		{
			speed -= accelleration;
			if (speed < accelleration)
			{
				speed = 0;
				if (control.free_wheeling_thread.joinable())
					control.free_wheeling_thread.join();
			}
			std::this_thread::sleep_for(1s);
		}
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK
#define CAR_CHECK

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
		std::cout << "Введите обьем топлива: "; std::cin >> fuel;
		tank.fill(fuel);
		tank.info();
	}
#endif // TANK_CHECK
#ifdef ENGINE_CHECK
	Engine engine(10);
	engine.info();
#endif // ENGINE_CHECK
#ifdef CAR_CHECK
	Car bmw(12, 60, 300);
	bmw.control_car();
#endif // CAR_CHECK

}