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

        using vertices_type = typename std::unordered_map<key_type, Node>;
        using const_iterator = typename vertices_type::const_iterator;
        using iterator = typename vertices_type::iterator;

        const_iterator cbegin() const noexcept { return m_vertices.cbegin(); }
        const_iterator cend() const noexcept { return m_vertices.cend(); }
        const_iterator begin() const noexcept { return m_vertices.begin(); }
        const_iterator end() const noexcept { return m_vertices.end(); }
        iterator begin() noexcept { return m_vertices.begin(); }
        iterator end() noexcept { return m_vertices.end(); }

        bool empty() const noexcept { m_vertices.empty(); }
        size_t size() const noexcept { m_vertices.size(); }
        void clear() noexcept { m_vertices.clear(); }

        void swap(Graph<key_type, value_type, weight_type>& graph) noexcept {
            m_vertices.swap(graph.m_vertices);
        }

        Node& operator[](const key_type& key) { return m_vertices[key]; }
        Node& at(const key_type& key);

        const_iterator find(const key_type& key) const { return m_vertices.find(key); }
        iterator find(const key_type& key) { return m_vertices.find(key); }
        size_t degree_out(const key_type& key) const;
        size_t degree_in(const key_type& key) const;
        bool loop(const key_type& key) const;

        std::pair<iterator, bool> insert_node(const key_type& key, const value_type& value) {
            return m_vertices.insert({key, {value}});
        }

        std::pair<iterator, bool> insert_or_assign_node(const key_type& key, const value_type& value) {
            return m_vertices.insert_or_assign(key, value);
        }

        std::pair<typename Node::iterator, bool>
        insert_edge(const std::pair<key_type, key_type>& key_pair, const weight_type& weight);

        std::pair<typename Node::iterator, bool>
        insert_or_assign_edge(const std::pair<key_type, key_type>& key_pair, const weight_type& weight);
    private:
        vertices_type m_vertices;
    };

    template<typename key_type, typename value_type, typename weight_type>
    class Graph<key_type, value_type, weight_type>::Node {
    public:
        using edges_type = typename std::unordered_map<key_type, weight_type>;
        using const_iterator = typename edges_type::const_iterator;
        using iterator = typename edges_type::iterator;

        const_iterator cbegin() const noexcept { return m_edges.cbegin(); }
        const_iterator cend() const noexcept { return m_edges.cend(); }
        const_iterator begin() const noexcept { return m_edges.begin(); }
        const_iterator end() const noexcept { return m_edges.end(); }
        iterator begin() noexcept { return m_edges.begin(); }
        iterator end() noexcept { return m_edges.end(); }

        Node() = default;
        Node(const value_type& value) : m_value(value), m_edges() {}

        bool empty() noexcept { return m_edges.empty(); }
        void clear() noexcept { m_edges.clear(); }
        size_t size() noexcept { return m_edges.size(); }

        const value_type& value() const noexcept { return m_value; }
        value_type& value() noexcept { return m_value; }

        const edges_type& get_edges() const noexcept { return m_edges; }
        edges_type& get_edges() noexcept { return m_edges; }
    private:
        value_type m_value;
        edges_type m_edges;
    };

    template<typename Key, typename Value, typename Weight>
    inline void
    swap(const Graph<Key, Value, Weight>& graph1, const Graph<Key, Value, Weight>& graph2) noexcept {
        graph1.swap(graph2);
    }

    class GraphException : public std::runtime_error {
    public:
        GraphException(const char* msg) : std::runtime_error(msg) {}
    };
}

#include "graph.hpp"
