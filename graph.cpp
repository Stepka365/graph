#include "graph.h"
#include <algorithm>

template<typename Key, typename Value, typename Weight>
typename graph::Graph<Key, Value, Weight>::Node&
graph::Graph<Key, Value, Weight>::at(const key_type& key) {
    auto it = m_vertices.find(key);
    if (it == end()) {
        throw GraphException("Can't find key:  " + key);
    }
    return (*it).second;
}

template<typename Key, typename Value, typename Weight>
std::size_t graph::Graph<Key, Value, Weight>::degree_in(const key_type& key) const {
    return std::count_if(begin(), end(), [&key](const auto& it) {
        return (*it).second.m_edges.count(key);
    });
}

template<typename Key, typename Value, typename Weight>
bool graph::Graph<Key, Value, Weight>::loop(const key_type& key) const {
    auto it = m_vertices.find(key);
    return it != end() && (*it).second.count(key);
}
