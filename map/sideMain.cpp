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

// int main()
// {
//     std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " begin and end methods "
//               << "] --------------------]\t\t\033[0m";
//     {
//         /*-------------------------------------- time limit test -----------------------------------*/
//         {
//             // time_t start, end, diff;
//             // /*------------------ std::maps ---------------------*/
//             // std::map<int, std::string> m1;
//             // ft::map<int, std::string> ft_m1;
//             // for (size_t i = 0; i < 1e4; i++)
//             // {
//             //     m1.insert(std::make_pair(i, "string2"));
//             //     ft_m1.insert(ft::make_pair(i, "string2"));
//             // }

//             // start = get_time();
//             // m1.begin();
//             // m1.end();
//             // end = get_time();
//             // diff = end - start;
//             // diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
//             // /*-----------------------------------------------------*/
//             // /*------------------ ft::maps ---------------------*/
//             // ualarm(diff * 1e2, 0);
//             // ft_m1.begin();
//             // ft_m1.end();
//             // ualarm(0, 0);
//             // /*----------------------------------------------------*/
//         }
//         /*------------------------------------------------------------------------------------------*/
//         /*------------------ std::maps ---------------------*/
//         std::map<int, std::string> m1;
//         ft::map<int, std::string> ft_m1;

//         for (size_t i = 0; i < 10; i++)
//         {
//             m1.insert(std::make_pair(i, "string2"));
//             ft_m1.insert(ft::make_pair(i, "string2"));
//         }

//         std::map<int, std::string> const m2(m1.begin(), m1.end());
//         ft::map<int, std::string> const ft_m2(ft_m1.begin(), ft_m1.end());

//         /*-----------------------------------------------------*/
//         /*------------------ ft::maps ---------------------*/
//         /*----------------------------------------------------*/
//         /*------------------ strings to store the results ----*/
//         std::string res, ft_res, c_res, c_ft_res;
//         /*----------------------------------------------------*/
//         for (std::map<int, std::string>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
//             res += it->second;
//         // for (std::map<int, std::string>::const_iterator rit = m2.begin(); rit != m2.end(); ++rit) // fill c_res from const m1
//         //     c_res += rit->second;

//         for (ft::map<int, std::string>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
//         {
//             ft_res += it->second;
//             std::cout << "ft_m len " << ft_m1.size() << std::endl;
//         }
//         // std::cout << res << std::endl;
//         std::cout << ft_res << std::endl;
//         // exit(1);
//         // for (ft::map<int, std::string>::const_iterator rit = ft_m2.begin(); rit != ft_m2.end(); ++rit) // fill c_ft_res from const ft_m1
//         //     c_ft_res += rit->second;
        
//         int arr[] = {12, 82, 37, 64, 15};
//         ft::map<int, int> end_test;
//         for(size_t i = 0; i < 5; ++i)
//             end_test.insert(ft::make_pair(arr[i], i));
//         ft::map<int, int>::iterator eit = end_test.end();
//         eit--;
//         EQUAL(res == ft_res && c_res == c_ft_res && eit->first == 82);
//     }
// }


    //  HADI RAH []
// int main()
// {
//     std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator [] "
//               << "] --------------------]\t\t\033[0m";
//     {
//         // {
//         //     time_t start, end, diff;
//         //     /*------------------ std::maps ---------------------*/
//         //     std::map<int, std::string> m1;
//         //     ft::map<int, std::string> ft_m1;

//         //     for (size_t i = 0; i < 1e4; i++)
//         //     // for (size_t i = 0; i < 1e6; i++)
//         //     {
//         //         m1.insert(std::make_pair(i, "string2"));
//         //         ft_m1.insert(ft::make_pair(i, "string2"));
//         //         // std::cout << i << std::endl;
//         //     }
//         //     start = get_time();
//         //     m1[1e6] = "string";
//         //     end = get_time();
//         //     diff = end - start;
//         //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
//         //     /*-----------------------------------------------------*/
//         //     /*------------------ ft::maps ---------------------*/
//         //     ualarm(diff * 1e3, 0);
//         //     ft_m1[1e6] = "string";
//         //     ualarm(0, 0);
//         //     /*----------------------------------------------------*/
//         //     /*------------------ std::maps ---------------------*/
//         //     start = get_time();
//         //     m1[1e6 - 100] = "string";
//         //     end = get_time();
//         //     diff = end - start;
//         //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
//         //     /*-----------------------------------------------------*/
//         //     /*------------------ ft::maps ---------------------*/
//         //     ualarm(diff * 1e3, 0);
//         //     ft_m1[1e6 - 100] = "string";
//         //     ualarm(0, 0);
//         //     /*----------------------------------------------------*/
//         //     /*------------------ std::maps ---------------------*/
//         //     start = get_time();
//         //     m1[1e6 - 100] = m1[1e5];
//         //     end = get_time();
//         //     diff = end - start;
//         //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
//         //     /*-----------------------------------------------------*/
//         //     /*------------------ ft::maps ---------------------*/
//         //     ualarm(diff * 1e3, 0);
//         //     ft_m1[1e6 - 100] = ft_m1[1e5];
//         //     ualarm(0, 0);
//         //     /*----------------------------------------------------*/
//         // }
//         std::map<char, std::string> m;
//         ft::map<char, std::string> ft_m;

//         m['a'] = "an element";
//         m['b'] = "another element";
//         m['c'] = m['b'];
//         m['a'] = "test";

//         ft_m['a'] = "an element";
//         ft_m['b'] = "another element";
//         ft_m['c'] = ft_m['b'];
//         ft_m['a'] = "test";

//         ft_m.printTree();
//         std::cout << m.size() << " x " << ft_m.size() << std::endl;
//         // exit(1);

//         EQUAL(m['a'] == ft_m['a'] && m['b'] == ft_m['b'] && m['c'] == ft_m['c'] && m.size() == ft_m.size());
//     }
// }

int main()
{
    std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method "
              << "] --------------------]\t\t\033[0m";

    {
        bool cond(false);
        // // erasing all the elements in the map;
        // {
        //     time_t start, end, diff;
        //     /*------------------ std::maps ---------------------*/
        //     std::map<int, std::string> m1;
        //     ft::map<int, std::string> ft_m1;
        //     for (size_t i = 0; i < 1e6; i++)
        //     {
        //         m1.insert(std::make_pair(i, "string2"));
        //         ft_m1.insert(ft::make_pair(i, "string2"));
        //     }

        //     start = get_time();
        //     m1.erase(m1.begin(), m1.end());
        //     end = get_time();
        //     diff = end - start;
        //     diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
        //     /*-----------------------------------------------------*/
        //     /*------------------ ft::maps ---------------------*/
        //     ualarm(diff * 1e3, 0);
        //     ft_m1.erase(ft_m1.begin(), ft_m1.end());
        //     ualarm(0, 0);
        //     /*----------------------------------------------------*/
        // }
        std::map<char, int> m;
        ft::map<char, int> ft_m;
        std::map<char, int>::iterator it;
        ft::map<char, int>::iterator ft_it;

        // insert some values:
        ft_m['a'] = 10;
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

        cond = m.size() == ft_m.size() && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        it = m.find('b');
        ft_it = ft_m.find('b');

        // exit(1);
        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second);
        m.erase(it);       // erasing by iterator
        ft_m.erase(ft_it); // erasing by iterator

        cond = cond && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        int ret = m.erase('c');       // erasing by key
        int ft_ret = ft_m.erase('c'); // erasing by key
        std::cout << ret << " x " << ft_ret << std::endl;

        cond = cond && ret == ft_ret && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        it = m.find('e');
        ft_it = ft_m.find('e');

        cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second) && m.size() == ft_m.size();

        m.erase(it, m.end());          // erasing by range
        ft_m.erase(ft_it, ft_m.end()); // erasing by range

        cond = cond && m.empty() == ft_m.empty() && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        /* ---------- Testing some edge cases ---------- */

        std::map<int, std::string> m2;
        ft::map<int, std::string> ft_m2;

        for (size_t i = 0; i < 1e3; i++)
        {
            m2.insert(std::make_pair(i, "string1"));
            ft_m2.insert(ft::make_pair(i, "string1"));
        }

        std::map<int, std::string>::reverse_iterator it2 = m2.rbegin();
        ft::map<int, std::string>::reverse_iterator ft_it2 = ft_m2.rbegin();

        m2.erase(m2.begin());
        ft_m2.erase(ft_m2.begin());

        cond = cond && m2.size() == ft_m2.size() && comparemaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

        m2.erase(it2->first);
        ft_m2.erase(ft_it2->first);

        cond = cond && m2.size() == ft_m2.size() && comparemaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

        // std::map<int, std::string> m3;
        // ft::map<int, std::string> ft_m3;
        // std::vector<int> vec;
        // std::vector<int> ft_vec;
        // std::random_device randDev;
        // std::mt19937 generator(randDev());
        // std::uniform_int_distribution<int> distr(0, 1e8);

        // for (size_t i = 0; i < 1e3; i++)
        // // // for (size_t i = 0; i < 1e6; i++)
        // {
        //     m3.insert(std::make_pair(i, "string1"));
        //     ft_m3.insert(ft::make_pair(i, "string1"));
        // }

        // for (size_t i = 0; i < 1e3; i++)
        // // // for (size_t i = 0; i < 1e6; ++i)
        // {
        //     int n = distr(generator);
        //     int ret1 = m3.erase(n);
        //     int ret2 = ft_m3.erase(n);

        //     if (ret1 != ret2)
        //     {
        //         cond = false;
        //         break;
        //     }
        // }

        // if (!m3.empty())
        // {
        //     m3.erase(m3.begin(), m3.end());
        //     m3.erase(m3.begin(), m3.end());
        // }
        // if (!ft_m3.empty())
        // {
        //     ft_m3.erase(ft_m3.begin(), ft_m3.end());
        //     ft_m3.erase(ft_m3.begin(), ft_m3.end());
        // }
        // // std::cou
        // cond = cond && (m3.size() == ft_m3.size() && comparemaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()));

        EQUAL(cond);
    }
}

//      W HADI RAH FIND
// int main()
// {
//     std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " find method "
//               << "] --------------------]\t\t\033[0m";
//     {
//         bool cond(true);
//         {
//             // time_t start, end, diff;
//             // /*------------------ std::maps ---------------------*/
//             // std::map<int, std::string> m1;
//             // ft::map<int, std::string> ft_m1;
//             // for (size_t i = 0; i < 1e4; i++)
//             // {
//             //     m1.insert(std::make_pair(i, "string2"));
//             //     ft_m1.insert(ft::make_pair(i, "string2"));
//             // }

//             // start = get_time();

//             // for (size_t i = 1e1; i < 1e3; i += 10)
//             //     m1.find(i);

//             // end = get_time();
//             // diff = end - start;
//             // diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;
//             // /*-----------------------------------------------------*/
//             // /*------------------ ft::maps ---------------------*/
//             // ualarm(diff * 1e2, 0);
//             // for (size_t i = 1e1; i < 1e3; i += 10)
//             //     ft_m1.find(i);
//             // ualarm(0, 0);
//             /*----------------------------------------------------*/
//         }

//         // std::vector<int> vec;
//         // std::vector<int> ft_vec;
//         // std::random_device randDev;
//         // std::mt19937 generator(randDev());
//         // std::uniform_int_distribution<int> distr(0, 1e8);

//         // std::map<int, std::string> m1;
//         // ft::map<int, std::string> ft_m1;
//         // std::map<int, std::string>::iterator it;
//         // ft::map<int, std::string>::iterator ft_it;

//         // for (size_t i = 0; i < 4/*1e6*/; i++)
//         // {
//         //     m1.insert(std::make_pair(i, "string2"));
//         //     ft_m1.insert(ft::make_pair(i, "string2"));
//         // }

//         // // std::cout << ft_m1.size() << "LMACHAKIL!\n";
//         // // exit(1);
//         // for (size_t i = 0; i < 1e4; i++)
//         // {
//         //     int n = distr(generator);
//         //     it = m1.find(n);
//         //     ft_it = ft_m1.find(n);
//         //     if (it == m1.end() && ft_it == ft_m1.end())
//         //         continue;
//         //     if (it == m1.end() && ft_it != ft_m1.end())
//         //     {
//         //         cond = false;
//         //         break;
//         //     }
//         //     else
//         //     {
//         //         vec.push_back(it->first);
//         //         ft_vec.push_back(ft_it->first);
//         //     }
//         // }

//         // std::cout <<"\n";
//         std::map<char, int> m;
//         ft::map<char, int> ft_m;
//         std::map<char, int>::iterator it2;
//         ft::map<char, int>::iterator ft_it2;

//         m['a'] = 50;
//         m['b'] = 100;
//         m['c'] = 150;
//         m['d'] = 200;

//         ft_m['a'] = 50;
//         ft_m['b'] = 100;
//         ft_m['c'] = 150;
//         ft_m['d'] = 200;

//         // it2 = m.find('a');
//         // ft_it2 = ft_m.find('a');
//         ft_m.printTree();
//         exit(1);

//         cond = cond && it2->first == ft_it2->first && it2->second == ft_it2->second;

//         if (it2 != m.end())
//             m.erase(it2);
//         if (ft_it2 != ft_m.end())
//             ft_m.erase(ft_it2);

//         cond = cond && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         EQUAL(cond);
//     }
// }

// int main()
// {
//     ft::map<char, int> bst;
//     // bst.insert(ft::make_pair('a', 10));
//     // bst.insert(ft::make_pair('b', 2));
//     // bst.insert(ft::make_pair('c', 3));
//     // bst.insert(ft::make_pair('d', 7));
//     // bst.insert(ft::make_pair('e', 57));
//     bst['a'] = 10;
//     // bst.printTree();
//     bst['b'] = 2;
//     // bst.printTree();
//     bst['c'] = 3;
//     bst['d'] = 7;
//     bst['e'] = 547;
//     bst['f'] = 33;
//     bst['g'] = 71;
//     bst['h'] = 573;

//     bst.printTree();
//     // std::cout << std::endl
//     //     << "After deleting" << std::endl;
//     // bst.erase('b');
//     // bst.printTree();
// }

// int main()
// {
//     std::cout << "\t\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method "
//               << "] --------------------]\t\t\033[0m";

//     {
//         bool cond(false);
//         // std::map<char, int> m;
//         // ft::map<char, int> ft_m;
//         // std::map<char, int>::iterator it;
//         // ft::map<char, int>::iterator ft_it;

//         // // insert some values:
//         // ft_m.insert(ft::make_pair('a', 10));
//         // ft_m.insert(ft::make_pair('b', 20));
//         // ft_m.insert(ft::make_pair('c', 30));
//         // ft_m.insert(ft::make_pair('d', 40));
//         // ft_m.insert(ft::make_pair('e', 50));
//         // ft_m.insert(ft::make_pair('f', 60));
//         // // ft_m['a'] = 10;
//         // // ft_m['b'] = 20;
//         // // ft_m['c'] = 30;
//         // // ft_m['d'] = 40;
//         // // ft_m['e'] = 50;
//         // // ft_m['f'] = 60;

//         // m['a'] = 10;
//         // m['b'] = 20;
//         // m['c'] = 30;
//         // m['d'] = 40;
//         // m['e'] = 50;
//         // m['f'] = 60;


//         // ft::map<char, int>::iterator first = ft_m.begin();
//         // ft::map<char, int>::iterator last = ft_m.end();
//         // // while(first != ft_m.end())
//         // // {
//         // //     first++;
//         // // }
        
//         // // std::cout << ft_m.begin()._node->data.second << std::endl;
//         // // last--;
//         // // last--;
//         // // std::cout << last._node->data.second << std::endl;
//         // // ft_m.printTree();

//         // cond = m.size() == ft_m.size() && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         // it = m.find('b');
//         // ft_it = ft_m.find('b');

//         // // exit(1);
//         // cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second);
//         // m.erase(it);       // erasing by iterator
//         // ft_m.erase(ft_it); // erasing by iterator

//         // cond = cond && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         // int ret = m.erase('c');       // erasing by key
//         // int ft_ret = ft_m.erase('c'); // erasing by key
//         // std::cout << ret << " x " << ft_ret << std::endl;

//         // cond = cond && ret == ft_ret && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         // it = m.find('e');
//         // ft_it = ft_m.find('e');

//         // cond = cond && (it->first == ft_it->first) && (it->second == ft_it->second) && m.size() == ft_m.size();

//         // m.erase(it, m.end());          // erasing by range
//         // ft_m.erase(ft_it, ft_m.end()); // erasing by range

//         // cond = cond && m.empty() == ft_m.empty() && comparemaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

//         /* ---------- Testing some edge cases ---------- */

//         std::map<int, std::string> m2;
//         ft::map<int, std::string> ft_m2;

//         for (size_t i = 0; i < 4; i++)
//         {
//             m2.insert(std::make_pair(i, "string1"));
//             ft_m2.insert(ft::make_pair(i, "string1"));
//         }

//         std::map<int, std::string>::reverse_iterator it2 = m2.rbegin();
//         ft::map<int, std::string>::reverse_iterator ft_it2 = ft_m2.rbegin();

//         // m2.erase(m2.begin());
//         // ft_m2.erase(ft_m2.begin());
//         // ft_m2.printTree();

//         cond =/*cond &&*/ m2.size() == ft_m2.size() && comparemaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

//         std::cout << std::endl;
//         ft_m2.printTree();
//         // std::cout << ft_it2->first << std::endl;
//         // std::cout << it2->first << std::endl;
//         m2.erase(it2->first);
//         ft_m2.erase(ft_it2->first);
//         ft_m2.printTree();

//         cond = /*cond && */m2.size() == ft_m2.size() && comparemaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

//         std::map<int, std::string> m3;
//         ft::map<int, std::string> ft_m3;
//         std::vector<int> vec;
//         std::vector<int> ft_vec;
//         // std::random_device randDev;
//         // std::mt19937 generator(randDev());
//         // std::uniform_int_distribution<int> distr(0, 1e8);

//         for (size_t i = 0; i < 1e3; i++)
//         // // for (size_t i = 0; i < 1e6; i++)
//         {
//             m3.insert(std::make_pair(i, "string1"));
//             ft_m3.insert(ft::make_pair(i, "string1"));
//         }

//         // for (size_t i = 0; i < 1e3; i++)
//         // // // for (size_t i = 0; i < 1e6; ++i)
//         // {
//         //     int n = distr(generator);
//         //     int ret1 = m3.erase(n);
//         //     int ret2 = ft_m3.erase(n);

//         //     if (ret1 != ret2)
//         //     {
//         //         cond = false;
//         //         break;
//         //     }
//         // }

//         if (!m3.empty())
//         {
//             m3.erase(m3.begin(), m3.end());
//             m3.erase(m3.begin(), m3.end());
//         }
//         if (!ft_m3.empty())
//         {
//             ft_m3.erase(ft_m3.begin(), ft_m3.end());
//             ft_m3.erase(ft_m3.begin(), ft_m3.end());
//         }
//         std::cout << "gg\n";
//         cond = cond && (m3.size() == ft_m3.size() && comparemaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()));

//         EQUAL(cond);
//     }
// }