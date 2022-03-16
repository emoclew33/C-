#pragma once
#include <iostream>
#include <map>
#include <fstream>



extern const std::map<size_t, std::string> crimes;

class Crime
{
	size_t  id;
	std::string place;
public:
	size_t get_id()const
	{
		return id;
	}
	const std::string& get_place()const
	{
		return place;
	}
	Crime(size_t id, const std::string& place) : id(id), place(place) {}
	~Crime(){}
	bool operator==(const Crime& other)const
	{
		return this->id == other.id && this->place == other.place;
	}
	bool operator!=(const Crime& other)const
	{
		return this->id != other.id && this->place != other.place;
	}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj);
std::ofstream& operator<<(std::ofstream& os, const Crime& obj);
