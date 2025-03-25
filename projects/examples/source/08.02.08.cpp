#include <iostream>

#include <boost/multiprecision/cpp_int.hpp>

////////////////////////////////////////////

int main()
{
    boost::multiprecision::cpp_int x = 1;

//  ----------------------------------------
    
    for (auto i = 1; i <= 100; ++i) 
    {
        x *= i;
    }

//  ----------------------------------------
    
    std::cout << "main : x = " << x << '\n';
}