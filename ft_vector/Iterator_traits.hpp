/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:33:44 by ael-asri          #+#    #+#             */
/*   Updated: 2022/10/30 14:19:38 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	template <class Iterator> class iterator_traits
	{
		private:
			typedef difference_type		Iterator::differece_type;
			typedef value_type			Iterator::value_type;
			typedef pointer				Iterator::pointer;
			typedef iterator_category	Iterator::iterator_category;
	};
	
	template <class T> class iterator_traits<T*>
	{
		
	};

	template <class T> class iterator_traits<const T*>
	{
		
	};
}

#endif