#include <tuple>

//////////////////////////////////////////////////////

struct Variant 
{
	union 
	{ 
		int x, y = 0;
	};
	
	bool has_error = false;
};

//////////////////////////////////////////////////////

auto test(int x)
{
	if (x > 0)
	{
		return Variant { .x = x, .has_error = false };
	}
	else
	{
		return Variant { .y = 1, .has_error =  true };
	}
}

//////////////////////////////////////////////////////

int main()
{
	std::ignore = test(1);
}