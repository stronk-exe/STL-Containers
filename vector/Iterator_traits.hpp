/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:33:44 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/04 19:27:02 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	template <typename Iterator> class iterator
	{
		// private:
		// 	typedef Iterator					iterator_traits_iterator;
			
		// 	typedef Iterator::differece_type	difference_type;
			typedef Iterator::value_type		value_type;
			typedef Iterator::pointer			pointer;
		// 	typedef Iterator::iterator_category	iterator_category;
		
		public:
			// Iterator(Iterator &i, size_t pos=0) {};
			// Iterator	&operator++() {};

			// iterator_traits() {};
			// explicit	iterator_traits(T *data) {};
			// iterator_traits(iterator_traits &v) {};
			iterator(pointer ptr) : v(ptr) {};
	};
	
	// template <class T> class iterator_traits<T*>
	// {
		
	// };

	// template <class T> class iterator_traits<const T*>
	// {
		
	// };
}

#endif