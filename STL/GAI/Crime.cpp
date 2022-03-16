#include "Crime.h"


const std::map<size_t, std::string> crimes =
{
	{1, "проезд на красный"},
	{2, "превышение скорости"},
	{3, "езда по встреной полосе"},
	{4, "дрифт на перекрестке"},
	{5, "парковка в неположенном месте"},
	{6, "оскорбление офицера"}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << crimes.at(obj.get_id()) << ", " << obj.get_place();
}
std::ofstream& operator<<(std::ofstream& os, const Crime& obj)
{
	os << obj.get_id() << " " << obj.get_place();
	return os;
}