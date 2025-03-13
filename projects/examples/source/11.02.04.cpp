#include <bit>
#include <cassert>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > struct Deque {};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Size {};

template < typename ... Ts > struct Size < Deque < Ts ... > >
{
    static constexpr auto value = sizeof...(Ts);
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > constexpr auto size_v = Size < D > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > constexpr auto empty_v = size_v < D > == 0;

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Front {};

template < typename T, typename ... Ts > struct Front < Deque < T, Ts ... > > 
{ 
    using type = T;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using front = typename Front < D > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > struct Pop_Front {};

template < typename T, typename ... Ts > struct Pop_Front < Deque < T, Ts ... > >
{
    using type = Deque < Ts ... > ;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using pop_front = typename Pop_Front < D > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, bool C = empty_v < D > > class Max_Type {};

template < typename D > class Max_Type < D, false >
{
private:

    using contender = front < D > ;

    using best = typename Max_Type < pop_front < D > > ::type;

public:

    using type = std::conditional_t < (sizeof(contender) >= sizeof(best)), contender, best > ;
};

template < typename D > class Max_Type < D, true > 
{ 
public: 
        
    using type = char;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D > using max_type = typename Max_Type < D > ::type;

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T, std::size_t I = 0, bool C = empty_v < D > > class Index {};

template < typename D, typename T, std::size_t I > class Index < D, T, I, false > 
:
    public std::conditional_t 
    < 
        std::is_same_v < front < D > , T > ,

        std::integral_constant < std::size_t, I > , 

        Index < pop_front < D > , T, I + 1 > 
    > 
{};

template < typename D, typename T, std::size_t I > class Index < D, T, I, true > {};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T > constexpr auto index_v = Index < D, T > ::value;

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > class Storage
{
protected:

    Storage() = default;

   ~Storage() = default;

//  --------------------------------------------------------------------------

    template < typename T > auto extract() const
    {
        return std::bit_cast < T * > (&m_data);
    }

//  --------------------------------------------------------------------------

    alignas(Ts...) std::byte m_data[sizeof(max_type < Deque < Ts ... > > )]{};

    std::size_t m_index = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename D, typename T, typename ... Ts > class Handler
{
public:

    Handler(T x) 
    { 
        std::construct_at(derived().template extract < T > (), std::move(x));
            
        update();
    }

    auto & operator=(T x)
    {
        if (derived().m_index == s_index) 
        {
            *derived().template extract < T > () = std::move(x);
        }
        else 
        {
            derived().destroy();
                
            std::construct_at(derived().template extract < T > (), std::move(x));
                
            update();
        }

        return derived();
    }

protected:

    Handler() = default;

   ~Handler() = default;

//  -----------------------------------------------------------------------------

    void destroy()
    {
        if (derived().m_index == s_index) 
        {
            derived().template extract < T > ()->~T();
        }
    }

//  -----------------------------------------------------------------------------

    static constexpr auto s_index = index_v < Deque < Ts ... > , T > + 1;

private:

    auto & derived()
    {
        return *static_cast < D * > (this);
    }

    void update() 
    { 
        derived().m_index = s_index;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////

template < typename ... Ts > class Variant 
: 
    private Storage           < Ts ... > , 

    private Handler < Variant < Ts ... > , Ts, Ts ... > ...
{
public:

    Variant() 
    { 
        *this = front < Deque < Ts ... > > ();
    }

    Variant(const Variant & other) : Handler < Variant < Ts ... > , Ts, Ts ... > ::Handler()...
    {
        other.visit([this](auto && x){ *this = x; });
    }

    Variant(Variant && other)
    {
        other.visit([this](auto && x){ *this = std::move(x); });
    }

    auto & operator=(Variant other)
    {
        swap(other);

		return *this;
    }

   ~Variant() 
    { 
        destroy();
    }

//  -------------------------------------------------------------------------------------------

    void swap(Variant & other)
	{
        std::swap(this->m_data , other.m_data );

		std::swap(this->m_index, other.m_index);
	}

//  -------------------------------------------------------------------------------------------

    using Handler < Variant < Ts ... > , Ts, Ts ... > ::Handler  ...;

    using Handler < Variant < Ts ... > , Ts, Ts ... > ::operator=...;

//  -------------------------------------------------------------------------------------------

    template < typename T > auto has() const
    {
        return this->m_index == Handler < Variant < Ts ... > , T, Ts ... > ::s_index;
    }

    template < typename T > auto get() const
    {
        if (!has < T > ()) 
        {
            throw std::runtime_error("invalid type");
        }

        return *this->template extract < T > ();
    }  

    template < typename V > auto visit(V && visitor) const
    {
        return visit_implementation(std::forward < V > (visitor), Deque < Ts ... > ());
    }

private:

    template < typename D, typename U, typename ... Us > friend class Handler;

//  -------------------------------------------------------------------------------------------

    void destroy()
    {
        (Handler < Variant < Ts ... > , Ts, Ts ... > ::destroy(), ... );
        
        this->m_index = 0;
    }

//  -------------------------------------------------------------------------------------------

    template 
    < 
        typename V, typename U, typename ... Us 
    > 
    auto visit_implementation(V && visitor, Deque < U, Us ... > ) const
    {
        if (this->template has < U > ()) 
        {
            return visitor(this->template get < U > ());
        }
        else if constexpr (sizeof...(Us) > 0) 
        {
            return visit_implementation(std::forward < V > (visitor), Deque < Us ... > ());
        }
        else 
        {
            throw std::runtime_error("invalid type");
        }
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Visitor
{
public:

    void operator()(int x) const
    {
        std::cout << "Visitor::operator() : x = " << x << '\n';
    }

    void operator()(const std::string & string) const
    {
        std::cout << "Visitor::operator() : string = " << string << '\n';
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////

class Entity 
{ 
public:

    Entity(int) {} 
};

///////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Variant < int, std::string > variant_1;
    
    Variant < int, std::string > variant_2 = 2;

//  --------------------------------------------------------------

    Variant < int, std::string > variant_3 = variant_2;

                                 variant_3 = variant_2;

//  --------------------------------------------------------------

    Variant < int, std::string > variant_4 = std::move(variant_3);

                                 variant_4 = std::move(variant_3);

                                 variant_4 = 4;

//  --------------------------------------------------------------

    assert(variant_4.has < int > ());
    
    assert(variant_4.get < int > () == 4);

//  --------------------------------------------------------------

    variant_4.visit(Visitor());

//  --------------------------------------------------------------

//  Variant <                 Entity, int > variant_5; // error

    Variant < std::monostate, Entity, int > variant_6;
}
