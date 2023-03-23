#include "graph.h"
#include <algorithm>

template<typename Key, typename Value, typename Weight>
typename graph::Graph<Key, Value, Weight>::Node&
graph::Graph<Key, Value, Weight>::at(const key_type& key) {
    auto it = m_vertices.find(key);
    if (it == end()) {
        throw GraphException("Can't find key in graph");
    }
    return (*it).second;
}

template<typename Key, typename Value, typename Weight>
std::size_t graph::Graph<Key, Value, Weight>::degree_in(const key_type& key) const {
    if (m_vertices.count(key) == 0) {
        throw GraphException("Can't find key in graph");
    }
    return std::count_if(begin(), end(), [&key](const auto& it) {
        return (*it).second.get_edges().count(key);
    });
//    bool flag = false;
//    std::size_t count = std::count_if(begin(), end(), [&key, &flag](const auto& it) {
//        flag = ((*it).first == key);
//        return (*it).second.get_edges().count(key);
//    });
//    if (!flag){
//        throw GraphException("Can't find key in graph");
//    }
//    return count;
}

template<typename Key, typename Value, typename Weight>
bool graph::Graph<Key, Value, Weight>::loop(const key_type& key) const {
    auto it = m_vertices.find(key);
    return it != end() && (*it).second.get_edges().count(key);
}

//template<typename Key, typename Value, typename Weight>
//std::pair<typename graph::Graph<Key, Value, Weight>::Node::iterator, bool>
//graph::Graph<Key, Value, Weight>::
//insert_edge(const std::pair<key_type, key_type>& key_pair, weight_type& weight) {
//    auto it = m_vertices.find(key_pair.first);
//
//    return nullptr;
//}