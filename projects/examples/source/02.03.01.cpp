#include <cassert>
#include <cstddef>
#include <iostream>
#include <type_traits>

//////////////////////////////////////////////////////////

int main()
{
    auto x = 1, * y = &x;

	static_assert(std::is_same_v < decltype(y), int * > );

	assert(*y == x);

	std::cout << "main : y = " << y << '\n';

//  ------------------------------------------------------

//	[[maybe_unused]] int * z1 = 0; // bad

//	[[maybe_unused]] int * z2 = NULL; // bad

	[[maybe_unused]] int * z3 = nullptr;
}