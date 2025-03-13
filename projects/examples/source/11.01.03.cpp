#include <algorithm>
#include <cassert>
#include <functional>
#include <set>
#include <vector>

///////////////////////////////////////////////////////////////////

int main()
{
    std::vector < int > vector = { 1, 2, 3, 4, 5 };

//  ---------------------------------------------------------------

	std::ranges::sort(vector, std::greater());

//  ---------------------------------------------------------------

	assert(std::ranges::is_sorted(vector, std::greater()));

//  ---------------------------------------------------------------

	std::set < int, std::greater < int > > set = { 1, 2, 3, 4, 5 };

//  ---------------------------------------------------------------

	assert(std::ranges::is_sorted(set, std::greater()));
}