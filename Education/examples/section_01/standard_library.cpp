#include <cmath>
#include <iostream>
#include <string>

//using namespace std; // bad: dangerous in big projects

int main()
{
	int x{};
	int y{};

	std::cout << "Enter two numbers separated by a space symbol: ";

	std::cin >> x >> y;

	std::cout << "You entered " << x << " and " << y << std::endl;

	std::string string_1 = "Hello, ";

	std::string string_2{};

	std::cout << "Enter your name in english: ";

	std::cin >> string_2;

	std::cout << string_1 + string_2 << std::endl;

	std::cout << std::abs(-1.0) << std::endl;

	std::cout << std::sin(2.0) << std::endl;

	std::cout << std::pow(2.0, 3.0) << std::endl;

	std::cout << std::sqrt(4.0) << std::endl;

	return 0;
}