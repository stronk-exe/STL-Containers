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
    std::map<int, std::string> m1;
    ft::map<int, std::string> ft_m1;
    std::map<int, std::string>::iterator it;
    ft::map<int, std::string>::iterator ft_it;

    for (size_t i = 0; i < 100000/*1e6*/; i++)
    {
        m1.insert(std::make_pair(i, "string2"));
        ft_m1.insert(ft::make_pair(i, "string2"));
        std::cout << ft_m1.size() << " LMACHAKIL!\n";
    }

}