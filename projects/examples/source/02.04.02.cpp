#include <cassert>
#include <cstddef>
#include <iostream>
#include <span>
#include <string>
#include <vector>

/////////////////////////////////////////////////////

void test_v1(int * x) { if (x) { ++*x; } }

void test_v2(int & x) { ++x; }

/////////////////////////////////////////////////////

void test_v3(const int *, std::size_t)
{
	std::cout << "test_v3 (1)\n";
}

void test_v3(std::span < const int > )
{
	std::cout << "test_v3 (2)\n";
}

void test_v3(const std::vector < int > &)
{
	std::cout << "test_v3 (3)\n";
}

void test_v3(const std::string &) 
{
	std::cout << "test_v3 (4)\n";
}

/////////////////////////////////////////////////////

int main()
{
    auto x = 1;

//  -------------------------------------------------

	test_v1(&x); assert(x == 2);

	test_v2( x); assert(x == 3);

//  -------------------------------------------------

    int array_1[5]{ 1, 2, 3, 4, 5 };

	auto size = 5uz;

	auto array_2 = new int[size]{ 1, 2, 3, 4, 5 };

//  -------------------------------------------------

	test_v3(array_1, std::size(array_1));

	test_v3(array_2, size);
    
//  -------------------------------------------------

	test_v3(std::span < const int > (array_1));

	test_v3(std::span < const int > (array_2, size));

//  -------------------------------------------------
	
	delete[] array_2;

//  -------------------------------------------------

	test_v3(std::vector < int > ({ 1, 2, 3, 4, 5 }));

	test_v3("aaaaa");

//  -------------------------------------------------

//	test_v3(1); // error
}