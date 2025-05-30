#include <algorithm>
#include <cassert>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

/////////////////////////////////////////////////////////////////////////////

int main()
{
	std::stringstream stream_1("1 2 3 4 5 a");

    std::stringstream stream_2;

//  -------------------------------------------------------------------------

	std::vector < int > vector;

//  -------------------------------------------------------------------------

	std::ranges::copy
	(
		std::istream_iterator < int > (stream_1),

		std::istream_iterator < int > (), 
			
		std::back_inserter(vector)
	);

	std::ranges::copy(vector, std::ostream_iterator < int > (stream_2, " "));

//  -------------------------------------------------------------------------

	assert(stream_2.str() == "1 2 3 4 5 ");
}