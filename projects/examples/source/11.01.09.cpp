#include <algorithm>
#include <cassert>
#include <set>
#include <vector>

///////////////////////////////////////////////////////////////

int main()
{
	std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------

	auto lambda = [](auto lhs, auto rhs){ return lhs > rhs; };

//  -----------------------------------------------------------

	std::ranges::sort(vector, lambda);

//  -----------------------------------------------------------

	assert(std::ranges::is_sorted(vector, lambda));

//  -----------------------------------------------------------

	std::set < int, decltype(lambda) > set = { 1, 2, 3, 4, 5 };

//  -----------------------------------------------------------

	assert(std::ranges::is_sorted(set, lambda));
}