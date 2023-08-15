#include <iostream>

unsigned int f(unsigned int n)
{
	return (n < 2 ? 1 : n * f(n - 1));
}

int g(int x);

[[noreturn]] void h()
{
	exit(1);
}

int main()
{
	std::cout << f(5) << std::endl;

	return 0;
}

int g(int x)
{
	return x + 42;
}