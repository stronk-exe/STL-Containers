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
#include <random>

#define BLUE "\e[0;34m"
// #define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))
#define TIME_FAC 20 // the ft::map methods can be slower up to std::map methods * TIME_FAC (MAX 20)

typedef std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator> iter_def;
typedef ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> ft_iter_def;
typedef std::pair<std::map<int, std::string>::const_iterator, std::map<int, std::string>::const_iterator> const_iter_def;
typedef ft::pair<ft::map<int, std::string>::const_iterator, ft::map<int, std::string>::const_iterator> ft_const_iter_def;


#define TEST_CASE(fn)                                                                                                             \
    cout << GREEN << "\t======================================================================================" << RESET << endl; \
    cout << endl;                                                                                                                 \
    cout << BLUE << "\t   Running " << #fn << " ... \t\t\t\t\t\t" << RESET << std::endl;                                          \
    fn();                                                                                                                         \
    cout << endl;                                                                                                                 \
    cout << GREEN << "\t======================================================================================" << RESET << endl;
using namespace std;

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

template <typename Iter1, typename Iter2>
bool comparemaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (first1->first != first2->first || first1->second != first2->second)
            return false;
    return true;
}

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};
int main()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " equal_range method "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            iter_def res;
            ft_iter_def ft_res;

            std::map<int, std::string> m;
            ft::map<int, std::string> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(std::make_pair(i, "value"));
                ft_m.insert(ft::make_pair(i, "value"));
            }
            start = get_time();
            res = m.equal_range(1e5);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft_res = ft_m.equal_range(1e5);
            ualarm(0, 0);
            cond = (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first);
        }
        iter_def res;
        ft_iter_def ft_res;
        const_iter_def c_res;
        ft_const_iter_def ft_c_res;
        std::map<int, std::string> m;
        ft::map<int, std::string> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(std::make_pair(arr[i], "value"));
            ft_m.insert(ft::make_pair(arr[i], "value"));
        }
        std::map<int, std::string> const c_m(m.begin(), m.end());
        ft::map<int, std::string> const c_ft_m(ft_m.begin(), ft_m.end());

        res = m.equal_range(15);
        ft_res = ft_m.equal_range(15);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(65);
        ft_res = ft_m.equal_range(65);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(63);
        ft_res = ft_m.equal_range(63);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(120);
        ft_res = ft_m.equal_range(120);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(70);
        ft_res = ft_m.equal_range(70);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));
        res = m.equal_range(150);
        ft_res = ft_m.equal_range(150);
        cond = (cond && (ft_res.first->first == res.first->first) && (ft_res.second->first == res.second->first));

        c_res = c_m.equal_range(15);
        ft_c_res = c_ft_m.equal_range(15);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(65);
        ft_c_res = c_ft_m.equal_range(65);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(63);
        ft_c_res = c_ft_m.equal_range(63);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(120);
        ft_c_res = c_ft_m.equal_range(120);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(70);
        ft_c_res = c_ft_m.equal_range(70);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        c_res = c_m.equal_range(150);
        ft_c_res = c_ft_m.equal_range(150);
        cond = (cond && (ft_c_res.first->first == c_res.first->first) && (ft_c_res.second->first == c_res.second->first));
        EQUAL(cond);
    }
}
