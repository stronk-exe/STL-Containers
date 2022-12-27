#include <iostream>
#include "vector.hpp"
#include <vector>
#include <iomanip>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

int main()
{
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method (range) "
              << "] --------------------]\t\t\033[0m";
    {
        /*
         * strings to store the resutls
         */
        std::string str, ft_str;
        /*
         * var to store the size and the capacity
         */
        ft::vector<std::string>::size_type s, ft_s;
        ft::vector<std::string>::size_type c, ft_c;
        std::vector<std::string>::iterator it;
        ft::vector<std::string>::iterator ft_it;
        /*
         * bool to store the comparison
         */
        bool cond;
        /*------------------ test 1: erase from the begin to end -------------------*/
        {
            // std::vector<std::string> v(100, "hello");
            // ft::vector<std::string> ft_v(100, "hello");

            // it = v.erase(v.begin(), v.end());
            // ft_it = ft_v.erase(ft_v.begin(), ft_v.end());

            // s = v.size();
            // ft_s = ft_v.size();
            // c = v.size();
            // ft_c = ft_v.size();
            // for (size_t i = 0; i < v.size(); ++i)
            //     str += v[i];
            // for (size_t i = 0; i < ft_v.size(); ++i)
            //     ft_str += ft_v[i];
            // cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            // cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }

        /*--------------------------------------------------------------------------*/
        /*------------------ test 2: erase from the begin to begin + 70 -------------------*/
        {
            std::vector<std::string> v(100, "hello");
            ft::vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin(), v.begin() + 70);
            ft_it = ft_v.erase(ft_v.begin(), ft_v.begin() + 70);
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            // cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }
        /*--------------------------------------------------------------------------*/
        /*------------------ test 3: erase from the begin + 60 to end -------------------*/

        {
            std::vector<std::string> v(100, "hello");
            ft::vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin() + 60, v.end());
            ft_it = ft_v.erase(ft_v.begin() + 60, ft_v.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            // cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }

        /*--------------------------------------------------------------------------*/
        /*------------------ test 4: erase from the begin + 20 to end - 30 -------------------*/
        {
            std::vector<std::string> v(100, "hello");
            ft::vector<std::string> ft_v(100, "hello");

            it = v.erase(v.begin() + 20, v.end() - 30);
            ft_it = ft_v.erase(ft_v.begin() + 20, ft_v.end() - 30);
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.size();
            ft_c = ft_v.size();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            // cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        }
        /*--------------------------------------------------------------------------*/
        EQUAL(cond);
    }
}