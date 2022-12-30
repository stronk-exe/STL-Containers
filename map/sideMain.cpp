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
    std::map<int, std::string> m;
        ft::map<int, std::string> ft_m;

        for (size_t i = 0; i < 1e3; i++)
        {
            // m.insert(std::make_pair(i, "string1"));
            m[i] = "stronk";
            std::cout << "Yo\n";
            ft_m[i] = "stronkest";
            // ft_m.insert(ft::make_pair(i, "string1"));
        }
        std::cout << m.size() << " - " << ft_m.size() << std::endl;
}