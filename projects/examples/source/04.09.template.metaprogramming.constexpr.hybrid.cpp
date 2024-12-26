#include <cassert>

//////////////////////////////////////////////////////////////////////////////////////////

template < int N, int D = 1 > struct Ratio
{
	static constexpr auto num = N;
	static constexpr auto den = D;

//  ---------------------------------

	using type = Ratio < num, den > ;
};

//////////////////////////////////////////////////////////////////////////////////////////

template < typename R1, typename R2 > struct Add
{
	static constexpr auto num = R1::num * R2::den + R2::num * R1::den;

	static constexpr auto den = R1::den * R2::den;

//  ------------------------------------------------------------------
	
	using type = Ratio < num, den > ;
};

template < typename R1, typename R2 > using add_t = typename Add < R1, R2 > ::type;

//////////////////////////////////////////////////////////////////////////////////////////

template < typename T, typename R = Ratio < 1 > > struct Duration 
{ 
	T value = T(); 
};

//////////////////////////////////////////////////////////////////////////////////////////

template 
< 
	typename T1, typename R1, 
	typename T2, typename R2 
>
constexpr auto operator+(const Duration < T1, R1 > & lhs, const Duration < T2, R2 > & rhs)
{
	using unit_t = Ratio < 1, add_t < R1, R2 > ::den > ;

	auto value = 
	(
		lhs.value * unit_t::den / R1::den * R1::num +
		rhs.value * unit_t::den / R2::den * R2::num
	);

	return Duration < decltype(value), unit_t > (value);
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	auto result = 
	(
		Duration < int, Ratio < 1, 2 > > (1) + 
		Duration < int, Ratio < 1, 3 > > (1)
	);

	assert(result.value == 5);
}