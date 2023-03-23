#include <iostream>
#include "graph.h"

int main() {
    using namespace graph;
    try {
        graph::Graph<std::size_t, int, int> graph;
        graph.insert_node(1, 1);
        graph.insert_node(2, 2);
        graph.insert_edge({1, 1}, 3);
        graph.insert_edge({1, 2}, 5);
        graph.insert_edge({2, 1}, 6);
        std::cout << graph.degree_in(1);
    }
    catch (std::exception& e) {
        std::cout << e.what();
    }
    return 0;
}
