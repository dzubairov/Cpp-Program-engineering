#include <cassert>
#include <cstddef>
#include <vector>

////////////////////////////////////////////////////////////////////////

class Memento 
{
public:

    Memento(int data) : m_states(1, State(data)) 
    {
        m_deltas.push_back(m_states.front() - State());
    }

//  --------------------------------------------------------------------

    auto get() const
    {
        return m_states.front().data;
    }

    void set(int data)
    {
        State state(data);
        
        m_deltas.push_back(state - m_states.front());

        m_states.front() = state;
    }

    void save()
    { 
        m_states.push_back(m_states.front()); 
    }

    void load_v1(std::size_t index)
    {
        m_states.front() = m_states.at(index);
    }

    void load_v2(std::size_t shift)
    {
        State state;

        for (auto i = 0uz; i < shift && i < std::size(m_deltas); ++i)
        {
            state = state + m_deltas[i];
        }

        m_states.front() = state;
    }

private:

    struct State { int data = 0; };

    struct Delta { int data = 0; };

//  --------------------------------------------------------------------

    friend auto operator-(const State & lhs, const State & rhs) -> Delta
    { 
        return Delta(lhs.data - rhs.data); 
    }

    friend auto operator+(const State & lhs, const Delta & rhs) -> State
    { 
        return State(lhs.data + rhs.data); 
    }

//  --------------------------------------------------------------------

    std::vector < State > m_states;

    std::vector < Delta > m_deltas;
};

////////////////////////////////////////////////////////////////////////

int main() 
{
    Memento memento(1); 
    
    memento.save(); memento.set(2);

    memento.save();
    
    memento.load_v1(1); assert(memento.get() == 1);
    
    memento.load_v2(2); assert(memento.get() == 2);
}