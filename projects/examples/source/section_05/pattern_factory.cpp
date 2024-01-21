#include <iostream>

class Computer
{
public:

    virtual ~Computer() = default; // note: polymorphic base class

    virtual void run() const = 0;
    
}; // class Computer

struct Mobile : public Computer { void run() const override { std::cout << "Mobile\n"; }; };
struct Tablet : public Computer { void run() const override { std::cout << "Tablet\n"; }; }; 
struct Laptop : public Computer { void run() const override { std::cout << "Laptop\n"; }; };

template < typename T > Computer * create() // note: factory function, consider enumeration
{
    return new T; // note: delete required, consider type traits to verify type T is correct
}

class Server : public Computer
{
public:

    struct Factory // note: factory methods
    {
        static Computer * create_v1() { return new Server(1); } // note: delete required
        static Computer * create_v2() { return new Server(2); } // note: delete required
        static Computer * create_v3() { return new Server(3); } // note: delete required

    }; // struct Factory

    void run() const override { std::cout << "Server v" << m_version << std::endl; };

private:

    explicit Server(int version) : m_version(version) {}; // note: use factory methods

private:

    int m_version = 0;

}; // class Server : public Computer

class Factory
{
public:

    virtual ~Factory() = default; // note: polymorphic base class

    [[nodiscard]] virtual Computer * create() const = 0;
    
}; // class Factory

class Factory_Mobile : public Factory
{
public:

    [[nodiscard]] Computer * create() const override
    { 
        return new Mobile; // note: delete required
    } 

}; // class Factory_Mobile : public Factory

class Factory_Tablet : public Factory
{
public:

    [[nodiscard]] Computer * create() const override
    { 
        return new Tablet; // note: delete required
    } 

}; // class Factory_Tablet : public Factory

class Factory_Laptop : public Factory
{
public:

    [[nodiscard]] Computer * create() const override
    { 
        return new Laptop; // note: delete required
    } 

}; // class Factory_Laptop : public Factory

int main()
{
    delete create < Mobile > ();
    delete create < Tablet > ();
    delete create < Laptop > ();

    delete Server::Factory::create_v1();
    delete Server::Factory::create_v2();
    delete Server::Factory::create_v3();

    Factory * factory_mobile = new Factory_Mobile; // note: delete required
    Factory * factory_tablet = new Factory_Tablet; // note: delete required
    Factory * factory_laptop = new Factory_Laptop; // note: delete required

    delete factory_mobile->create();
    delete factory_tablet->create();
    delete factory_laptop->create();

    delete factory_mobile;
    delete factory_tablet;
    delete factory_laptop;

    return 0;
}