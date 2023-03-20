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
        class Node;

        std::unordered_map<key_type, Node> m_vertices;
    };

    template<typename key_type, typename value_type, typename weight_type>
    class Graph<key_type, value_type, weight_type>::Node {
    public:
        using const_iterator = typename std::unordered_map<key_type, weight_type>::const_iterator;
        using iterator = typename std::unordered_map<key_type, weight_type>::iterator;

        const_iterator cbegin() const noexcept { return m_edges.cbegin(); }
        const_iterator cend() const noexcept { return m_edges.cend(); }
        const_iterator begin() const noexcept { return m_edges.begin(); }
        const_iterator end() const noexcept { return m_edges.end(); }
        iterator begin() noexcept { return m_edges.begin(); }
        iterator end() noexcept { return m_edges.end(); }

        bool empty() noexcept { return m_edges.empty(); }
        void clear() noexcept { m_edges.clear(); }
        std::size_t size() noexcept { return m_edges.size(); }

        const value_type& value() const noexcept { return m_value; }
        value_type& value() noexcept { return m_value; }
    private:
        value_type m_value;
        std::unordered_map<key_type, weight_type> m_edges;
    };
}