#include "Crime.h"


const std::map<size_t, std::string> crimes =
{
	{1, "������ �� �������"},
	{2, "���������� ��������"},
	{3, "���� �� �������� ������"},
	{4, "����� �� �����������"},
	{5, "�������� � ������������ �����"},
	{6, "����������� �������"}
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