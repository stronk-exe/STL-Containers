/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 17:00:40 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/09 19:42:27 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXICOGRAPHICAL_COMPARE_HPP
#define LEXICOGRAPHICAL_COMPARE_HPP

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
}

#endif