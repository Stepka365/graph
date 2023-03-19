#pragma once

#include <unordered_map>

namespace graph {
    template<typename Key, typename Value, typename Weight>
    class Graph {
    public:
        using key_type = Key;
        using value_type = Value;
        using weight_type = Weight;
    private:
        class Node {
        private:
            value_type value;
            std::unordered_map<key_type, weight_type> m_edges;
        };

        std::unordered_map<key_type, Node> m_vertices;
    };
}