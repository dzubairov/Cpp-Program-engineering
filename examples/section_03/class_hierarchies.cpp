#include <iostream>
#include <string>

class Person
{
public:

	Person(const std::string & name) : m_name(name)
	{
		std::cout << "person " << name << " constructed" << std::endl;
	}

public:

	void print() const
	{
		std::cout << "person" << std::endl;
	}

	void print_person() const
	{
		std::cout << "only person" << std::endl;
	}

public:

	void f([[maybe_unused]] int    x) const {}
	void f([[maybe_unused]] char   x) const {}
	void f([[maybe_unused]] double x) const {}

protected:

	const auto & get_name() const // good: return big object by constant reference
	{
		return m_name;
	}

private:

	std::string m_name;

}; // class Person

class Employee : public Person
{
public:

	Employee(const std::string & name, int salary) : Person(name), m_salary(salary)
	{
		std::cout << "employee " << name << " constructed" << std::endl;

//		std::cout << m_name << std::endl; // error: private member

		std::cout << get_name() << std::endl;
	}

public:

	void print() const
	{
		std::cout << "employee" << std::endl;

//		print(); // error: infinite recursion

		Person::print();
	}

	using Person::get_name; // note: change access specifier to public

private:

	using Person::f; // note: change access specifier for all overloaded functions to private

private:

	int m_salary = 0;

}; // class Employee : public Person

class Manager : public Employee
{
public:

	Manager(const std::string & name, int salary, int level) : Employee(name, salary), m_level(level)
	{
		std::cout << "manager " << name << " constructed" << std::endl;
	}

public:

	void print() const
	{
		std::cout << "manager" << std::endl;
	}

private:

	int m_level = 0;

}; // class Manager : public Employee

class Base
{
public:
	int m_data_1{}; // note: avoid public data mostly
protected:
	int m_data_2{}; // note: use protected data by situation
private:
	int m_data_3{}; // good: prefer private data in hierarchies

}; // class Base

class Derived_1 : public Base // note: useful inheritance
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error: private data member
	}

}; // class Derived_1 : public Base

class Derived_2 : protected Base // note: useless inheritance
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error: private data member
	}

}; // class Derived_2 : protected Base

class Derived_3 : /*private*/ Base // note: default inheritance, prefer composition
{
	void f()
	{
		m_data_1 = 42;
		m_data_2 = 42;
//		m_data_3 = 42; // error: private data member
	}

}; // class Derived_3 : private Base

int main()
{
	Manager manager("Ivan", 100000, 10);

	manager.print();

	manager.print_person();

	Derived_1 d1;

	d1.m_data_1 = 42;
//	d1.m_data_2 = 42; // error: protected data member
//	d1.m_data_3 = 42; // error: private   data member

	[[maybe_unused]] Derived_2 d2;

//	d2.m_data_1 = 42; // error: protected data member
//	d2.m_data_2 = 42; // error: protected data member
//	d2.m_data_3 = 42; // error: private   data member

	[[maybe_unused]] Derived_3 d3;

//	d3.m_data_1 = 42; // error: private   data member
//	d3.m_data_2 = 42; // error: private   data member
//	d3.m_data_3 = 42; // error: private   data member

	return 0;
}