#ifndef TEST_HPP
#define TEST_HPP

#include <iostream>
#include <unordered_map>

template<typename K, typename V>
void print_map(std::unordered_map<K, V> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
};

#endif