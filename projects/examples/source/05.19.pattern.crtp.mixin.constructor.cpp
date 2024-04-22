#include <iostream>

// =================================================================================================

class Base
{
public:

    virtual ~Base() = default; // note: polymorphic base class

    virtual void initialize() = 0;

}; // class Base

// =================================================================================================

class Derived : public Base
{
protected: // good: constructor can not be called by user

    explicit Derived(int) {} 

public:

    void initialize() override { std::cout << "initialization" << std::endl; }

}; // class Derived : public Base

// =================================================================================================

template < typename T > class Initializer : private T
{
public:

    template < typename ... Ts > explicit Initializer(Ts ... args) : T(args...)
    {
        this->initialize(); // good: mandatory function call
    }

}; // template < typename T > class Initializer : private T

// =================================================================================================

int main()
{
    const Initializer < Derived > derived(42);

    return 0;
}