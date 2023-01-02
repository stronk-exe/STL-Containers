/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:56:43 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/02 13:35:37 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
#define PAIR_HPP

namespace  ft
{
	//----  pair
    template<class T1, class T2> struct pair
    {
        public:
            typedef T1 first_type;
            typedef T2 second_type;

            first_type first;
            second_type second;

            pair() : first(), second() {};
            pair( const first_type &a, const second_type &b ) : first(a), second(b) {};
            template<class X, class Y> pair( const pair<X, Y> &pr ) : first(pr.first), second(pr.second) {};
            ~pair() {};

            pair& operator=( const pair& pr )
            {
                if (this != &pr)
                {
                    first = pr.first;
                    second = pr.second;
                }
                return *this;
            };
    };
    //----  pair Non-Member functions
    template<class T1, class T2> bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }
    template<class T1, class T2> bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        return !(lhs == rhs);
    }
    template<class T1, class T2> bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        return (lhs.first < rhs.first || (!(lhs.first < rhs.first) && lhs.second < rhs.second));
    }
    template<class T1, class T2> bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        return !(rhs < lhs);
    }
    template<class T1, class T2> bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        return rhs < lhs;
    }
    template<class T1, class T2> bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs )
    {
        return !(lhs < rhs);
    }
    template<class T1, class T2> ft::pair<T1, T2> make_pair( T1 x, T2 y )
    {
        return ft::pair<T1, T2>(x, y);
    }
}


#endif