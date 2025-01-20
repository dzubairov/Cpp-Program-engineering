#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/graph/visitors.hpp>

/////////////////////////////////////////////////////////////////////////////////////////

class Visitor : public boost::default_bfs_visitor
{
public:

    template < typename V, typename G > auto initialize_vertex(V vertex, const G & graph)
    {
        std::cout << "Visitor::initialize_vertex : vertex = " << vertex << '\n';

        return boost::default_bfs_visitor::initialize_vertex(vertex, graph);
    }

    template < typename V, typename G > auto discover_vertex(V vertex, const G & graph)
    {
        std::cout << "Visitor::discover_vertex : vertex = " << vertex << '\n';

        return boost::default_bfs_visitor::discover_vertex(vertex, graph);
    }

    template < typename V, typename G > auto examine_vertex(V vertex, const G & graph)
    {
        std::cout << "Visitor::examine_vertex : vertex = " << vertex << '\n';

        return boost::default_bfs_visitor::examine_vertex(vertex, graph);
    }

    template < typename V, typename G > auto finish_vertex(V vertex, const G & graph)
    {
        std::cout << "Visitor::finish_vertex : vertex = " << vertex << '\n';

        return boost::default_bfs_visitor::finish_vertex(vertex, graph);
    }

//  -------------------------------------------------------------------------------------

    template < typename E, typename G > auto examine_edge(E edge, const G & graph)
    {
        std::cout << "Visitor::examine_edge : edge = " << edge << '\n';

        return boost::default_bfs_visitor::examine_edge(edge, graph);
    }

    template < typename E, typename G > auto tree_edge(E edge, const G & graph)
    {
        std::cout << "Visitor::tree_edge : edge = " << edge << '\n';

        return boost::default_bfs_visitor::tree_edge(edge, graph);
    }

    template < typename E, typename G > auto non_tree_edge(E edge, const G & graph)
    {
        std::cout << "Visitor::non_tree_edge : edge = " << edge << '\n';

        return boost::default_bfs_visitor::non_tree_edge(edge, graph);
    }
    
//  -------------------------------------------------------------------------------------

    template < typename E, typename G > auto gray_target(E edge, const G & graph)
    {
        std::cout << "Visitor::gray_target : edge = " << edge << '\n';

        return boost::default_bfs_visitor::gray_target(edge, graph);
    }

    template < typename E, typename G > auto black_target(E edge, const G & graph)
    {
        std::cout << "Visitor::black_target : edge = " << edge << '\n';

        return boost::default_bfs_visitor::black_target(edge, graph);
    }
};

/////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	boost::adjacency_list < boost::vecS, boost::vecS, boost::directedS > graph;

    boost::add_edge(1, 3, graph);
    boost::add_edge(2, 2, graph);
    boost::add_edge(2, 4, graph);
    boost::add_edge(3, 2, graph);
    boost::add_edge(3, 4, graph);
    boost::add_edge(4, 2, graph);
    boost::add_edge(4, 5, graph);
    boost::add_edge(5, 1, graph);
    boost::add_edge(5, 2, graph);

    auto visitor = boost::visitor(Visitor());

    boost::breadth_first_search(graph, 1, visitor);
}