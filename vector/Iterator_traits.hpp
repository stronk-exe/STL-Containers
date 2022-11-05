/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:33:44 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/05 16:19:55 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	template <typename vector> class iterator
	{
		// private:
		// 	typedef Iterator					iterator_traits_iterator;
			
		// 	typedef Iterator::differece_type	difference_type;
			// typedef typename Iterator::value_type		value_type;
			// typedef typename Iterator::pointer			pointer;

			// typedef typename vetor::T				value_type;
			// typedef typename vetor::T*				pointer;
			// typedef typename vetor::T&				reference;
		// 	typedef Iterator::iterator_category	iterator_category;
		private:
			pointer	ptr;
		public:
			using valueType = typename vector::valueType;
			using pointerType = valueType*;
			using pointerType = valueType&;
			// Iterator(Iterator &i, size_t pos=0) {};
			// Iterator	&operator++() {};

			// iterator_traits() {};
			// explicit	iterator_traits(T *data) {};
			// iterator_traits(iterator_traits &v) {};
			iterator(valueType _ptr) : ptr(_ptr) {};

			iterator&	operator++()
			{
				ptr++;
				return *this;
			}
			iterator	operator++(int)
			{
				iterator it = *this;
				++(*this);
				return it;
			}
			iterator&	operator--()
			{
				ptr--;
				return *this;
			}
			iterator	operator--(int)
			{
				iterator it = *this;
				--(*this);
				return it;
			}
	};
	
	// template <class T> class iterator_traits<T*>
	// {
		
	// };

	// template <class T> class iterator_traits<const T*>
	// {
		
	// };
}

#endif