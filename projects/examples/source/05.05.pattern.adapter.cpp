#include <iostream>

//  ==========================================================

struct Client 
{ 
	void test() const
	{ 
		std::clog << "Client::test\n"; 
	} 
};

//  ==========================================================

struct Entity
{
	virtual ~Entity() = default; 

	virtual void test() const = 0;	
};

//  ==========================================================

class Adapter_v1 : public Entity
{
public:

	explicit Adapter_v1(Client & client) : m_client(client) {}

//  ----------------------------------------------------------

	void test() const override 
	{ 
		m_client.test(); 
	}

private:

	Client & m_client;
};

//  ==========================================================

struct Adapter_v2 : public Entity, private Client
{
	void test() const override 
	{ 
		Client::test(); 
	}
};

//  ==========================================================

int main()
{	
	Client client;

	Entity * entity_1 = new Adapter_v1(client);

	Entity * entity_2 = new Adapter_v2;

	entity_1->test(); 
	entity_2->test(); 
	
	delete entity_1;
	delete entity_2;
}