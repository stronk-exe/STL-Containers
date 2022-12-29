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

int main()
{
    std::map<char, int> m;
    ft::map<char, int> ft_m;

    std::pair<std::map<char, int>::iterator, bool> ret;
    ft::pair<ft::map<char, int>::iterator, bool> ft_ret;

    ret = m.insert(std::pair<char, int>('z', 500));
    ft_ret = ft_m.insert(ft::pair<char, int>('z', 500));

    std::cout << ret.second << ft_ret.second << std::endl;

}