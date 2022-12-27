/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 15:50:40 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/27 13:33:38 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <iterator>
#include <ctime>
#include <iomanip>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include "vector.hpp"

#define BLUE "\e[0;34m"
#define RED "\e[0;31m"
#define GREEN "\e[0;32m"
#define YELLOW "\e[1;33m"
#define RESET "\e[0m"

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mOK\033[0m\n") : (std::cout << "\033[1;31mKO\033[0m\n"))
// #define TIME_FAC 3 // the ft::vector methods can be slower up to std::vector methods * TIME_FAC (MAX 20)

void iterator_tests()
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< vector iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::vector ---------*/
    std::vector<int> v(3, 4);
    std::vector<int>::iterator it, it1;
    it = v.begin();
    it1 = v.begin() + 1;
    /*----------------------------------*/
    /*------------ ft::vector ---------*/
    ft::vector<int> my_v(3, 4);
    ft::vector<int>::iterator my_it, my_it1, tmp;
    my_it = my_v.begin();
    my_it1 = my_v.begin() + 1;
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::vector<int>::iterator ob(my_it);
        EQUAL(&(*my_it) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " iterator to const_iterator "
              << "] --------------------]\t\t\033[0m";
    {
        ft::vector<int>::const_iterator c_it, c_ob(my_it);
        c_it = my_it;
        EQUAL(&(*my_it) == &(*c_it) && (&(*my_it) == &(*c_ob)));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it > it1) == (my_it > my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it >= it1) == (my_it >= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it < it1) == (my_it < my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it <= it1) == (my_it <= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((*my_it = 6) == 6) && (*my_it == *(my_v.begin())));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- std::vector-------------------- */
        std::vector<std::string> v(3, "hello");
        std::vector<std::string>::iterator it = v.begin();
        /*---------------------------------------------- */
        /*--------------- ft::vector-------------------- */
        ft::vector<std::string> my_v(3, "hello");
        ft::vector<std::string>::iterator my_it = my_v.begin();
        /*---------------------------------------------- */
        EQUAL(it->length() == my_it->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_it += 1;
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_it -= 1;
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_it[0] = 5) == 5) && (*my_it == 5));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
              << "] --------------------]\t\t\033[0m";
    ++my_it; // I incremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
              << "] --------------------]\t\t\033[0m";
    --my_it; // I decremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));



    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));    
    
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (it1 - it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it++;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it--;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
}

void const_iterator_tests()
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< vector const_iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::vector ---------*/
    std::vector<int> v(3, 4);
    std::vector<int>::const_iterator it, it1;
    it = v.begin();
    it1 = v.begin() + 1;
    /*----------------------------------*/
    /*------------ ft::vector ---------*/
    ft::vector<int> my_v(3, 4);
    ft::vector<int>::const_iterator my_it, my_it1, tmp;
    my_it = my_v.begin();
    my_it1 = my_v.begin() + 1;
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::vector<int>::const_iterator ob(my_it);
        EQUAL(&(*my_it) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it > it1) == (my_it > my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it >= it1) == (my_it >= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it < it1) == (my_it < my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((it <= it1) == (my_it <= my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(*my_it == *(my_v.begin()) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- std::vector-------------------- */
        std::vector<std::string> v(3, "hello");
        std::vector<std::string>::const_iterator it = v.begin();
        /*---------------------------------------------- */
        /*--------------- ft::vector-------------------- */
        ft::vector<std::string> my_v(3, "hello");
        ft::vector<std::string>::const_iterator my_it = my_v.begin();
        /*---------------------------------------------- */
        EQUAL(it->length() == my_it->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_it += 1;
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_it -= 1;
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((my_it[0] == *(my_v.begin())) && (&(my_it[0]) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++it operator "
              << "] --------------------]\t\t\033[0m";
    ++my_it; // I incremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*my_it1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --it operator "
              << "] --------------------]\t\t\033[0m";
    --my_it; // I decremented here to make sure that the object changes
    EQUAL(&(*my_it) == &(*(my_it1 - 1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(&(*(1 + my_it)) == &(*(my_it1)) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (it1 - it) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_it1 - my_it == 1)) && ((my_it - my_it1) == -1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it++ operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it++;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*my_it1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " it-- operator "
              << "] --------------------]\t\t\033[0m";
    tmp = my_it--;
    EQUAL(&(*my_it) != &(*tmp) && (&(*my_it) == &(*(my_v.begin()))));
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void reverse_iterator_tests()
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< reverse_iterator tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::reverse_iterator ---------*/
    std::vector<int> v(3, 4);
    std::reverse_iterator<std::vector<int>::iterator> rit(v.end()), rit_1(v.end() - 1);
    /*----------------------------------*/
    /*------------ ft::reverse_iterator ---------*/
    ft::reverse_iterator<std::vector<int>::iterator> my_rit(v.end()), my_rit1(v.end() - 1);
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::reverse_iterator<std::vector<int>::iterator> ob(my_rit);
        EQUAL(&(*my_rit) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " riterator to const_riterator "
              << "] --------------------]\t\t\033[0m";
    {
        ft::vector<int> v(4, 5);
        ft::vector<int>::reverse_iterator my_rit2(v.end());
        ft::vector<int>::const_reverse_iterator c_it, c_ob(v.end());
        c_it = my_rit2;
        EQUAL(&(*my_rit2) == &(*c_it) && (&(*my_rit2) == &(*c_ob)));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*rit) == &(*rit_1.base())) && (&(*my_rit) == &(*my_rit1.base())));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit == rit_1) == (my_rit == my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit != rit_1) == (my_rit != my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit > rit_1) == (my_rit > my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit >= rit_1) == (my_rit >= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit < rit_1) == (my_rit < my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit <= rit_1) == (my_rit <= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((*my_rit == *(v.end() - 1)) && (&(*my_rit) == &(*(v.end() - 1)))) && ((*rit == *(v.end() - 1)) && (&(*rit) == &(*(v.end() - 1)))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<std::string> v(3, "hello");
        std::reverse_iterator<std::vector<std::string>::iterator> rit(v.end());
        ft::reverse_iterator<std::vector<std::string>::iterator> my_rit(v.end());
        EQUAL(rit->length() == my_rit->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(my_rit + 1)) == &(*my_rit1)) && (&(*(rit + 1)) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_rit += 1;
    rit += 1;
    EQUAL((&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_rit -= 1;
    rit -= 1;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit[0] = 5) == 5) && (rit[0] == 5));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator "
              << "] --------------------]\t\t\033[0m";
    ++my_rit; // I incremented here to make sure that the object changes
    ++rit;
    EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator "
              << "] --------------------]\t\t\033[0m";
    --my_rit; // I incremented here to make sure that the object changes
    --rit;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(2 + my_rit)) == &(*(1 + my_rit1))) && (&(*(2 + rit)) == &(*(1 + rit_1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (rit1 - rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit - my_rit1) == (rit - rit_1)) && ((my_rit1 - my_rit) == (rit_1 - rit)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::reverse_iterator<std::vector<int>::iterator> tmp(rit++);
        ft::reverse_iterator<std::vector<int>::iterator> my_tmp(my_rit++);
        EQUAL((&(*tmp) == &(*(--rit))) && (&(*my_tmp) == &(*(--my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::reverse_iterator<std::vector<int>::iterator> tmp(rit--);
        ft::reverse_iterator<std::vector<int>::iterator> my_tmp(my_rit--);
        EQUAL((&(*tmp) == &(*(++rit))) && (&(*my_tmp) == &(*(++my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " *rit++ test "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<char> v(10);
        std::string res, my_res;
        std::reverse_iterator<std::vector<char>::iterator> start(v.end()), end(v.begin());
        ft::reverse_iterator<std::vector<char>::iterator> my_start(v.end()), my_end(v.begin());

        for (size_t i = 0; i < 10; ++i)
            v[i] = '0' + i;
        while (start != end)
            res.push_back(*start++);
        while (my_start != my_end)
            my_res.push_back(*my_start++);
        EQUAL(res == my_res);
    }
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void reverse_iterator_vector_tests()
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< reverse_iterator with ft::vector >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    /*------------ std::reverse_iterator ---------*/
    std::vector<int> v(3, 4);
    std::vector<int>::reverse_iterator rit(v.end()), rit_1(v.end() - 1);
    /*----------------------------------*/
    /*------------ ft::reverse_iterator ---------*/
    ft::vector<int> my_v(3, 4);
    ft::vector<int>::reverse_iterator my_rit(my_v.end()), my_rit1(my_v.end() - 1);
    /*----------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        ft::vector<int>::reverse_iterator ob(my_rit);
        EQUAL(&(*my_rit) == &(*ob));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " base function "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*rit) == &(*rit_1.base())) && (&(*my_rit) == &(*my_rit1.base())));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " == operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit == rit_1) == (my_rit == my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " != operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit != rit_1) == (my_rit != my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " > operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit > rit_1) == (my_rit > my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " >= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit >= rit_1) == (my_rit >= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " < operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit < rit_1) == (my_rit < my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " <= operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((rit <= rit_1) == (my_rit <= my_rit1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " * operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((*my_rit == *(my_v.end() - 1)) && (&(*my_rit) == &(*(my_v.end() - 1)))) && ((*rit == *(v.end() - 1)) && (&(*rit) == &(*(v.end() - 1)))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -> operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<std::string> v(3, "hello");
        ft::vector<std::string> my_v(3, "hello");
        std::vector<std::string>::reverse_iterator rit(v.end());
        ft::vector<std::string>::reverse_iterator my_rit(my_v.end());
        EQUAL(rit->length() == my_rit->length());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(my_rit + 1)) == &(*my_rit1)) && (&(*(rit + 1)) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " += operator "
              << "] --------------------]\t\t\033[0m";
    my_rit += 1;
    rit += 1;
    EQUAL((&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " -= operator "
              << "] --------------------]\t\t\033[0m";
    my_rit -= 1;
    rit -= 1;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " [] operator "
              << "] --------------------]\t\t\033[0m";
    EQUAL((my_rit[0] = 5) == 5);
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " ++rit operator "
              << "] --------------------]\t\t\033[0m";
    ++my_rit; // I incremented here to make sure that the object changes
    ++rit;
    EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " --rit operator "
              << "] --------------------]\t\t\033[0m";
    --my_rit; // I incremented here to make sure that the object changes
    --rit;
    EQUAL((&(*my_rit) == &(*(my_rit1 - 1))) && (&(*rit) == &(*(rit_1 - 1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " + operator (n + rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL((&(*(2 + my_rit)) == &(*(1 + my_rit1))) && (&(*(2 + rit)) == &(*(1 + rit_1))));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " - operator (rit1 - rit) "
              << "] --------------------]\t\t\033[0m";
    EQUAL(((my_rit - my_rit1) == (rit - rit_1)) && ((my_rit1 - my_rit) == (rit_1 - rit)));
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit++ operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<int>::reverse_iterator tmp(rit++);
        ft::vector<int>::reverse_iterator my_tmp(my_rit++);
        EQUAL((&(*tmp) == &(*(--rit))) && (&(*my_tmp) == &(*(--my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " rit-- operator "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<int>::reverse_iterator tmp(rit--);
        ft::vector<int>::reverse_iterator my_tmp(my_rit--);
        EQUAL((&(*tmp) == &(*(++rit))) && (&(*my_tmp) == &(*(++my_rit))));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " *rit++ test "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<char> v(10);
        ft::vector<char> my_v(10);
        std::string res, my_res;
        std::vector<char>::reverse_iterator start(v.end()), end(v.begin());
        ft::vector<char>::reverse_iterator my_start(my_v.end()), my_end(my_v.begin());
        for (size_t i = 0; i < 10; ++i)
            v[i] = '0' + i;
        size_t i = 0;
        for (ft::vector<char>::iterator it = my_v.begin(); it != my_v.end(); ++it)
            *it = '0' + i++;
        while (start != end)
            res.push_back(*start++);
        while (my_start != my_end)
            my_res.push_back(*my_start++);
        EQUAL(res == my_res);
    }
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

void ft_vector_tests()
{
    std::cout << "\033[1;36m<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< vector tests >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " fill constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- fill tow vectors with a 10 strings ------*/
        ft::vector<std::string> my_v(10, "fill constructor test");
        std::vector<std::string> v(10, "fill constructor test");
        /*---------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, my_res;
        /*---------------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) // fill res from std::vector
            res += *it;

        for (ft::vector<std::string>::iterator it = my_v.begin(); it != my_v.end(); ++it) // fill my_res from ft::vector
            my_res += *it;
        EQUAL(res == my_res);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " range constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*--------------- fill std::vector with 10 strings and ft::vector with range of iterators ------*/
        std::vector<std::string> v(10, "range constructor test");
        ft::vector<std::string> my_v(10, "range constructor test");
        ft::vector<std::string> my_v1(my_v.begin(), my_v.end()); // this one is to check if the range works with ft::vector
        /*----------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, my_res, my_res1;
        /*--------------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); ++it) // fill res from std::vector
            res += *it;

        for (ft::vector<std::string>::iterator it = my_v.begin(); it != my_v.end(); ++it) // fill my_res from ft::vector
            my_res += *it;

        for (ft::vector<std::string>::iterator it = my_v1.begin(); it != my_v1.end(); ++it) // fill my_res1 from ft::vector
            my_res1 += *it;
        EQUAL(res == my_res && my_res == my_res1);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " copy constructor "
              << "] --------------------]\t\t\033[0m";
    {
        /*---------------------------- declare a vector and fill with 'a', and create a copy of it ------------------*/
        ft::vector<char> v1(10, 'a');
        ft::vector<char> copy_v(v1);
        /*-----------------------------------------------------------------------------------------------------------*/
        /*--------------- declare tow strings to store the results ------*/
        std::string res, res1;
        /*--------------------------------------------------------*/
        for (ft::vector<char>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<char>::iterator it = copy_v.begin(); it != copy_v.end(); ++it) // fill res from copy_v
            res1 += *it;
        EQUAL(res == res1);
    }
    /*------------------------------------------ = operator tests --------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 1 : test with equale size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size = rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string1");
        std::vector<std::string> v2(10, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string1");
        ft::vector<std::string> ft_v2(10, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 2 : test with diff size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size < rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string1");
        std::vector<std::string> v2(20, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string1");
        ft::vector<std::string> ft_v2(20, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 3 : test with diff size vecotrs ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size > rhs.size) "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(20, "string1");
        std::vector<std::string> v2(10, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(20, "string1");
        ft::vector<std::string> ft_v2(10, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 4 : test with one empty vector ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size = 0) "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1;
        std::vector<std::string> v2(10, "string2");
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1;
        ft::vector<std::string> ft_v2(10, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    /*------------------------------------------ test 5 : test with one empty vector ----------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (rhs.size = 0) "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<std::string> v2;
        v1 = v2;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<std::string> ft_v2;
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    /*-------------------------------------------------------------------------------------------------------------------------------------------------------*/
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " begin and end methods "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<std::string> const v2(10, "string2");
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<std::string> const ft_v2(10, "string2");
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        std::string res, ft_res, c_res, c_ft_res;
        /*----------------------------------------------------*/
        for (std::vector<std::string>::iterator it = v1.begin(); it != v1.end(); ++it) // fill res from v1
            res += *it;
        for (std::vector<std::string>::const_iterator rit = v2.begin(); rit != v2.end(); ++rit) // fill c_res from const v1
            c_res += *rit;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
            ft_res += *it;
        for (ft::vector<std::string>::const_iterator rit = ft_v2.begin(); rit != ft_v2.end(); ++rit) // fill c_ft_res from const ft_v1
            c_ft_res += *rit;

        EQUAL(res == ft_res && c_res == c_ft_res);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " size method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");          // fill constructor
        std::vector<std::string> v2;                         // empty constructor
        std::vector<std::string> v3(v1.begin(), v1.end());   // range constructor with normal iterators
        std::vector<std::string> v4(v3);                     // copy constructor
        std::vector<std::string> v5(v1.rbegin(), v1.rend()); // range constructor with reverse iterators
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<std::string> ft_v2;
        ft::vector<std::string> ft_v3(ft_v1.begin(), ft_v1.end());
        ft::vector<std::string> ft_v4(ft_v1);
        ft::vector<std::string> ft_v5(ft_v1.rbegin(), ft_v1.rend());
        /*----------------------------------------------------*/
        EQUAL(v1.size() == ft_v1.size() && v2.size() == ft_v2.size() && v3.size() == ft_v3.size() && v4.size() == ft_v4.size());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " capacity method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");          // fill constructor
        std::vector<std::string> v2;                         // empty constructor
        std::vector<std::string> v3(v1.begin(), v1.end());   // range constructor with normal iterators
        std::vector<std::string> v4(v3);                     // copy constructor
        std::vector<std::string> v5(v1.rbegin(), v1.rend()); // range constructor with reverse iterators
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<std::string> ft_v2;
        ft::vector<std::string> ft_v3(ft_v1.begin(), ft_v1.end());
        ft::vector<std::string> ft_v4(ft_v1);
        ft::vector<std::string> ft_v5(ft_v1.rbegin(), ft_v1.rend());
        /*----------------------------------------------------*/
        EQUAL(v1.capacity() == ft_v1.capacity() && v2.capacity() == ft_v2.capacity() && v3.capacity() == ft_v3.capacity() && v4.capacity() == ft_v4.capacity());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " max_size method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/

        std::vector<std::string> v1(10, "string");
        std::vector<int> v2;
        std::vector<double> v4;
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<int> ft_v2;
        ft::vector<double> ft_v4;
        /*----------------------------------------------------*/
        EQUAL(v1.max_size() == ft_v1.max_size() && v2.max_size() == ft_v2.max_size() && v4.max_size() == ft_v4.max_size());
    }




    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " resize method "
              << "] --------------------]\t\t\033[0m";
    {
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, s4, ft_s1, ft_s2, ft_s3, ft_s4;
        std::string sit1, sit2, sit3, ft_sit1, ft_sit2, ft_sit3; // strings to store the result by iterators
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, z4, ft_z1, ft_z2, ft_z3, ft_z4;
        size_t c1, c2, c3, c4, ft_c1, ft_c2, ft_c3, ft_c4;
        /*
         * iterators to check the iterator validity
         *  it : iterator, eit : iterator to the end
         */
        std::vector<std::string>::iterator valid_it, valid_eit;
        ft::vector<std::string>::iterator ft_valid_it, ft_valid_eit;
        /*
         * test with n greater than vector capacity
         */
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        v1.resize(1e6, "hello");
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft_v1.resize(1e6, "hello");

        z1 = v1.size();
        ft_z1 = ft_v1.size();
        c1 = v1.capacity();
        ft_c1 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1[i];

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s1 += *it;
        /*----------------------------------------------------*/
        /*
         *	test with n lesser than capacity and greater than size
         */
        /*------------------ std::vectors ---------------------*/
        v1.resize(20);
        valid_it = v1.begin();
        valid_eit = v1.end();
        v1.resize(1e5);
        /*------------------ ft::vectors ---------------------*/
        ft_v1.resize(20);
        ft_valid_it = ft_v1.begin();
        ft_valid_eit = ft_v1.end();
        ft_v1.resize(1e5);

        z2 = v1.size();
        ft_z2 = ft_v1.size();
        c2 = v1.capacity();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s2 += v1[i];

        for (; valid_it != valid_eit; ++valid_it)
            sit1 += *valid_it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s2 += *it;

        for (; ft_valid_it != ft_valid_eit; ++ft_valid_it)
            ft_sit1 += *ft_valid_it;
        /*----------------------------------------------------*/
        /*
         * test with n lesser than capacity and lesser an size
         */
        /*------------------ std::vectors ---------------------*/
        valid_it = v1.begin();
        v1.resize(50);
        /*------------------ ft::vectors ---------------------*/
        ft_valid_it = ft_v1.begin();
        ft_v1.resize(50);

        z3 = v1.size();
        ft_z3 = ft_v1.size();
        c3 = v1.capacity();
        ft_c3 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1[i];

        for (; valid_it != v1.end(); ++valid_it)
            sit2 += *valid_it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s3 += *it;

        for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
            ft_sit2 += *ft_valid_it;
        /*----------------------------------------------------*/
        /*
         * test with n = 0
         */
        /*------------------ std::vectors ---------------------*/
        valid_it = v1.begin();
        v1.resize(0, "string4");
        /*------------------ ft::vectors ---------------------*/
        ft_valid_it = ft_v1.begin();
        ft_v1.resize(0, "string4");

        z4 = v1.size();
        ft_z4 = ft_v1.size();
        c4 = v1.capacity();
        ft_c4 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s4 += v1[i];

        for (; valid_it != v1.end(); ++valid_it)
            sit3 += *valid_it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s4 += *it;

        for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
            ft_sit3 += *ft_valid_it;
        /*----------------------------------------------------*/
        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1 && sit1 == ft_sit1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3 && sit2 == ft_sit2) && (s4 == ft_s4 && z4 == ft_z4 && c4 == ft_c4 && sit3 == ft_sit3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " empty method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<int> v2;
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<int> ft_v2;

        EQUAL(v1.empty() == ft_v1.empty() && v2.empty() == ft_v2.empty());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " reserve method "
              << "] --------------------]\t\t\033[0m";
    {
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        std::string sit1, ft_sit1; // strings to store the result by iterators
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        /*
         * iterators to check the iterator validity
         *  it : iterator, eit : iterator to the end
         */
        std::vector<std::string>::iterator valid_it, valid_eit;
        ft::vector<std::string>::iterator ft_valid_it, ft_valid_eit;
        // bool to check if the function throw or not
        bool exec_throwed = false;
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> v2;
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<char> ft_v2;
        try
        {
            ft_v1.reserve(ft_v1.max_size() + 1);
        }
        catch (std::length_error const &e)
        {
            (void)e;
            exec_throwed = true;
        }
        v1.reserve(100);
        ft_v1.reserve(100);

        z1 = v1.size();
        ft_z1 = ft_v1.size();
        c1 = v1.capacity();
        ft_c1 = ft_v1.capacity();

        for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1[i];

        ft_valid_it = ft_v1.begin();
        for (; ft_valid_it != ft_v1.end(); ++ft_valid_it)
            ft_s1 += *ft_valid_it;

        valid_it = v1.begin();
        valid_eit = v1.end();
        ft_valid_it = ft_v1.begin();
        ft_valid_eit = ft_v1.end();
        v1.reserve(50);
        ft_v1.reserve(50);

        z2 = v1.size();
        ft_z2 = ft_v1.size();
        c2 = v1.capacity();
        ft_c2 = ft_v1.capacity();

        for (size_t i = 0; i < v1.size(); ++i)
            s2 += v1[i];

        for (; valid_it != valid_eit; ++valid_it)
            sit1 += *valid_it;

        for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it)
            ft_s2 += *it;

        for (; ft_valid_it != ft_valid_eit; ++ft_valid_it)
            ft_sit1 += *ft_valid_it;

        v2.reserve(200);
        ft_v2.reserve(200);
        z3 = v2.size();
        ft_z3 = ft_v2.size();
        c3 = v2.capacity();
        ft_c3 = ft_v2.capacity();

        for (size_t i = 0; i < v2.size(); ++i)
            s3 += v2[i];

        for (ft::vector<char>::iterator it = ft_v2.begin(); it != ft_v2.end(); ++it)
            ft_s3 += *it;

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1 && sit1 == ft_sit1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3) && exec_throwed);
    }
    
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator[] method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> const v2(10, '9');
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<char> const ft_v2(10, '9');
        /*
         * Strings to store the results
         */
        std::string s1, s2, ft_s1, ft_s2;

        for (size_t i = 0; i < v1.size(); ++i)
        {
            if (i == v1.size() - 1)
                v1[i] = "other";
            s1 += v1[i];
        }

        for (size_t i = 0; i < ft_v1.size(); ++i)
        {
            if (i == ft_v1.size() - 1)
                ft_v1[i] = "other";
            ft_s1 += ft_v1[i];
        }

        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2[i];

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2[i];

        EQUAL(s1 == ft_s1 && s2 == ft_s2);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " at method "
              << "] --------------------]\t\t\033[0m";
    {
        
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> const v2(10, '9');
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<char> const ft_v2(10, '9');
        /*
         * Strings to store the results
         */
        std::string s1, s2, ft_s1, ft_s2;
        // bool to check if an exception is throwed
        bool exce_throwed = false;

        try
        {
            ft_v1.at(20);
        }
        catch (std::out_of_range const &e)
        {
            (void)e;
            exce_throwed = true;
        }
        for (size_t i = 0; i < v1.size(); ++i)
        {
            if (i == v1.size() - 1)
                v1.at(i) = "other";
            s1 += v1.at(i);
        }

        for (size_t i = 0; i < ft_v1.size(); ++i)
        {
            if (i == ft_v1.size() - 1)
                ft_v1.at(i) = "other";
            ft_s1 += ft_v1.at(i);
        }

        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);
        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL(s1 == ft_s1 && s2 == ft_s2 && exce_throwed);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " front method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<int> const v2(10, 9);
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<int> const ft_v2(10, 9);

        v1.front() = "LEET";
        ft_v1.front() = "LEET";
        EQUAL(v1.front() == ft_v1.front() && v2.front() == ft_v2.front());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " back method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<int> const v2(10, 9);
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<int> const ft_v2(10, 9);

        v1.back() = "LEET";
        ft_v1.back() = "LEET";
        EQUAL(v1.back() == ft_v1.back() && v2.back() == ft_v2.back());
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " assign(fill) method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(10, "string2");
        std::vector<char> v2;
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(10, "string2");
        ft::vector<char> ft_v2;
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        // test for n greater than the vector capactiy
        v1.assign(20, "assign");
        ft_v1.assign(20, "assign");

        z1 = v1.size();
        ft_z1 = ft_v1.size();
        c1 = v1.capacity();
        ft_c1 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s1 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s1 += ft_v1.at(i);
        // test for n lesser than the vector capactiy
        v1.assign(10, "less");
        ft_v1.assign(10, "less");

        z2 = v1.size();
        ft_z2 = ft_v1.size();
        c2 = v1.capacity();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s3 += ft_v1.at(i);
        // test for empty vectors
        v2.assign(20, 'h');
        ft_v2.assign(20, 'h');

        z3 = v2.size();
        ft_z3 = ft_v2.size();
        c3 = v2.capacity();
        ft_c3 = ft_v2.capacity();
        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " assign(range) method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v1(20, "less");
        std::vector<std::string> v2;
        std::vector<std::string> v3(10, "string2");
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v1(20, "less");
        ft::vector<std::string> ft_v2;
        ft::vector<std::string> ft_v3(10, "string2");
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        // test for n greater than the vector capactiy
        v3.assign(v1.begin(), v1.end());
        ft_v3.assign(v1.begin(), v1.end());

        z1 = v3.size();
        c1 = v3.capacity();
        ft_z1 = ft_v3.size();
        ft_c1 = ft_v3.capacity();
        for (size_t i = 0; i < v3.size(); ++i)
            s1 += v3.at(i);

        for (size_t i = 0; i < ft_v3.size(); ++i)
            ft_s1 += ft_v3.at(i);
        // test for n lesser than the vector capactiy
        v1.assign(v3.begin(), v3.end());
        ft_v1.assign(ft_v3.begin(), ft_v3.end());

        z2 = v1.size();
        c2 = v1.capacity();
        ft_z2 = ft_v1.size();
        ft_c2 = ft_v1.capacity();
        for (size_t i = 0; i < v1.size(); ++i)
            s3 += v1.at(i);

        for (size_t i = 0; i < ft_v1.size(); ++i)
            ft_s3 += ft_v1.at(i);
        // test for empty vectors
        v2.assign(v1.begin(), v1.end());
        ft_v2.assign(ft_v1.begin(), ft_v1.end());

        z3 = v2.size();
        c3 = v2.capacity();
        ft_z3 = ft_v2.size();
        ft_c3 = ft_v2.capacity();
        for (size_t i = 0; i < v2.size(); ++i)
            s2 += v2.at(i);

        for (size_t i = 0; i < ft_v2.size(); ++i)
            ft_s2 += ft_v2.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }

    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " push_back method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v;
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v;
        /*
         * Strings to store the results
         */
        std::string s1, s2, s3, ft_s1, ft_s2, ft_s3;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, z2, z3, ft_z1, ft_z2, ft_z3;
        size_t c1, c2, c3, ft_c1, ft_c2, ft_c3;
        ft::vector<std::string>::iterator ft_it;
        // test for an empty vector
        v.push_back("hello");
        ft_v.push_back("hello");
        ft_it = ft_v.begin();
        ft_it->length();

        z1 = v.size();
        c1 = v.capacity();
        ft_z1 = ft_v.size();
        ft_c1 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s1 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s1 += ft_v.at(i);
        /*---------------------------------------------*/
        // test for a vector with capacity >= size + the new element
        v.reserve(30);
        ft_v.reserve(30);
        v.push_back("string");
        ft_v.push_back("string");
        v.push_back("string");
        ft_v.push_back("string");

        z2 = v.size();
        c2 = v.capacity();
        ft_z2 = ft_v.size();
        ft_c2 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s2 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s2 += ft_v.at(i);
        /*---------------------------------------------------------*/
        // test for a vector with capactiy < size + the new element
        for (size_t i = 0; i < 100; ++i)
            v.push_back("string");

        for (size_t i = 0; i < 100; ++i)
            ft_v.push_back("string");

        z3 = v.size();
        c3 = v.capacity();
        ft_z3 = ft_v.size();
        ft_c3 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s3 += v.at(i);

        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s3 += ft_v.at(i);

        EQUAL((s1 == ft_s1 && z1 == ft_z1 && c1 == ft_c1) && (s2 == ft_s2 && z2 == ft_z2 && c2 == ft_c2) && (s3 == ft_s3 && z3 == ft_z3 && c3 == ft_c3));
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " pop_back method "
              << "] --------------------]\t\t\033[0m";
    {
        /*------------------ std::vectors ---------------------*/
        std::vector<std::string> v(20, "string");
        /*------------------ std::vectors ---------------------*/
        ft::vector<std::string> ft_v(20, "string");
        /*
         * Strings to store the results
         */
        std::string s1, ft_s1;
        /*
         * Var to store the size and the capacity
         */
        size_t z1, ft_z1;
        size_t c1, ft_c1;
        v.pop_back();
        ft_v.pop_back();
        z1 = v.size();
        ft_z1 = ft_v.size();
        c1 = v.capacity();
        ft_c1 = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            s1 += v[i];
        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_s1 += ft_v[i];
        EQUAL(z1 == ft_z1 && c1 == ft_c1 && s1 == ft_s1);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (single element) "
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
        ft::vector<std::string>::iterator ft_it;
        std::vector<std::string>::iterator it;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;
            it = v.insert(v.begin(), "hello");
            ft_it = ft_v.insert(ft_v.begin(), "hello");
            ft_it->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c) && (*ft_it == *it));
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;

            it = v.insert(v.end(), "hello");
            ft_it = ft_v.insert(ft_v.end(), "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 2: the vector capacity >= size + the new element ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");
            ft::vector<std::string>::iterator valid_it;

            v.reserve(30);
            ft_v.reserve(30);
            valid_it = ft_v.begin();
            it = v.insert(v.begin() + 10, "hello");
            ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it) && (&(*valid_it) == &(*ft_v.begin())));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 3: the vector capacity < size + the new element ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            it = v.insert(v.begin() + 10, "hello");
            ft_it = ft_v.insert(ft_v.begin() + 10, "hello");
            ft_it->length();

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (*it == *ft_it));
        }
        /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (fill) "
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
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;
            v.insert(v.begin(), 100, "hello");
            ft_v.insert(ft_v.begin(), 100, "hello");
            ft_v.begin()->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // insert at the end
        {
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;

            v.insert(v.end(), "hello");
            ft_v.insert(ft_v.end(), "hello");
            ft_v.begin()->length();

            str.clear();
            ft_str.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 2: the vector capacity >= size + n ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");
            ft::vector<std::string>::iterator valid_it;

            v.reserve(100);
            ft_v.reserve(100);
            valid_it = ft_v.begin();
            v.insert(v.begin() + 15, 70, "hello");
            ft_v.insert(ft_v.begin() + 15, 70, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*ft_v.begin())));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 3: the vector capacity < size + n && n > size ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, 100, "hello");
            ft_v.insert(ft_v.begin() + 10, 100, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 4: the vector capacity < size + n && n <= size ----------------------------------------*/
        {
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, 15, "hello");
            ft_v.insert(ft_v.begin() + 10, 15, "hello");

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " insert method (range) "
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
        /*
         * bool to store the comparison
         */
        bool cond;

        /*------------------------------- test 1: empty vector ----------------------------------------*/
        // insert at the begin
        {
            std::vector<std::string> v1(300, "string");
            std::vector<std::string> v;
            ft::vector<std::string> ft_v;
            v.insert(v.begin(), v1.begin(), v1.end());
            ft_v.insert(ft_v.begin(), v1.begin(), v1.end());
            ft_v.begin()->length();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        // insert at the end
        {
            // std::vector<std::string> v;
            // ft::vector<std::string> v1(300, "string");
            // ft::vector<std::string> ft_v;

            // v.insert(v.end(), v1.begin(), v1.end());
            // ft_v.insert(ft_v.end(), v1.begin(), v1.end());
            // ft_v.begin()->length();

            // str.clear();
            // ft_str.clear();

            // s = v.size();
            // ft_s = ft_v.size();
            // c = v.capacity();
            // ft_c = ft_v.capacity();
            // for (size_t i = 0; i < v.size(); ++i)
            //     str += v[i];
            // for (size_t i = 0; i < ft_v.size(); ++i)
            //     ft_str += ft_v[i];
            // cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 2: the vector capacity >= size + n ----------------------------------------*/
        {
            std::vector<std::string> v1(70, "hello");
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");
            ft::vector<std::string>::iterator valid_it;

            v.reserve(100);
            ft_v.reserve(100);
            valid_it = ft_v.begin();
            v.insert(v.begin() + 15, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 15, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*ft_v.begin())));
        }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 3: the vector capacity < size + n && n > size ----------------------------------------*/
        // {
        //     ft::vector<std::string> v1(100, "hello");
        //     std::vector<std::string> v(20, "string");
        //     ft::vector<std::string> ft_v(20, "string");

        //     v.insert(v.begin() + 10, v1.begin(), v1.end());
        //     ft_v.insert(ft_v.begin() + 10, v1.begin(), v1.end());

        //     str.clear();
        //     ft_str.clear();
        //     s = v.size();
        //     ft_s = ft_v.size();
        //     c = v.capacity();
        //     ft_c = ft_v.capacity();
        //     for (size_t i = 0; i < v.size(); ++i)
        //         str += v[i];
        //     for (size_t i = 0; i < ft_v.size(); ++i)
        //         ft_str += ft_v[i];
        //     cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        // }
        /*---------------------------------------------------------------------------------------------------*/
        /*------------------------------- test 4: the vector capacity < size + n && n <= size ----------------------------------------*/
        {
            std::vector<std::string> v1(15, "hello");
            std::vector<std::string> v(20, "string");
            ft::vector<std::string> ft_v(20, "string");

            v.insert(v.begin() + 10, v1.begin(), v1.end());
            ft_v.insert(ft_v.begin() + 10, v1.begin(), v1.end());

            str.clear();
            ft_str.clear();
            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];
            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*---------------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    
    
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " erase method (single element) "
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
        /*
         * bool to store the comparison
         */
        bool cond;

        std::vector<std::string> v(200, "hello");
        ft::vector<std::string> ft_v(200, "hello");
        ft::vector<std::string>::iterator valid_it;
        std::vector<std::string>::iterator it;
        ft::vector<std::string>::iterator ft_it;
        valid_it = ft_v.begin() + 99;
        it = v.erase(v.begin() + 100);
        ft_it = ft_v.erase(ft_v.begin() + 100);
        ft_it->length();

        s = v.size();
        ft_s = ft_v.size();
        c = v.capacity();
        ft_c = ft_v.capacity();
        for (size_t i = 0; i < v.size(); ++i)
            str += v[i];
        for (size_t i = 0; i < ft_v.size(); ++i)
            ft_str += ft_v[i];
        cond = ((str == ft_str) && (s == ft_s) && (c == ft_c) && (&(*valid_it) == &(*(ft_v.begin() + 99))));
        // cond = (cond && (std::distance(v.begin(), it) == std::distance(ft_v.begin(), ft_it)));
        EQUAL(cond);
    }
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
        bool cond=false;
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
            // std::vector<std::string> v(100, "hello");
            // ft::vector<std::string> ft_v(100, "hello");

            // it = v.erase(v.begin() + 60, v.end());
            // ft_it = ft_v.erase(ft_v.begin() + 60, ft_v.end());

            // str.clear();
            // ft_str.clear();
            // s = v.size();
            // ft_s = ft_v.size();
            // c = v.size();
            // ft_c = ft_v.size();
            // for (size_t i = 0; i < v.size(); ++i)
            //     str += v[i];
            // for (size_t i = 0; i < ft_v.size(); ++i)
            //     ft_str += ft_v[i];
            // cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
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
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " swap method "
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
        ft::vector<std::string>::iterator b1, b2;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*---------------------------------- test 1: equal size vectors ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(200, "string");
            ft::vector<std::string> ft_v(200, "hello");
            ft::vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs > rhs ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(50, "string");
            ft::vector<std::string> ft_v(200, "hello");
            ft::vector<std::string> ft_v1(50, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs < rhs ----------------------*/
        {
            std::vector<std::string> v(50, "hello");
            std::vector<std::string> v1(200, "string");
            ft::vector<std::string> ft_v(50, "hello");
            ft::vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            v.swap(v1);
            ft_v.swap(ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " clear method "
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
        /*
         * bool to store the comparison
         */
        bool cond;

        /*---------------------------------- test 1: equal size vectors ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            ft::vector<std::string> ft_v(200, "hello");

            v.clear();
            ft_v.clear();

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
        }
        /*--------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " get_allocator method "
              << "] --------------------]\t\t\033[0m";
    {
        std::vector<std::string> v(200, "hello");
        ft::vector<std::string> ft_v(200, "hello");

        EQUAL(v.get_allocator().max_size() == ft_v.get_allocator().max_size());
    }

    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator== "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v == v1) == (ft_v == ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v == v1) == (ft_v == ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v == v1) == (ft_v == ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v == v1) == (ft_v == ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator!= "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v != v1) == (ft_v != ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v != v1) == (ft_v != ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v != v1) == (ft_v != ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v != v1) == (ft_v != ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator< "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v < v1) == (ft_v < ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v < v1) == (ft_v < ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v < v1) == (ft_v < ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v < v1) == (ft_v < ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator<= "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v <= v1) == (ft_v <= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v <= v1) == (ft_v <= ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v <= v1) == (ft_v <= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v <= v1) == (ft_v <= ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator> "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v > v1) == (ft_v > ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v > v1) == (ft_v > ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v > v1) == (ft_v > ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v > v1) == (ft_v > ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " operator>= "
              << "] --------------------]\t\t\033[0m";
    {
        bool cond;
        /*------------------------------------------ test 1: lhs.size == rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = ((v >= v1) == (ft_v >= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 2: lhs.size < rhs.size ------------------*/
        {
            std::vector<int> v(50, 5);
            std::vector<int> v1(100, 5);
            ft::vector<int> ft_v(50, 5);
            ft::vector<int> ft_v1(100, 5);

            cond = (cond && (v >= v1) == (ft_v >= ft_v1));
            v[40] = 4;
            ft_v[40] = 4;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
            v1[80] = 3;
            ft_v1[80] = 3;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
        }
        /*------------------------------------------------------------------------------------------*/
        /*------------------------------------------ test 3: lhs.size > rhs.size ------------------*/
        {
            std::vector<int> v(100, 5);
            std::vector<int> v1(50, 5);
            ft::vector<int> ft_v(100, 5);
            ft::vector<int> ft_v1(50, 5);

            cond = (cond && (v >= v1) == (ft_v >= ft_v1));
            v[80] = 4;
            ft_v[80] = 4;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
            v1[40] = 3;
            ft_v1[40] = 3;
            cond = (cond && ((v >= v1) == (ft_v >= ft_v1)));
        }
        EQUAL(cond);
    }
    std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " swap "
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
        ft::vector<std::string>::iterator b1, b2;
        /*
         * bool to store the comparison
         */
        bool cond;

        /*---------------------------------- test 1: equal size vectors ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(200, "string");
            ft::vector<std::string> ft_v(200, "hello");
            ft::vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            swap(v, v1);
            swap(ft_v, ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = ((str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs > rhs ----------------------*/
        {
            std::vector<std::string> v(200, "hello");
            std::vector<std::string> v1(50, "string");
            ft::vector<std::string> ft_v(200, "hello");
            ft::vector<std::string> ft_v1(50, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            swap(v, v1);
            swap(ft_v, ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        /*---------------------------------- test 2: lhs < rhs ----------------------*/
        {
            std::vector<std::string> v(50, "hello");
            std::vector<std::string> v1(200, "string");
            ft::vector<std::string> ft_v(50, "hello");
            ft::vector<std::string> ft_v1(200, "string");

            b1 = ft_v.begin();
            b2 = ft_v1.begin();

            swap(v, v1);
            swap(ft_v, ft_v1);

            s = v.size();
            ft_s = ft_v.size();
            c = v.capacity();
            ft_c = ft_v.capacity();
            for (size_t i = 0; i < v.size(); ++i)
                str += v[i];
            for (size_t i = 0; i < ft_v.size(); ++i)
                ft_str += ft_v[i];

            cond = (cond && (str == ft_str) && (s == ft_s) && (c == ft_c));
            cond = (cond && ((&*b2) == (&(*ft_v.begin()))));
            cond = (cond && ((&*b1) == (&(*ft_v1.begin()))));
        }
        /*--------------------------------------------------------------------------------------------*/
        EQUAL(cond);
    }
    std::cout << "\033[1;36m\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\033[0m\n\n";
}

int main()
{
    iterator_tests();
    const_iterator_tests();
    reverse_iterator_tests();
    reverse_iterator_vector_tests();
    ft_vector_tests();
}

// int main ()
// {
	// constructors used in the same order as described above:
	// ft::vector<int> first;                                // empty vector of ints
	// ft::vector<int> second (4,100);                       // four ints with value 100
	// ft::vector<int> third (second.begin(),second.end());  // iterating through second
	// ft::vector<int> fourth (third);                       // a copy of third

	// std::cout << *(second.begin())+1 << std::endl;
	// std::cout << "size before " << first.size() << std::endl;
	// first.assign(4, 7);
	// typedef ft::vector<int>::const_iterator ci;
	// ci gg (first.end());
	// ft::vector<int> first;
	// ft::vector<int>::iterator t = first.begin();
	// // std::cout << "holla\n";
	// first.insert(t, 2);
	// const std::string extra(4, 7);
	// first.assign(extra.begin(), extra.end());
	// std::cout << "size after " << first.size() << std::endl;
	// for (ft::vector<int>::iterator it = first.begin() ; it != first.end(); ++it)
    // 	std::cout << *it << std::endl;
	// ft::vector<double> vec;
	// vec.assign(5, 8.8);
	// vec.push_back(7.3);
	// vec.push_back(7.4);
	// vec.push_back(7.7);

	// std::cout << "vec: \n";
	// for(unsigned int i = 0; i < vec.size(); i++)
	// 	std::cout << vec.at(i) << "\n";
	// ft::vector<std::string> letters;
 
    // letters.push_back("abc");
    // std::string s("def");
    // letters.push_back(std::move(s));
 
    // std::cout << "std::vector `letters` holds: \n";
    // for(unsigned int i = 0; i < letters.size(); i++)
	// 	std::cout << letters[i] << "\n";
// 	ft::vector<int> numbers;
 
//     std::cout<<"[";
// 	for(unsigned int i = 0; i < numbers.size(); i++)
// 		std::cout << numbers[i] << " ";
// 	 std::cout<<"]\n";
 
//     numbers.push_back(5);
//     numbers.push_back(3);
//     numbers.push_back(4);
 
//     std::cout<<"[";
// 	for(unsigned int i = 0; i < numbers.size(); i++)
// 		std::cout << numbers[i] << " ";
// 	 std::cout<<"]\n";
 
//     numbers.pop_back();
 
//    std::cout<<"[";
// 	for(unsigned int i = 0; i < numbers.size(); i++)
// 		std::cout << numbers[i] << " ";
// 	 std::cout<<"]\n";
 
    // std::cout << "\nMoved-from string `s` holds: " << std::quoted(s) << '\n';
	// ft::vector<int> c1(3, 100);
	// std::cout<<"[";
	// for(unsigned int i = 0; i < c1.size(); i++)
	// 	std::cout << c1[i] << " ";
	// std::cout<<"]\n";

	// ft::vector<int>::iterator it = c1.begin();

    // c1.insert(it, 200);
	// // c1.erase(ie);
	// ft::vector<int>::iterator ie = c1.begin();
	// ft::vector<int>::iterator ei = c1.end();
	// // ei--;
	// // ei--;
	// c1.erase(ie, ei);
    // std::cout<<"[";
	// for(unsigned int i = 0; i < c1.size(); i++)
	// 	std::cout << c1[i] << " ";
	// std::cout<<"]\n";
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;

	// ft::vector<int> ce1(3, 100);
	// std::cout<<"[";
	// for(unsigned int i = 0; i < ce1.size(); i++)
	// 	std::cout << ce1[i] << " ";
	// std::cout<<"]\n";

	// ft::vector<int>::iterator ite = ce1.end();

    // ce1.insert(ite, 200);
    // std::cout<<"[";
	// for(unsigned int i = 0; i < ce1.size(); i++)
	// 	std::cout << ce1[i] << " ";
	// std::cout<<"]\n";
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::vector<int> c2(3, 100);
	// std::cout<<"[";
	// for(unsigned int i = 0; i < c2.size(); i++)
	// 	std::cout << c2[i] << " ";
	// std::cout<<"]\n";

	// ft::vector<int>::iterator it2 = c2.begin();

    // c2.insert(it2, 2, 700);
    // std::cout<<"[";
	// for(unsigned int i = 0; i < c2.size(); i++)
	// 	std::cout << c2[i] << " ";
	// std::cout<<"]\n";
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::vector<int> ce2(3, 100);
	// std::cout<<"[";
	// for(unsigned int i = 0; i < ce2.size(); i++)
	// 	std::cout << ce2[i] << " ";
	// std::cout<<"]\n";

	// ft::vector<int>::iterator ite2 = ce2.end();

    // ce2.insert(ite2, 2, 300);
    // std::cout<<"[";
	// for(unsigned int i = 0; i < ce2.size(); i++)
	// 	std::cout << ce2[i] << " ";
	// std::cout<<"]\n";
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// the iterator constructor can also be used to construct from arrays:
	// int myints[] = {16,2,77,29};
	// ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	// std::cout << "The contents of fifth are:";
	// for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	// 	std::cout << ' ' << *it;
	// std::cout << '\n';
	
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// constructors used in the same order as described above:
	// ft::vector<int> first;                                // empty vector of ints
	// ft::vector<int> second (4,100);                       // four ints with value 100
	// // ft::ft_vector<int> third (second.begin(),second.end());  // iterating through second
	// // ft::ft_vector<int> fourth (third);                       // a copy of third
	// ft::vector<int> fourth (second); 
	
	// // ft::vector<int> hlwa1(3,13);
	// // ft::vector<int> hlwa2(3,37);
	// // hlwa1 = hlwa2;
	// ////
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::vector<int> hlwa1 (100,0);
	// ft::vector<int> hlwa2 (8,0);
	// // std::cout << "hlwa's allocator " << hlwa1.get_allocator() << std::endl;

	// hlwa2 = hlwa1;
	// // hlwa1 = ft::vector<int>();

	// std::cout << "Size of hlwa1: " << hlwa1.size() << " Capacity of hlwa1: " << hlwa1.capacity() << '\n';
	// std::cout << "Size of hlwa2: " << hlwa2.size() << " Capacity of hlwa2: " << hlwa2.capacity() << '\n';
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	
	
	
	
	
	
	// //////
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::vector<int> foo (3,100);   // three ints with a value of 100
	// ft::vector<int> bar (5,200);   // five ints with a value of 200

	// foo.swap(bar);

	// std::cout << "foo contains:";
	// for (unsigned i=0; i<foo.size(); i++)
	// 	std::cout << ' ' << foo[i];
	// std::cout << '\n';

	// std::cout << "bar contains:";
	// for (unsigned i=0; i<bar.size(); i++)
	// 	std::cout << ' ' << bar[i];
	// std::cout << '\n';
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// //////






	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::vector<int> empty_hlwa;
	
	// hlwa1.clear();
	// std::cout << "hlwa is empty " << hlwa1.empty() << std::endl;
	// std::cout << "empty_hlwa is empty " << empty_hlwa.empty() << std::endl;
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// //////

	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::vector<int> hlwa;
	// std::cout << "hlwas size before " << hlwa.size() << std::endl;
	// hlwa.push_back(1);
	// hlwa.push_back(3);
	// hlwa.push_back(3);
	// hlwa.push_back(7);
	// hlwa.pop_back();
	// hlwa.pop_back();
	// std::cout << "hlwas size after " << hlwa.size() << std::endl;
	// hlwa.shrink_to_fit();
	// std::cout << "hlwas capacity after " << hlwa.capacity() << std::endl;
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// std::cout << "resizing some" << std::endl;
	// ft::vector<int> myvector;
	// for (int i=1;i<10;i++) myvector.push_back(i);
	// myvector.resize(5);
	// myvector.resize(8,100);
	// myvector.resize(12);
	// std::cout << "myvector contains:";
	// for (size_t i=0;i<myvector.size();i++)
	// 	std::cout << ' ' << myvector[i];
	// std::cout << '\n';
	// ft::vector<int> c;
	// c.push_back(1);
	// c.push_back(2);
	// c.push_back(3);
    // std::cout << "The vector holds: ";
    // for (size_t i=0;i<c.size();i++)
	// 	std::cout << ' ' << c[i];
    // std::cout << '\n';
 
    // c.resize(5);
    // std::cout << "After resize up to 5: ";
    // for (size_t i=0;i<c.size();i++)
	// 	std::cout << ' ' << c[i];
    // std::cout << '\n';
 
    // c.resize(2);
    // std::cout << "After resize down to 2: ";
    // for (size_t i=0;i<c.size();i++)
	// 	std::cout << ' ' << c[i];
    // std::cout << '\n';
 
    // c.resize(6, 4);
    // std::cout << "After resize up to 6 (initializer = 4): ";
    // for (size_t i=0;i<c.size();i++)
	// 	std::cout << ' ' << c[i];
    // std::cout << '\n';
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// std::cout << "^^^ at ^^^" << std::endl;
	// ft::vector<int> myvector2 (10);
	// for (unsigned i=0; i<myvector2.size(); i++)
	// 	myvector2.at(i)=i;
	// for (unsigned i=0; i<myvector2.size(); i++)
	// 	std::cout << ' ' << myvector2.at(i);
	// std::cout << '\n';
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// std::cout << "^^^ front & back ^^^" << std::endl;
	// ft::vector<int> myvector3;
	// myvector3.push_back(78);
	// myvector3.push_back(16);
	// myvector3.front() -= myvector3.back();
	// std::cout << "myvector.front() is now " << myvector3.front() << '\n';
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// std::cout << "^^^ data ^^^" << std::endl;
	// ft::vector<int> myvector4 (5);
	// int* p = myvector4.data();
	// *p = 10;
	// ++p;
	// *p = 20;
	// p[2] = 100;
	// std::cout << "myvector contains:";
	// for (unsigned i=0; i<myvector4.size(); ++i)
	// 	std::cout << ' ' << myvector4[i];
	// std::cout << '\n';
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// std::cout << "^^^ get_allocator ^^^" << std::endl;
	// ft::vector<int> myvector5;
	// int * p2;
	// unsigned int i;
	// p2 = myvector5.get_allocator().allocate(5);
	// for (i=0; i<5; i++) myvector5.get_allocator().construct(&p2[i],i);
	// std::cout << "The allocated array contains:";
	// for (i=0; i<5; i++) std::cout << ' ' << p2[i];
	// std::cout << '\n';
	// for (i=0; i<5; i++) myvector4.get_allocator().destroy(&p2[i]);
	// myvector4.get_allocator().deallocate(p2,5);
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// std::cout << "^^^ iterators ^^^" << std::endl;
	// typedef std::iterator_traits<int*> traits;
	// if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
	// 	std::cout << "int* is a random-access iterator\n";
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::vector<int> values;
	// values.push_back(1);
	// values.push_back(2);
	// values.push_back(3);
	// values.push_back(4);
	// std::cout <<"size-- "<<values.size()<<"--\n";
	// values.push_back(5);
	// std::cout << "not using iterators" << std::endl;
	// for (unsigned int i=0; i<values.size(); i++)
	// 	std::cout << values[i] << std::endl;
	// // std::cout << "Range-based for loop" << std::endl;
	// // for (unsigned int value : values)
	// // 	std::cout << value << std::endl;
	// std::cout << "using iterators" << std::endl;
	// for (ft::vector<int>::iterator it = values.begin(); it != values.end(); it++)
	// 	std::cout << *it << std::endl;
	// // std::cout << '\n';
	// // the iterator constructor can also be used to construct from arrays:
	// // int myv[] = {16,2,77,29};
	// // ft::vector<int> fifth (myv, myv + sizeof(myv) / sizeof(int) );
	// // std::cout << "The contents of fifth are:";
	// // for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	// //   std::cout << ' ' << *it;
	// // std::cout << '\n';
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::vector<int> myg;
	// for (int i=0; i<10; i++) myg.push_back(i);

	// typedef ft::vector<int>::iterator iter_type;
	// iter_type from (myg.begin());
	// iter_type until (myg.end());
	// ft::reverse_iterator<iter_type> rev_until (from);
	// ft::reverse_iterator<iter_type> rev_from (until);
	// std::cout << "myg:";
	// while (rev_from != rev_until)
	// 	std::cout << ' ' << *rev_from++;
	// std::cout << '\n';
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::vector<int> alice(1, 2);
    // ft::vector<int> bob(7, 10);
    // ft::vector<int> eve(1, 3);

    // // std::cout << std::boolalpha;

    // // Compare non equal containers
    // std::cout << "alice == bob returns " << (alice == bob) << '\n';
    // std::cout << "alice != bob returns " << (alice != bob) << '\n';
    // std::cout << "alice <  bob returns " << (alice < bob) << '\n';
    // std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
    // std::cout << "alice >  bob returns " << (alice > bob) << '\n';
    // std::cout << "alice >= bob returns " << (alice >= bob) << '\n';

    // std::cout << '\n';

    // // Compare equal containers
    // std::cout << "alice == eve returns " << (alice == eve) << '\n';
    // std::cout << "alice != eve returns " << (alice != eve) << '\n';
    // std::cout << "alice <  eve returns " << (alice < eve) << '\n';
    // std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
    // std::cout << "alice >  eve returns " << (alice > eve) << '\n';
    // std::cout << "alice >= eve returns " << (alice >= eve) << '\n';



	// ft::vector<int> characters;
	// characters.push_back("stronk");
	// characters.push_back('s');
	// characters.push_back('s');
 
    

    // characters.assign(2, "stronkest");
	// std::string gg(2, 7);
	// characters.assign(gg.begin(), gg.end());
    // for (ft::vector<int>::iterator it = characters.begin() ; it != characters.end(); ++it)
    // 	std::cout << *it << std::endl;

    // const std::string extra(6, 'b');
    // characters.assign(extra.begin(), extra.end());
    // print_vector();
 
    // characters.assign({'C', '+', '+', '1', '1'});
    // print_vector();
// 	return 0;
// }