#include <iostream>

int main()
{
    std::cout << "Enter integer value: ";

    int x{}; // good: zero initialized variable for input

    std::cin >> x;

    if (auto y = x * 4 + 10; 42 == y) // good: 42 == y prevents error 42 = y
    {
        std::cout << "path 1" << std::endl;
    }
    else if (y > 0)
    {
        std::cout << "path 2" << std::endl;
    }
    else
    {
        if (x < 0)
        {
            std::cout << "path 3" << std::endl;
        }
        else
        { 
            std::cout << "path 4" << std::endl;
        }
    }

    std::cout << (x > 0 ? x : 42) << std::endl; // good: compact selection

    switch (auto y = x / 4 - 1; y)
    {
    [[likely]] case 0: // good: optimally generated machine code
    [[likely]] case 1:
    [[likely]] case 2:
    {
        std::cout << "path 1" << std::endl;
        [[fallthrough]]; // good: suppressed warning, clear intentions
    }
    case 3:
    {
        std::cout << "path 2" << std::endl;
        break;
    }
    [[unlikely]] case 4: // good: optimally generated machine code
    {
        std::cout << "path 3" << std::endl;
        break;
    }
    default: // good: secure code
    {
        std::cout << "path 4" << std::endl;
        break;
    }
    }

    return 0;
}