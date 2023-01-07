/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:59:24 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/07 22:43:28 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft
{
	//----	enable_if
        template<bool B, class T = void> struct enable_if {};

        template<class T> struct enable_if<true, T> { typedef T type; };
	
	 //----  is_integral
        template<class T, T v>
        struct integral_constant {
            static const T  value = v;
            typedef T       value_type;
            typedef integral_constant<T, v>    type;
            operator T() { return value; }
        };

        template <typename T> struct is_integral : public integral_constant<bool, false> {};

        template <> struct is_integral<int> : public integral_constant<int, true> {};
        template <> struct is_integral<unsigned int> : public integral_constant<unsigned int, true> {};
        template <> struct is_integral<short> : public integral_constant<short, true> {};
        template <> struct is_integral<unsigned short> : public integral_constant<unsigned short, true> {};
        template <> struct is_integral<long> : public integral_constant<long, true> {};
        template <> struct is_integral<unsigned long> : public integral_constant<unsigned long, true> {};
        template <> struct is_integral<long long> : public integral_constant<long long, true> {};
        template <> struct is_integral<unsigned long long> : public integral_constant<unsigned long long, true> {};

        template <> struct is_integral<char> : public integral_constant<char, true> {};
        template <> struct is_integral<signed char> : public integral_constant<signed char, true> {};
        template <> struct is_integral<unsigned char> : public integral_constant<unsigned char, true> {};

        template <> struct is_integral<bool> : public integral_constant<bool, true> {};
}

#endif