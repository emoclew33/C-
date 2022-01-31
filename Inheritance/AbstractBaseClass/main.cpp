#include<iostream>
using namespace std;

class Vehicle
{
	int speed;
public:
	virtual void move() = 0;
};


class GroundVehicle : public Vehicle {};
class AirVehicle : public Vehicle {};
class WaterVehicle : public Vehicle {};

class Car :public GroundVehicle
{
public:
	void move() { cout << "Машина едит на 4-х колесах" << endl; }
};

class Bike :public GroundVehicle
{
public:
	void move() { cout << "Мотоцикл едит на 2-х колесах" << endl; }
};

class Airplain :public AirVehicle
{
public:
	void move() { cout << "Самолет летит по воздуху. Hужна взлетная полоса" << endl; }
};

class Helicopter :public AirVehicle
{
public:
	void move() { cout << "Вертолет летит по воздуху. Не нужна взлетная полоса" << endl; }
};

class Boat :public WaterVehicle
{
public:
	void move() { cout << "Катер плывет по воде с помощью мотора" << endl; }
};

class Yacht :public WaterVehicle
{
public:
	void move() { cout << "Яхта, парус" << endl; }
};


void main()
{
	setlocale(LC_ALL, "");
	//Vehicle v;		//Abstract
	//GroundVehicle gv;	//Abstract

	Car bmw;
	bmw.move();
	Bike harley_devidson;
}