#include <iostream>

/////////////////////////////////////////////////////////////

int main()
{
    auto x = 0;

//  ---------------------------------------------------------

    std::cout << "main : enter int x : "; std::cin >> x;

    std::cout << "main : selection ";

//  ---------------------------------------------------------

    if (auto y = x; y > 0) // support : compiler-explorer.com
    {
        std::cout << "(1)\n";
    }
    else if (0 == y)
    {
        std::cout << "(2)\n";
    }
    else
    {
        std::cout << "(3)\n";
    }
}