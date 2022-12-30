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
    std::map<char, int> m;
        ft::map<char, int> ft_m;
        std::map<char, int>::iterator it;
        ft::map<char, int>::iterator ft_it;

        // insert some values:
        std::cout << "len " << ft_m.size() << std::endl; 
        ft_m['a'] = 10;
        std::cout << "len " << ft_m.size() << std::endl;
        ft_m['a'] = 10;
        std::cout << "len " << ft_m.size() << std::endl;
        exit(1);
        ft_m['b'] = 20;
        ft_m['c'] = 30;
        ft_m['d'] = 40;
        ft_m['e'] = 50;
        ft_m['f'] = 60;

        m['a'] = 10;
        m['b'] = 20;
        m['c'] = 30;
        m['d'] = 40;
        m['e'] = 50;
        m['f'] = 60;
    
    ft_m.erase('e');
    m.erase('e');
    std::cout << m.size() << " X "<< ft_m.size() << std::endl;
    // std::cout <<(ft_m.begin() == ft_m.end()) << std::endl;
    // && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());
}