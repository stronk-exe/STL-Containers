/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 16:57:56 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/01 16:58:58 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

namespace ft
{
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

#endif