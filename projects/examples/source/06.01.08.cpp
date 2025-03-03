#include <cassert>
#include <iostream>

#include "06.01.05.hpp"
#include "06.01.06.hpp"

/////////////////////////////////

//  void test_v2() // error
//  { 
//	    std::cout << "test_v2\n";
//  } 

/////////////////////////////////

int main()
{
	test_v2();
	
//	test_v3(); // error

//	test_v4(); // error

	test_v5();

	test_v6 < int > ();

//  ---------------------------

	assert(g_x1 == 1);

//	assert(g_x2 == 2); // error

//	assert(g_x3 == 3); // error

	assert(g_x4 == 4);

	assert(g_x5 == 5);

	assert(g_x6 == 6);
}