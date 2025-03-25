#include <cstdlib>
#include <iostream>

//////////////////////////////////////////////////////

void test_v1() { std::cout << "test_v1\n"; }

void test_v2() { std::cout << "test_v2\n"; }

//////////////////////////////////////////////////////

int main()
{
    std::atexit(test_v1);

    std::atexit(test_v2);

//  --------------------------------------------------

    auto x = 0;

//  --------------------------------------------------
    
    std::cout << "main : enter int : "; std::cin >> x;

//  --------------------------------------------------

    if (x > 0) 
    {
        std::exit(0);
    }
    else 
    {
        std::abort();
    }
}