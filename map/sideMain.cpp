#include "map.hpp"

#include <map>

#include <vector>
#include <iostream>
#include <iterator>
#include <utility>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

template <typename Iter1, typename Iter2>
bool comparemaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

int main()
{
    std::map<char, std::string> m;
    ft::map<char, std::string> ft_m;

    m['a'] = "an element";
    m['b'] = "another element";
    // m['c'] = m['b'];
    m['b'] = "test";
    m['d'] = "test";

    ft_m['a'] = "an element";
    ft_m['c'] = "an element";
    ft_m['v'] = "an element";
    ft_m['x'] = "an element";
    ft_m['b'] = "another element";
    // ft_m['c'] = ft_m['b'];
    ft_m['b'] = "test";
    // ft_m['d'] = "test";

    std::cout << m.size() << ft_m.size() << std::endl;
}