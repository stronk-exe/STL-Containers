/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:33:44 by ael-asri          #+#    #+#             */
/*   Updated: 2022/10/27 10:45:09 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template <class Iterator> class iterator_traits
	{
		typedef difference_type Iterator::differece_type;
		typedef value_type Iterator::value_type;
		typedef pointer Iterator::pointer;
		typedef iterator_category Iterator::iterator_category;
		
	};
	
	template <class T> class iterator_traits<T*>
	{
		
	};

	template <class T> class iterator_traits<const T*>
	{
		
	};
}