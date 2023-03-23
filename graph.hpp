#pragma once

#include <algorithm>

template<typename Key, typename Value, typename Weight>
typename graph::Graph<Key, Value, Weight>::Node&
graph::Graph<Key, Value, Weight>::at(const key_type& key) {
    auto it = m_vertices.find(key);
    if (it == end()) {
        throw GraphException("at :: key doesn't exist");
    }
    return it->second;
}

template<typename Key, typename Value, typename Weight>
std::size_t graph::Graph<Key, Value, Weight>::degree_out(const key_type& key) const {
    auto it = m_vertices.find(key);
    if (it == end()) {
        throw GraphException("degree_out :: key doesn't exist");
    }
    return it->second.get_edges().size();
}

template<typename Key, typename Value, typename Weight>
std::size_t graph::Graph<Key, Value, Weight>::degree_in(const key_type& key) const {
    if (m_vertices.count(key) == 0) {
        throw GraphException("degree_in :: key doesn't exist");
    }
    return std::count_if(begin(), end(), [&key](auto& it) {
        return it.second.get_edges().count(key);
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
    if (it == end()) {
        throw GraphException("loop :: key doesn't exist");
    }
    return it->second.get_edges().count(key);
}

template<typename Key, typename Value, typename Weight>
std::pair<typename graph::Graph<Key, Value, Weight>::Node::iterator, bool>
graph::Graph<Key, Value, Weight>::
insert_edge(const std::pair<key_type, key_type>& key_pair, const weight_type& weight) {
    auto it = m_vertices.find(key_pair.first);
    if (it == end()) {
        throw GraphException("insert_edge :: key_from doesn't exist");
    }
    if (m_vertices.count(key_pair.second) == 0) {
        throw GraphException("insert_edge :: key_to doesn't exist");
    }
    return it->second.get_edges().insert({key_pair.second, weight});
}

template<typename Key, typename Value, typename Weight>
std::pair<typename graph::Graph<Key, Value, Weight>::Node::iterator, bool>
graph::Graph<Key, Value, Weight>::
insert_or_assign_edge(const std::pair<key_type, key_type>& key_pair, const weight_type& weight) {
    auto it = m_vertices.find(key_pair.first);
    if (it == end()) {
        throw GraphException("insert_or_assign_edge :: key_from doesn't exist");
    }
    if (m_vertices.count(key_pair.second) == 0) {
        throw GraphException("insert_or_assign_edge :: key_to doesn't exist");
    }
    return it->second.get_edges().insert_or_assign({key_pair.second, weight});
}
