#pragma once

#include <unordered_map>
#include <stdexcept>

namespace graph {
    template<typename Key, typename Value, typename Weight>
    class Graph {
    private:
        class Node;

    public:
        using key_type = Key;
        using value_type = Value;
        using weight_type = Weight;

        using const_iterator = typename std::unordered_map<key_type, Node>::const_iterator;
        using iterator = typename std::unordered_map<key_type, Node>::iterator;

        const_iterator cbegin() const noexcept { return m_vertices.cbegin(); }
        const_iterator cend() const noexcept { return m_vertices.cend(); }
        const_iterator begin() const noexcept { return m_vertices.begin(); }
        const_iterator end() const noexcept { return m_vertices.end(); }
        iterator begin() noexcept { return m_vertices.begin(); }
        iterator end() noexcept { return m_vertices.end(); }

        bool empty() const noexcept { m_vertices.empty(); }
        std::size_t size() const noexcept { m_vertices.size(); }
        void clear() const noexcept { m_vertices.clear(); }

        void swap(const Graph<key_type, value_type, weight_type>& graph) noexcept {
            m_vertices.swap(graph.m_vertices);
        }

        Node& operator[](const key_type& key) { return m_vertices[key]; }
        Node& at(const key_type& key);

        std::size_t degree_out(const key_type& key) const { return m_vertices[key].size(); }
        std::size_t degree_in(const key_type& key) const;
        bool loop(const key_type& key) const;

        std::pair<iterator, bool> insert_node(const key_type& key, const value_type& value) {
            return m_vertices.insert({key, value});
        }

        std::pair<iterator, bool> insert_or_assign_node(const key_type& key, const value_type& value) {
            return m_vertices.insert_or_assign(key, value);
        }


    private:
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

    template<typename Key, typename Value, typename Weight>
    inline void
    swap(const Graph<Key, Value, Weight>& graph1, const Graph<Key, Value, Weight>& graph2) noexcept {
        graph1.swap(graph2);
    }

    class GraphException : public std::runtime_error {
        GraphException(std::string& msg) : std::runtime_error(msg) {}
    };
}