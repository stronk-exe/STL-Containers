/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:00:55 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/09 19:38:43 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "set.hpp"
#include "../utils/pair.hpp"

#include <set>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <random>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mOK\033[0m\n") : (std::cout << "\033[1;31mKO\033[0m\n"))
#define TIME_FAC 4

typedef std::pair<std::set<int>::iterator, std::set<int>::iterator> iter_def;
typedef ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> ft_iter_def;

time_t get_time(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    time_t msecs_time = (time_now.tv_sec * 1e3) + (time_now.tv_usec / 1e3);
    return (msecs_time);
}

template <typename Iter1, typename Iter2>
bool compareMaps(Iter1 first1, Iter1 last1, Iter2 first2, Iter2 last2)
{
    for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
        if (*first1 != *first2)
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

bool testMapConstructors()
{
    bool cond;
    std::set<int> first;
    ft::set<int> m_first;

    for (size_t i = 97; i < 110; i++)
	{
		first.insert(i);
		m_first.insert(i);
	}

    std::set<int> copy(first);
    ft::set<int> m_copy(m_first);

    cond = first.size() == m_first.size() && compareMaps(first.begin(), first.end(), m_first.begin(), m_first.end());

    std::set<int> second(first.begin(), first.end());
    ft::set<int> m_second(m_first.begin(), m_first.end());

    cond = cond && second.size() == m_second.size() && compareMaps(second.begin(), second.end(), m_second.begin(), m_second.end());

    std::set<int> third(second);
    ft::set<int> m_third(m_second);

    cond = cond && third.size() == m_third.size() && compareMaps(third.begin(), third.end(), m_third.begin(), m_third.end());

    std::set<int, classcomp> fourth;  // class as Compare
    ft::set<int, classcomp> m_fourth; // class as Compare

    cond = fourth.size() == m_fourth.size() && cond && compareMaps(fourth.begin(), fourth.end(), m_fourth.begin(), m_fourth.end());

    bool (*fn_pt)(char, char) = fncomp;
    std::set<int, bool (*)(char, char)> fifth(fn_pt);  // function pointer as Compare
    ft::set<int, bool (*)(char, char)> m_fifth(fn_pt); // function pointer as Compare

    cond = fifth.size() == m_fifth.size() && cond && compareMaps(fifth.begin(), fifth.end(), m_fifth.begin(), m_fifth.end());

    first = std::set<int>();
    m_first = ft::set<int>();

    cond = copy.size() == m_copy.size() && cond && compareMaps(copy.begin(), copy.end(), m_copy.begin(), m_copy.end());

    return cond;
}

void iterator_tests(void)
{
    std::set<char> m;
    std::set<char>::iterator it, it1;

    ft::set<char> my_m;
    ft::set<char>::iterator my_it, my_it1, tmp;

    for (int i = 0; i < 10; ++i)
    {
        my_m.insert(static_cast<char>(i + 97));
        m.insert(static_cast<char>(i + 97));
    }

    it = m.begin();
    it1 = ++(m.begin());
    my_it = my_m.begin();
    my_it1 = ++(my_m.begin());
    std::cout <<"	copy constructor ---	                ";
    {
        ft::set<char>::iterator ob(my_it);
        EQUAL(&(*my_it) == &(*ob));
    }
    std::cout <<"	iterator to const_iterator ---		";
    {
        ft::set<char>::const_iterator c_it, c_ob(my_it);
        c_it = my_it;
        EQUAL(&(*my_it) == &(*c_it) && (&(*my_it) == &(*c_ob)));
    }
    std::cout <<"	== operator ---	                	";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout <<"	!= operator ---	                	";
    EQUAL((it != it1) == (my_it != my_it1));
    std::cout <<"	* operator ---	                	";
    EQUAL((*my_it == *(my_m.begin())));
    std::cout <<"	-> operator ---	                	";
    {
        std::set<std::string> m;
        ft::set<std::string> my_m;
        m.insert("HELLO");
        my_m.insert("HELLO");


        ft::set<std::string>::iterator my_it = my_m.begin();
        std::set<std::string>::iterator it = m.begin();
        EQUAL(it->length() == my_it->length());
    }
    std::cout <<"	++it operator ---	                ";
    {
        bool cond(false);
        {
            int res(0);
            int myints[] = {12, 82, 37, 64, 15};
            ft::set<int32_t> m;
            for (size_t i = 0; i < 5; ++i)
                m.insert(myints[i]);
            for (ft::set<int>::iterator it = m.begin(); it != m.end(); ++it)
                res += *(it);
            cond = res == 210;
        }
        {
            int res(0), tmp;
            int myints[] = {12, 82, 37, 64, 15};
            ft::set<int> m;
            for (size_t i = 0; i < 5; ++i)
                m.insert(myints[i]);
            ft::set<int>::iterator it = m.begin(), eit = --m.end();
            tmp = *(eit);
            m.erase(eit);
            for (; it != m.end(); ++it)
                res += *(it);
            cond = cond && (res == (210 - tmp));
        }
        ++my_it; // I incremented here to make sure that the object changes
        EQUAL(*my_it == *my_it1);
    }
    std::cout <<"	--it operator ---	                ";
    {
        int res(0);
        {
            int myints[] = {12, 82, 37, 64, 15};
            ft::set<int> m;
            for (size_t i = 0; i < 5; ++i)
                m.insert(myints[i]);
            ft::set<int>::iterator it = --m.end();
            for (;; --it)
            {
                if (it == m.begin())
                {
                    res += *(it);
                    break;
                }
                res += *(it);
            }
        }
        --my_it; // I decremented here to make sure that the object changes
        EQUAL(*my_it != *my_it1);
    }
    std::cout <<"	it++ operator ---	                ";
    tmp = my_it++;
    EQUAL(*my_it != *tmp && *my_it == *my_it1);
    std::cout <<"	it-- operator ---	                ";
    tmp = my_it--;
    EQUAL(*my_it != *tmp && *my_it == *(my_m.begin()));
}

void const_iterator_tests(void)
{
    std::set<char> m;
    std::set<char>::const_iterator it, it1;

    ft::set<char> my_m;
    ft::set<char>::const_iterator my_it, my_it1, tmp;

    for (int i = 0; i < 10; ++i)
    {
        my_m.insert(static_cast<char>(i + 97));
        m.insert(static_cast<char>(i + 97));
    }

    it = m.begin();
    it1 = ++(m.begin());
    my_it = my_m.begin();
    my_it1 = ++(my_m.begin());

    std::cout <<"	copy constructor ---			";
    {
        ft::set<char>::const_iterator ob(my_it);
        EQUAL(*my_it == *ob);
    }
    std::cout <<"	== operator ---	                	";
    EQUAL((it == it1) == (my_it == my_it1));
    std::cout <<"	!= operator ---	                	";
    EQUAL((it != it1) == (my_it != my_it1));
	std::cout <<"	* operator ---	                	";
    EQUAL(*(my_it) == (*(my_m.begin())));
    std::cout <<"	-> operator ---	                	";
    {
        std::set<std::string> m;
        ft::set<std::string> my_m;

        m.insert("HELLO");
        my_m.insert("HELLO");

        ft::set<std::string>::iterator my_it = my_m.begin();
        std::set<std::string>::iterator it = m.begin();
        EQUAL(it->length() == my_it->length());
    }
    std::cout <<"	++it operator ---	                ";
    ++my_it; // I incremented here to make sure that the object changes
    EQUAL(*my_it == *my_it1);
    std::cout <<"	--it operator ---	                ";
    --my_it; // I decremented here to make sure that the object changes
    EQUAL(*my_it != *my_it1);
    std::cout <<"	it++ operator ---	                ";
    tmp = my_it++;
    EQUAL(*my_it != *tmp && *my_it == *my_it1);
    std::cout <<"	it-- operator ---	                ";
    tmp = my_it--;
    EQUAL(*my_it != *tmp && *my_it == *(my_m.begin()));
}

void reverse_iterator_tests(void)
{
    std::set<int> m;
    for (int i = 0; i < 1e2; i++)
        m.insert(i);

    std::reverse_iterator<std::set<int>::iterator> rit(m.end()), rit_1(--m.end());

    ft::reverse_iterator<std::set<int>::iterator> my_rit(m.end()), my_rit1(--m.end());
    std::cout <<"	copy constructor ---	                ";
    {
        ft::reverse_iterator<std::set<int>::iterator> ob(my_rit);
        EQUAL(*my_rit == *ob);
    }
    std::cout <<"	riterator to const_riterator ---	";
    {
        ft::set<int> my_m;
        for (int i = 0; i < 1e2; i++)
            my_m.insert(i);

        ft::set<int>::reverse_iterator my_rit2(my_m.end());
        ft::set<int>::const_reverse_iterator c_it, c_ob(my_m.end());
        c_it = my_rit2;
        EQUAL(*my_rit == *c_it && *my_rit2 == *c_ob);
    }
    std::cout <<"	base function ---	                ";
    EQUAL((*rit == (*rit_1.base())) && (*my_rit == *my_rit1.base()));
    std::cout <<"	== operator ---	                	";
    EQUAL((rit == rit_1) == (my_rit == my_rit1));
    std::cout <<"	!= operator ---	                	";
    EQUAL((rit != rit_1) == (my_rit != my_rit1));
    std::cout <<"	-> operator ---	                	";
    {
        std::set<std::string> s;
        ft::set<std::string> mys;
        s.insert("hello");
        mys.insert("hello");
        EQUAL(s.rbegin()->length() == mys.rbegin()->length());
    }
    std::cout <<"	* operator ---	                	";
    EQUAL((((*my_rit) == (*(--m.end()))) && (((*my_rit)) == ((*(--m.end()))))) && (((*rit) == (*(--m.end()))) && ((*(rit))) == ((*(--m.end())))));

    std::cout <<"	++rit operator ---	                ";
    ++my_rit; // I incremented here to make sure that the object changes
    ++rit;
    EQUAL(&(*my_rit) == &(*my_rit1)) && (&(*rit) == &(*rit_1));
    std::cout <<"	--rit operator ---	                ";
    --my_rit; // I incremented here to make sure that the object changes
    --rit;
    EQUAL((*my_rit == *(--my_rit1)) && (*rit == *(--rit_1)));
    std::cout <<"	rit++ operator ---	                ";
    {
        std::reverse_iterator<std::set<int>::iterator> tmp(rit++);
        ft::reverse_iterator<std::set<int>::iterator> my_tmp(my_rit++);
        EQUAL(*tmp == *(--rit) && *my_tmp == *(--my_rit));
    }
    std::cout <<"	rit-- operator ---	                ";
    {
        rit++;
        my_rit++;
        std::reverse_iterator<std::set<int>::iterator> tmp(rit--);
        ft::reverse_iterator<std::set<int>::iterator> my_tmp(my_rit--);
        EQUAL(*tmp == *(++rit) && *my_tmp == *(++my_rit));
    }
}

void testConstructors()
{
    std::cout <<"	empty constructor ---	                ";
    {
        ft::set<int> my_m;
        std::set<int> m;
        for (int i = 0; i < 10; i++)
        {
            m.insert(i);
            my_m.insert(i);
        }

        std::string res, my_res;
        for (std::set<int>::iterator it = m.begin(); it != m.end(); ++it) // fill res from std::set
            res += *it;
        for (ft::set<int>::iterator it = my_m.begin(); it != my_m.end(); ++it) // fill res from std::set
            my_res += *it;
        EQUAL(res == my_res);
    }
    std::cout <<"	range constructor ---	                ";
    {
        std::set<int> m;
        ft::set<int> my_m;
        for (size_t i = 0; i < 10; i++)
        {
            m.insert(i);
            my_m.insert(i);
        }

        ft::set<int> my_m1(my_m.begin(), my_m.end()); // this one is to check if the range works with ft::set
        int sum(0), my_sum(0), my_sum1(0);
        for (std::set<int>::iterator it = m.begin(); it != m.end(); ++it)
            sum += *it;

        for (ft::set<int>::iterator it = my_m.begin(); it != my_m.end(); ++it)
            my_sum += *it;

        for (ft::set<int>::iterator it = my_m1.begin(); it != my_m1.end(); ++it)
            my_sum1 += *it;
        EQUAL(my_sum == sum && my_sum == my_sum1);
    }
    std::cout <<"	copy constructor ---	                ";
    {
        ft::set<int> m1;
        for (int i = 0; i < 10; i++)
            m1.insert(i);
        ft::set<int> copy_m(m1);
        int res(0), res1(0);
        for (ft::set<int>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += *it;

        for (ft::set<int>::iterator it = copy_m.begin(); it != copy_m.end(); ++it) // fill res from copy_m
            res1 += *it;
        EQUAL(res == res1);
    }
    std::cout <<"	Constructors with costum compare ---	";
    EQUAL(testMapConstructors());
    std::cout <<"	operator= (lhs.size = rhs.size) ---	";
    {
        std::set<int> m1;
        std::set<int> m2;
        ft::set<int> ft_m1;
        ft::set<int> ft_m2;
        for (int i = 0; i < 10; ++i)
        {
            m1.insert(i);
            m2.insert(i);
            ft_m1.insert(i);
            ft_m2.insert(i);
        }

        m1 = m2;
        ft_m1 = ft_m2;
        int res(0), ft_res(0);
        for (std::set<int>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += *it;

        for (ft::set<int>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += *it;

        EQUAL(res == ft_res);
    }

    std::cout <<"	= operator (lhs.size < rhs.size) ---	";
    {
        std::set<int> m1;
        std::set<int> m2;
        ft::set<int> ft_m1;
        ft::set<int> ft_m2;
		for(size_t i = 0; i < 1000; ++i)
		{
			m2.insert(i);
			ft_m2.insert(i);
		}
        for(size_t i = 0; i < 100; ++i)
		{
			m1.insert(i);
			ft_m1.insert(i);
		}
        m1 = m2;
        ft_m1 = ft_m2;
        int res(0), ft_res(0);
        for (std::set<int>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += *it;

        for (ft::set<int>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    std::cout <<"	= operator (lhs.size > rhs.size) ---	";
    {
        std::set<int> m1;
        std::set<int> m2;
        ft::set<int> ft_m1;
        ft::set<int> ft_m2;

        for (int i = 0; i < 20; ++i)
        {
            m1.insert(i);
            ft_m1.insert(i);
        }

        for (int i = 0; i < 10; ++i)
        {
            m2.insert(i);
            ft_m2.insert(i);
        }
        m1 = m2;
        ft_m1 = ft_m2;
        int res(0), ft_res(0);
        for (std::set<int>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += *it;

        for (ft::set<int>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    std::cout <<"	= operator (lhs.size = 0) ---		";
    {
        std::set<int> m1;
        std::set<int> m2;
        ft::set<int> ft_m1;
        ft::set<int> ft_m2;

        for (int i = 0; i < 10; ++i)
        {
            m2.insert(i);
            ft_m2.insert(i);
        }
        m1 = m2;

        ft_m1 = ft_m2;
        int res(0), ft_res(0);
        for (std::set<int>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += *it;

        for (ft::set<int>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
    std::cout <<"	= operator (rhs.size = 0) ---		";
    {
        std::set<int> m1;
        std::set<int> m2;
        ft::set<int> ft_m1;
        ft::set<int> ft_m2;

        for (int i = 0; i < 10; ++i)
        {
            m1.insert(i);
            ft_m1.insert(i);
        }
        m1 = m2;
        ft_m1 = ft_m2;
        int res(0), ft_res(0);
        for (std::set<int>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += *it;

        for (ft::set<int>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += *it;

        EQUAL(res == ft_res);
    }
}

void testIterators()
{
    std::cout <<"	begin and end methods ---		";
    {
        std::set<int> m1;
        ft::set<int> ft_m1;

        for (size_t i = 0; i < 10; i++)
        {
            m1.insert(i);
            ft_m1.insert(i);
        }

        std::set<int> const m2(m1.begin(), m1.end());
        ft::set<int> const ft_m2(ft_m1.begin(), ft_m1.end());

        int res(0), ft_res(0), c_res(0), c_ft_res(0);
        for (std::set<int>::iterator it = m1.begin(); it != m1.end(); ++it) // fill res from m1
            res += *it;
        for (std::set<int>::const_iterator rit = m2.begin(); rit != m2.end(); ++rit) // fill c_res from const m1
            c_res += *rit;

        for (ft::set<int>::iterator it = ft_m1.begin(); it != ft_m1.end(); ++it) // fill ft_res from ft_m1
            ft_res += *it;
        for (ft::set<int>::const_iterator rit = ft_m2.begin(); rit != ft_m2.end(); ++rit) // fill c_ft_res from const ft_m1
            c_ft_res += *rit;
        int arr[] = {12, 82, 37, 64, 15};
        ft::set<int> end_test;
        for(size_t i = 0; i < 5; ++i)
            end_test.insert(arr[i]);
        ft::set<int>::iterator eit = end_test.end();
        eit--;
        EQUAL(res == ft_res && c_res == c_ft_res && *eit == 82);
    }
    std::cout <<"	rbegin and rend methods ---		";
    {
        std::set<int> m1;
        ft::set<int> ft_m1;

        for (size_t i = 0; i < 10; i++)
        {
            m1.insert(i);
            ft_m1.insert(i);
        }

        std::set<int> const m2(m1.rbegin(), m1.rend());
        ft::set<int> const ft_m2(ft_m1.rbegin(), ft_m1.rend());

        int res(0), ft_res(0), c_res(0), c_ft_res(0);
        for (std::set<int>::reverse_iterator it = m1.rbegin(); it != m1.rend(); ++it) // fill res from m1
            res += *it;
        for (std::set<int>::const_reverse_iterator rit = m2.rbegin(); rit != m2.rend(); ++rit) // fill c_res from const m1
            c_res += *rit;

        for (ft::set<int>::reverse_iterator it = ft_m1.rbegin(); it != ft_m1.rend(); ++it) // fill ft_res from ft_m1
            ft_res += *it;
        for (ft::set<int>::const_reverse_iterator rit = ft_m2.rbegin(); rit != ft_m2.rend(); ++rit) // fill c_ft_res from const ft_m1
            c_ft_res += *rit;
        int arr[] = {12, 82, 37, 64, 15};
        ft::set<int> end_test;
        for(size_t i = 0; i < 5; ++i)
            end_test.insert(arr[i]);
        ft::set<int>::reverse_iterator rit = end_test.rend();
        rit--;
        EQUAL(res == ft_res && c_res == c_ft_res && *rit == 12);
    }
}

void testCapacityMethods()
{
    std::cout <<"	size method ---	                	";
    {
        std::set<std::string> m1; // fill constructor
        ft::set<std::string> ft_m1;
        std::string s[5] = {"hello", "string", "value", "size", "test"};
        for (size_t i = 0; i < 5; i++)
        {
            m1.insert(s[i]);
            ft_m1.insert(s[i]);
        }

        std::set<std::string> m2;                         // empty constructor
        std::set<std::string> m3(m1.begin(), m1.end());   // range constructor with normal iterators
        std::set<std::string> m4(m3);                     // copy constructor
        std::set<std::string> m5(m1.rbegin(), m1.rend()); // range constructor with reverse iterators
        ft::set<std::string> ft_m2;
        ft::set<std::string> ft_m3(ft_m1.begin(), ft_m1.end());
        ft::set<std::string> ft_m4(ft_m3);
        ft::set<std::string> ft_m5(ft_m1.rbegin(), ft_m1.rend());
        /*----------------------------------------------------*/
        bool cond = (m1.begin()->size() == ft_m1.begin()->size()) && (m3.begin()->size() == ft_m3.begin()->size())
        && (m4.begin()->size() == ft_m4.begin()->size()) && (m5.begin()->size() == ft_m5.begin()->size());
        EQUAL(cond && (m1.size() == ft_m1.size() && m2.size() == ft_m2.size() && m3.size() == ft_m3.size() && m5.size() == ft_m5.size() && m4.size() == ft_m4.size()));
    }

    std::cout <<"	empty method ---	                ";
    {
        std::set<int> m1;
        std::set<int> m2;
        ft::set<int> ft_m1;
        ft::set<int> ft_m2;
        m1.insert(145);
        ft_m1.insert(145);
        EQUAL(m1.empty() == ft_m1.empty() && m2.empty() == ft_m2.empty());
    }
}

void testModifiers()
{
    std::cout <<"	insert method ---	                ";
    {
        bool cond(false);
        std::set<float> m;
        ft::set<float> ft_m;

        cond = m.size() == ft_m.size() && m.empty() == ft_m.empty();

        // first insert function version (single parameter):
        m.insert(100.5f);
        m.insert(200.5f);

        ft_m.insert(100.5f);
        ft_m.insert(200.5f);

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

        std::pair<std::set<float>::iterator, bool> ret;
        ft::pair<ft::set<float>::iterator, bool> ft_ret;

        ret = m.insert(500.6f);
        ft_ret = ft_m.insert(500.6f);

        cond = cond && ret.second == ft_ret.second;

        // second insert function version (with hint position):
        std::set<float>::iterator it = m.begin();
        ft::set<float>::iterator ft_it = ft_m.begin();
        m.insert(it, 300.8f);
        m.insert(it, 400.8f);

        ft_m.insert(ft_it, 300.8f);
        ft_m.insert(ft_it, 400.8f);

        cond = cond && (m.size() == ft_m.size() && m.empty() == ft_m.empty());

        // third insert function version (range insertion):
        std::set<float> anothermap;
        ft::set<float> ft_anothermap;
        anothermap.insert(m.begin(), m.find(300.8f));
        ft_anothermap.insert(ft_m.begin(), ft_m.find(300.8f));
        cond = cond && (anothermap.size() == ft_anothermap.size() && anothermap.empty() == ft_anothermap.empty());

        cond = cond && compareMaps(ft_m.begin(), ft_m.end(), m.begin(), m.end()) && compareMaps(ft_anothermap.begin(), ft_anothermap.end(), anothermap.begin(), anothermap.end());
        EQUAL(cond);
    }

    std::cout <<"	erase method ---	                ";
    {
        bool cond(false);
        std::set<char> m;
        ft::set<char> ft_m;
        std::set<char>::iterator it;
        ft::set<char>::iterator ft_it;

        // insert some values:
        ft_m.insert('a');
        ft_m.insert('b');
        ft_m.insert('c');
        ft_m.insert('d');
        ft_m.insert('e');
        ft_m.insert('f');

        m.insert('a');
        m.insert('b');
        m.insert('c');
        m.insert('d');
        m.insert('e');
        m.insert('f');

        cond = m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        it = m.find('b');
        ft_it = ft_m.find('b');

        cond = cond && (*it == *ft_it);
        m.erase(it);       // erasing by iterator
        ft_m.erase(ft_it); // erasing by iterator

        cond = cond && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        int ret = m.erase('c');       // erasing by key
        int ft_ret = ft_m.erase('c'); // erasing by key

        cond = cond && ret == ft_ret && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        it = m.find('e');
        ft_it = ft_m.find('e');

        cond = cond && (*it == *ft_it) && m.size() == ft_m.size();

        m.erase(it, m.end());          // erasing by range
        ft_m.erase(ft_it, ft_m.end()); // erasing by range

        cond = cond && m.empty() == ft_m.empty() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        /* ---------- Testing some edge cases ---------- */

        std::set<int> m2;
        ft::set<int> ft_m2;

        for (size_t i = 0; i < 1e5; i++)
        {
            m2.insert(i);
            ft_m2.insert(i);
        }

        std::set<int>::reverse_iterator it2 = m2.rbegin();
        ft::set<int>::reverse_iterator ft_it2 = ft_m2.rbegin();

        m2.erase(m2.begin());
        ft_m2.erase(ft_m2.begin());

        cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

        m2.erase(*it2);
        ft_m2.erase(*ft_it2);

        cond = cond && m2.size() == ft_m2.size() && compareMaps(m2.begin(), m2.end(), ft_m2.begin(), ft_m2.end());

        std::set<int> m3;
        ft::set<int> ft_m3;
        std::vector<int> vec;
        std::vector<int> ft_vec;
        std::random_device randDev;
        std::mt19937 generator(randDev());
        std::uniform_int_distribution<int> distr(0, 1e8);

        for (size_t i = 0; i < 1e6; i++)
        {
            m3.insert(i);
            ft_m3.insert(i);
        }

        for (size_t i = 0; i < 1e6; ++i)
        {
            int n = distr(generator);
            int ret1 = m3.erase(n);
            int ret2 = ft_m3.erase(n);

            if (ret1 != ret2)
            {
                cond = false;
                break;
            }
        }

        if (!m3.empty())
        {
            m3.erase(m3.begin(), m3.end());
            m3.erase(m3.begin(), m3.end());
        }
        if (!ft_m3.empty())
        {
            ft_m3.erase(ft_m3.begin(), ft_m3.end());
            ft_m3.erase(ft_m3.begin(), ft_m3.end());
        }

        cond = cond && (m3.size() == ft_m3.size() && compareMaps(m3.begin(), m3.end(), ft_m3.begin(), ft_m3.end()));

        EQUAL(cond);
    }

    std::cout <<"	swap method ---	                	";
    {
        bool cond = false;
        std::set<char> foo, bar;
        ft::set<char> ft_foo, ft_bar;

        foo.insert('x');
        foo.insert('y');

        ft_foo.insert('x');
        ft_foo.insert('y');

        cond = foo.size() == ft_foo.size() && bar.size() == ft_bar.size();

        bar.insert('a');
        bar.insert('b');
        bar.insert('c');

        ft_bar.insert('a');
        ft_bar.insert('b');
        ft_bar.insert('c');

        cond = cond && foo.size() == ft_foo.size() && bar.size() == ft_bar.size() && compareMaps(foo.begin(), foo.end(), ft_foo.begin(), ft_foo.end()) && compareMaps(bar.begin(), bar.end(), ft_bar.begin(), ft_bar.end());

        foo.swap(bar);
        ft_foo.swap(ft_bar);

        cond = cond && foo.size() == ft_foo.size() && bar.size() == ft_bar.size() && compareMaps(foo.begin(), foo.end(), ft_foo.begin(), ft_foo.end()) && compareMaps(bar.begin(), bar.end(), ft_bar.begin(), ft_bar.end());

        std::set<std::string, std::greater<std::string> > m1, m2;
        ft::set<std::string, std::greater<std::string> > ft_m1, ft_m2;

        m1.insert("γ");
        m1.insert("β");
        m1.insert("α");
        m1.insert("γ");

        m2.insert("ε");
        m2.insert("δ");
        m2.insert("ε");

        ft_m1.insert("γ");
        ft_m1.insert("β");
        ft_m1.insert("α");
        ft_m1.insert("γ");

        ft_m2.insert("ε");
        ft_m2.insert("δ");
        ft_m2.insert("ε");

        const std::string &ref = *(m1.begin());
        const std::set<std::string, std::greater<std::string> >::iterator iter = std::next(m1.begin());
        const std::string &ft_ref = *(ft_m1.begin());
        const ft::set<std::string, std::greater<std::string> >::iterator ft_iter = std::next(ft_m1.begin());

        // std::cout << "──────── before swap ────────\n"
        //           << "m1: " << m1 << "m2: " << m2 << "ref: " << ref
        //           << "\niter: " << *iter << '\n';

        cond = cond && ref == ft_ref && *iter == *ft_iter && m1.size() == ft_m1.size() && m2.size() && ft_m2.size();

        m1.swap(m2);
        ft_m1.swap(ft_m2);

        // _---------------_ << ──────── after swap ──────── >> _---------------_

        cond = cond && ref == ft_ref && *iter == *ft_iter && m1.size() == ft_m1.size() && m2.size() && ft_m2.size();

        EQUAL(cond);
    }
    std::cout <<"	clear method ---	                ";

    {
        bool cond(false);
        std::set<char> m;
        ft::set<char> ft_m;

        m.insert('x');
        m.insert('y');
        m.insert('z');

        ft_m.insert('x');
        ft_m.insert('y');
        ft_m.insert('z');

        cond = m.size() == ft_m.size();

        m.clear();
        ft_m.clear();

        cond = cond && m.empty() == ft_m.empty() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        m.insert('a');
        m.insert('b');
        ft_m.insert('a');
        ft_m.insert('b');

        cond = cond && m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        m = std::set<char>();
        ft_m = ft::set<char>();

        m.clear();
        ft_m.clear();

        cond = cond && m.size() == ft_m.size() && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        EQUAL(cond);
    }
}

struct ModCmp
{
    bool operator()(const int lhs, const int rhs) const
    {
        return (lhs % 97) < (rhs % 97);
    }
};

void testObservers()
{
    std::cout <<"	key_comp method ---	                ";
    {
        bool cond(true);
        std::set<int> m;
        ft::set<int> ft_m;
        std::set<int>::key_compare comp = m.key_comp();
        ft::set<int>::key_compare mycomp = ft_m.key_comp();

        for (size_t i = 0; i < 1e2; i++)
        {
            m.insert(i);
            ft_m.insert(i);
        }

        int highest = *m.rbegin();       // key value of last element
        int ft_highest = *ft_m.rbegin(); // key value of last element

        std::set<int>::iterator it = m.begin();
        ft::set<int>::iterator ft_it = ft_m.begin();
        do
        {
            if (!(*it == *ft_it && *it == *ft_it))
            {
                cond = false;
                break;
            }

        } while (comp((*it++), highest) && mycomp((*ft_it++), ft_highest));
        EQUAL(cond);
    }

    std::cout <<"	value_comp method ---	                ";
    {
        int sum(0);
        ft::set<int> mymap;

        mymap.insert(1001);
        mymap.insert(2002);
        mymap.insert(3003);

        int highest = *mymap.rbegin(); // last element

        ft::set<int>::iterator it = mymap.begin();
        do
        {
            sum += *it;
        } while (mymap.value_comp()(*it++, highest));

        EQUAL(sum == 6006);
    }
}
void testNonMemberSwap()
{
    std::cout <<"	non-member swap method ---		";
    {
        int res(0), ft_res(0);
        ft::set<char> foo, bar;

        foo.insert('x');
        foo.insert('y');

        bar.insert('a');
        bar.insert('b');
        bar.insert('c');

        swap(foo, bar);

        for (ft::set<char>::iterator it = foo.begin(); it != foo.end(); ++it)
            res += *it;

        for (ft::set<char>::iterator it = bar.begin(); it != bar.end(); ++it)
            ft_res += *it;
        EQUAL((res == ('a' + 'b' + 'c')) && (ft_res == ('x' + 'y')));
    }
}

void testOperations()
{
    std::cout <<"	find method ---	                	";
    {
        bool cond(true);
        std::vector<int> vec;
        std::vector<int> ft_vec;
        std::random_device randDev;
        std::mt19937 generator(randDev());
        std::uniform_int_distribution<int> distr(0, 1e8);

        std::set<int> m1;
        ft::set<int> ft_m1;
        std::set<int>::iterator it;
        ft::set<int>::iterator ft_it;

        for (size_t i = 0; i < 1e6; i++)
        {
            m1.insert(i);
            ft_m1.insert(i);
        }

        for (size_t i = 0; i < 1e6; i++)
        {
            int n = distr(generator);
            it = m1.find(n);
            ft_it = ft_m1.find(n);
            if (it == m1.end() && ft_it == ft_m1.end())
                continue;
            if (it == m1.end() && ft_it != ft_m1.end())
            {
                cond = false;
                break;
            }
            else
            {
                vec.push_back(*it);
                ft_vec.push_back(*ft_it);
            }
        }

        std::set<char> m;
        ft::set<char> ft_m;
        std::set<char>::iterator it2;
        ft::set<char>::iterator ft_it2;

        m.insert('a');
        m.insert('b');
        m.insert('c');
        m.insert('d');

        ft_m.insert('a');
        ft_m.insert('b');
        ft_m.insert('c');
        ft_m.insert('d');

        it2 = m.find('b');
        ft_it2 = ft_m.find('b');

        cond = cond && *it2== *ft_it2;

        if (it2 != m.end())
            m.erase(it2);
        if (ft_it2 != ft_m.end())
            ft_m.erase(ft_it2);

        cond = cond && compareMaps(m.begin(), m.end(), ft_m.begin(), ft_m.end());

        EQUAL(cond && vec == ft_vec);
    }
    std::cout <<"	count method ---	                ";
    {
        bool cond = false;
        std::set<int> m;
        ft::set<int> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(arr[i]);
            ft_m.insert(arr[i]);
        }
        cond = (m.count(65) == ft_m.count(65) && m.count(300) == ft_m.count(300));
        EQUAL(cond);
    }
    std::cout <<"	lower_bound method ---	                ";
    {
        bool cond = false;
        std::set<int> m;
        ft::set<int> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(arr[i]);
            ft_m.insert(arr[i]);
        }
        std::set<int> const c_m(m.begin(), m.end());
        ft::set<int> const c_ft_m(ft_m.begin(), ft_m.end());
        cond = (*m.lower_bound(15) == *ft_m.lower_bound(15));
        cond = (cond && (*m.lower_bound(65) == *ft_m.lower_bound(65)));
        cond = (cond && (*m.lower_bound(63) == *ft_m.lower_bound(63)));
        cond = (cond && (*m.lower_bound(120) == *ft_m.lower_bound(120)));
        cond = (cond && (*m.lower_bound(70) == *ft_m.lower_bound(70)));

        cond = (cond && (*c_m.lower_bound(15) == *c_ft_m.lower_bound(15)));
        cond = (cond && (*c_m.lower_bound(65) == *c_ft_m.lower_bound(65)));
        cond = (cond && (*c_m.lower_bound(63) == *c_ft_m.lower_bound(63)));
        cond = (cond && (*c_m.lower_bound(120) == *c_ft_m.lower_bound(120)));
        cond = (cond && (*c_m.lower_bound(70) == *c_ft_m.lower_bound(70)));
        EQUAL(cond);
    }
    std::cout <<"	upper_bound method ---	                ";
    {
        bool cond;
        /*---------------------------------- time limit test --------------------------------------------*/
        {
            time_t start, end, diff;
            int res(0), ft_res(0);

            std::set<int> m;
            ft::set<int> ft_m;
            for (size_t i = 0; i < 1e6; ++i)
            {
                m.insert(i);
                ft_m.insert(i);
            }
            start = get_time();
            res = *m.upper_bound(1e5);
            end = get_time();
            diff = end - start;
            diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

            ualarm(diff * 1e3, 0);
            ft_res = *ft_m.upper_bound(1e5);
            ualarm(0, 0);
            cond = ft_res == res;
        }
        std::set<int> m;
        ft::set<int> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(arr[i]);
            ft_m.insert(arr[i]);
        }
        std::set<int> const c_m(m.begin(), m.end());
        ft::set<int> const c_ft_m(ft_m.begin(), ft_m.end());
        cond = (cond && (*m.upper_bound(15) == *ft_m.upper_bound(15)));
        cond = (cond && (*m.upper_bound(65) == *ft_m.upper_bound(65)));
        cond = (cond && (*m.upper_bound(63) == *ft_m.upper_bound(63)));
        cond = (cond && (*m.upper_bound(120) == *ft_m.upper_bound(120)));
        cond = (cond && (*m.upper_bound(70) == *ft_m.upper_bound(70)));
        cond = (cond && (*m.upper_bound(150) == *ft_m.upper_bound(150)));

        cond = (cond && (*c_m.upper_bound(15) == *c_ft_m.upper_bound(15)));
        cond = (cond && (*c_m.upper_bound(65) == *c_ft_m.upper_bound(65)));
        cond = (cond && (*c_m.upper_bound(63) == *c_ft_m.upper_bound(63)));
        cond = (cond && (*c_m.upper_bound(120) == *c_ft_m.upper_bound(120)));
        cond = (cond && (*c_m.upper_bound(70) == *c_ft_m.upper_bound(70)));
        cond = (cond && (*c_m.upper_bound(150) == *c_ft_m.upper_bound(150)));
        EQUAL(cond);
    }
    std::cout <<"	equal_range method ---	                ";
    {
        bool cond = false;
        iter_def res;
        ft_iter_def ft_res;
        std::set<int> m;
        ft::set<int> ft_m;
        int arr[] = {20, 10, 100, 15, 60, 90, 65, 200, 150}; // size = 9
        for (size_t i = 0; i < 9; ++i)
        {
            m.insert(arr[i]);
            ft_m.insert(arr[i]);
        }
        std::set<int> const c_m(m.begin(), m.end());
        ft::set<int> const c_ft_m(ft_m.begin(), ft_m.end());

        res = m.equal_range(15);
        ft_res = ft_m.equal_range(15);
        cond = (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second));
        res = m.equal_range(65);
        ft_res = ft_m.equal_range(65);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));
        res = m.equal_range(63);
        ft_res = ft_m.equal_range(63);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));
        res = m.equal_range(120);
        ft_res = ft_m.equal_range(120);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));
        res = m.equal_range(70);
        ft_res = ft_m.equal_range(70);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));
        res = m.equal_range(150);
        ft_res = ft_m.equal_range(150);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));

        res = c_m.equal_range(15);
        ft_res = c_ft_m.equal_range(15);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));
        res = c_m.equal_range(65);
        ft_res = c_ft_m.equal_range(65);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));
        res = c_m.equal_range(63);
        ft_res = c_ft_m.equal_range(63);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));
        res = c_m.equal_range(120);
        ft_res = c_ft_m.equal_range(120);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));
        res = c_m.equal_range(70);
        ft_res = c_ft_m.equal_range(70);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));
        res = c_m.equal_range(150);
        ft_res = c_ft_m.equal_range(150);
        cond = (cond && (*(ft_res.first) == *(res.first)) && (*(ft_res.second) == *(res.second)));
        EQUAL(cond);
    }
}

void testAllocatorMethodes()
{
    std::cout <<"	get_allocator method ---		";
    {
        int psize;
        ft::set<char> mymap;
        char *p;

        // allocate an array of 5 elements using mymap's allocator:
        p = mymap.get_allocator().allocate(5);

        psize = sizeof(ft::set<char>::value_type) * 5;
        EQUAL(psize == 5);
        mymap.get_allocator().deallocate(p, 5);
    }
}
void testRetionalOperators()
{
    std::set<char> foo, bar;
    ft::set<char> ft_foo, ft_bar;
    bool res(false);
    bool ft_res(false);
    foo.insert('a');
    foo.insert('b');
    bar.insert('a');
    bar.insert('z');

    ft_foo.insert('a');
    ft_foo.insert('b');
    ft_bar.insert('a');
    ft_bar.insert('z');

    std::set<int> m, m1;
    ft::set<int> ft_m, ft_m1;
    for (size_t i = 0; i < 1e6; ++i)
    {
        m.insert(i);
        ft_m.insert(i);
    }
    for (size_t i = 0; i < 1e6; ++i)
    {
        m1.insert(i + 1);
        ft_m1.insert(i + 1);
    }

    std::cout <<"	operator == ---	                	";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;
        start = get_time();
        res = m == m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m == ft_m1;
        ualarm(0, 0);
    }

    EQUAL(((foo == bar) == (ft_foo == ft_bar)) && res == ft_res);

    std::cout <<"	operator != ---	                	";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m != m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m != ft_m1;
        ualarm(0, 0);
    }
    EQUAL((foo != bar) == (ft_foo != ft_bar) && res == ft_res);

    std::cout <<"	operator > ---	                	";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;
        start = get_time();
        res = m > m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m > ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo > bar) == (ft_foo > ft_bar)) && (res == ft_res));

    std::cout <<"	operator >= ---	                	";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m >= m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m >= ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo >= bar) == (ft_foo >= ft_bar)) && (res == ft_res));

    std::cout <<"	operator < ---	                	";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m < m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m < ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo < bar) == (ft_foo < ft_bar)) && (res == ft_res));

    std::cout <<"	operator <= ---	                	";
    /*---------------------------------- time limit test --------------------------------------------*/
    {
        time_t start, end, diff;

        start = get_time();
        res = m <= m1;
        end = get_time();
        diff = end - start;
        diff = (diff) ? (diff * TIME_FAC) : TIME_FAC;

        ualarm(diff * 1e3, 0);
        ft_res = ft_m <= ft_m1;
        ualarm(0, 0);
    }
    EQUAL(((foo <= bar) == (ft_foo <= ft_bar)) && (res == ft_res));
}

void alarm_handler(int seg)
{
    (void)seg;
    std::cout << "\033[1;33mTLE\033[0m\n";
    kill(getpid(), SIGINT);
}

int main()
{
    std::cout << "* Set Iterators;" << std::endl;
    iterator_tests();
    const_iterator_tests();
    reverse_iterator_tests();
    std::cout << std::endl;

    std::cout << "* Set Constructors;" << std::endl;
    testConstructors();
    std::cout << std::endl;

    std::cout << "* Set Iterator Methods;" << std::endl;
    testIterators();
    std::cout << std::endl;

    std::cout << "* Set Capacity Methods;" << std::endl;
    testCapacityMethods();
    std::cout << std::endl;

    std::cout << "* Set Modifiers Methods;" << std::endl;
    testModifiers();
    std::cout << std::endl;

    std::cout << "* Set Observers Methods;" << std::endl;
    testObservers();
    std::cout << std::endl;

    std::cout << "* Set Operations Methods;" << std::endl;
    testOperations();
    std::cout << std::endl;

    std::cout << "* Set Allocator Methods;" << std::endl;
    testAllocatorMethodes();
    std::cout << std::endl;

    std::cout << "* Set Retional Operators;" << std::endl;
    testRetionalOperators();
    std::cout << std::endl;

    std::cout << "* Set Non-Member Swap;" << std::endl;
    testNonMemberSwap();
    std::cout << std::endl;
    
    return 0;
}


// #include "set.hpp"

// int main()
// {
//     ft::set<std::string> s;
//     s.insert("stronk");
//     // s.insert("dog");
//     // s.insert("horse");
//     std::cout << s.size() << '\n';

//     // for(auto& str: a) std::cout << str << ' ';
// }