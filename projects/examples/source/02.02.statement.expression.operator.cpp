#include <cassert>
#include <cmath>
#include <iostream>

int main()
{
	const auto a = false, b = true;

	assert((   ! a) == b); assert((  not a) == b);
	assert((   ! b) == a); assert((  not b) == a);

//  ================================================================================================

	assert((a && a) == a); assert((a and a) == a);
	assert((a && b) == a); assert((a and b) == a);
	assert((b && a) == a); assert((b and a) == a);
	assert((b && b) == b); assert((b and b) == b);

//  ================================================================================================

	assert((a || a) == a); assert((a  or a) == a);
	assert((a || b) == b); assert((a  or b) == b);
	assert((b || a) == b); assert((b  or a) == b);
	assert((b || b) == b); assert((b  or b) == b);

//  ================================================================================================

	assert(!(a && b) == (!a || !b));
	assert(!(a || b) == (!a && !b));

//  ================================================================================================

	assert(((a && b) && (std::cout << "aaa")) == a);
	assert(((a || b) || (std::cout << "bbb")) == b);

//  ================================================================================================

	auto x = 1, y = 2;

	assert((  +  y) == +2);
	assert((  -  y) == -2);

//  ================================================================================================

	assert((x +  y) == +3);
	assert((x -  y) == -1);
	assert((x *  y) == +2);
	assert((x /  y) == +0);
	assert((x %  y) == +1);

//  ================================================================================================

	assert((x += y) == +3);
	assert((x -= y) == +1);
	assert((x *= y) == +2);
	assert((x /= y) == +1);
	assert((x %= y) == +1);

//  ================================================================================================

	assert((  ++ y) == +3);
	assert((  -- y) == +2);
	assert((x ++  ) == +1);
	assert((x --  ) == +2);

//  ================================================================================================

	assert((x <  y) ==  1);
	assert((x >  y) ==  0);
	assert((x <= y) ==  1);
	assert((x >= y) ==  0);
	assert((x == y) ==  0);
	assert((x != y) ==  1);
	
//  ================================================================================================

//	assert((static_cast < bool > (x) != static_cast < bool > (y)) == 0); // bad

	assert((!!x != !!y) == 0);

	std::swap(x, y);

	x = x + y; 
	y = x - y; 
	x = x - y;

	assert(std::abs(1.0 * x / y - 0.5) < 0.000001);

	assert((+x % +y) == +1);
	assert((+x % -y) == +1);
	assert((-x % +y) == -1);
	assert((-x % -y) == -1);

//	x+++++y; // error

//  ================================================================================================

	[[maybe_unused]] auto z = (1 + 4) / (2 + 3);

//	z = (z + ++z); // error

	[[maybe_unused]] auto m = 1 + 2 + 3;
	[[maybe_unused]] auto n = x = y = z;

//	assert((++m, ++n) == 2); // bad

	return 0;
}
