/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:20:42 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/08 17:08:58 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../vector/vector.hpp"
#include "vector_Iterators.hpp"
#include "Iterator_traits.hpp"

namespace ft
{    
    //---   lexicographical_compare
        template<class InputIt1, class InputIt2> bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
        {
            for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
            {
                if (*first1 < *first2)
                    return true;
                if (*first2 < *first1)
                    return false;
            }
        
            return (first1 == last1) && (first2 != last2);
        }

    //----	enable_if
        template<bool B, class T = void> struct enable_if {};

        template<class T> struct enable_if<true, T> { typedef T type; };
    
    //----  is_integral
        template<class T, T v>
        struct integral_constant {
            static const T  value = v;
            typedef T       value_type;
            typedef integral_constant<T, v>    type; // using injected-class-name
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
        // template <> struct is_integral_type<wchar_t> : public integral_constant<wchar_t, true> {};
        // template <> struct is_integral_type<char16_t> : public integral_constant<char16_t, true> {};
        // template <> struct is_integral_type<char32_t> : public integral_constant<char32_t, true> {};

        template <> struct is_integral<bool> : public integral_constant<bool, true> {};

    //----  equal
        template<class InputIt1, class InputIt2> bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
        {
            for (; first1 != last1; ++first1, ++first2) {
                if (!(*first1 == *first2)) {
                    return false;
                }
            }
            return true;
        }
}