#include <iostream>

long unsigned factorial(unsigned n);
double power(double a, int n);

int main()
{
	int n_number; std::cin >> n_number;
	std::cout << factorial(n_number);
	double d_number; std::cin >> d_number; std::cin >> n_number;
	std::cout << power(d_number, n_number);
	return 0;
}

long unsigned factorial(unsigned n)
{
	return n > 1 ? n * factorial(n-1) : 1;
}
double power(double a, int n)
{
	return n != 1 ? a * power(a, n-1) : a;
}