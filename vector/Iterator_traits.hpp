/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:33:44 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/08 17:07:06 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "vector.hpp"

namespace ft
{
/*	template <typename vector> class InputIterator
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
		
		public:
			typedef typename vector::T				value_type;
			typedef typename vector::T*				pointer;
			typedef typename vector::T&				reference;
			// using valueType = typename vector::valueType;
			// using pointerType = valueType*;
			// using pointerType = valueType&;
			// Iterator(Iterator &i, size_t pos=0) {};
			// Iterator	&operator++() {};

			// iterator_traits() {};
			// explicit	iterator_traits(T *data) {};
			// iterator_traits(iterator_traits &v) {};
			InputIterator(pointer _ptr) : ptr(_ptr) {};

			InputIterator&	operator++()
			{
				ptr++;
				return *this;
			}
			InputIterator	operator++(int)
			{
				InputIterator it = *this;
				++(*this);
				return it;
			}
			InputIterator&	operator--()
			{
				ptr--;
				return *this;
			}
			InputIterator	operator--(int)
			{
				InputIterator it = *this;
				--(*this);
				return it;
			}
		private:
			pointer	ptr;
	};*/
	
	template <typename T> class Vectoriterator
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
		
		public:
			typedef T				vt;
			typedef T*				ptr;
			typedef T&				ref;
			// using valueType = typename vector::valueType;
			// using pointerType = valueType*;
			// using pointerType = valueType&;
			// Iterator(Iterator &i, size_t pos=0) {};
			// Iterator	&operator++() {};

			// iterator_traits() {};
			// explicit	iterator_traits(T *data) {};
			// iterator_traits(iterator_traits &v) {};
			Vectoriterator(ptr _p) : p(_p) {};

			Vectoriterator&	operator++()
			{
				p++;
				return *this;
			}
			Vectoriterator	operator++(int)
			{
				Vectoriterator it = *this;
				++(*this);
				return it;
			}
			Vectoriterator&	operator--()
			{
				p--;
				return *this;
			}
			Vectoriterator	operator--(int)
			{
				Vectoriterator it = *this;
				--(*this);
				return it;
			}
			ref	operator[](int index)
			{
				return *(p+index);
			};
			Vectoriterator	operator*()
			{
				return 1;
			}
			bool	operator==(const Vectoriterator& other) const
			{
				return p == other.p;
			}
			bool	operator!=(const Vectoriterator& other) const
			{
				return !(*this == other);
			}
		private:
			ptr	p;
	};
	// template <class Vectoriterator> bool operator<()
	template <typename vector> class const_iterator
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
		
		public:
			typedef typename vector::T				value_type;
			typedef typename vector::T*				pointer;
			typedef typename vector::T&				reference;
			// using valueType = typename vector::valueType;
			// using pointerType = valueType*;
			// using pointerType = valueType&;
			// Iterator(Iterator &i, size_t pos=0) {};
			// Iterator	&operator++() {};

			// iterator_traits() {};
			// explicit	iterator_traits(T *data) {};
			// iterator_traits(iterator_traits &v) {};
			const_iterator(pointer _ptr) : ptr(_ptr) {};

			const_iterator&	operator++()
			{
				ptr++;
				return *this;
			}
			const_iterator	operator++(int)
			{
				const_iterator it = *this;
				++(*this);
				return it;
			}
			const_iterator&	operator--()
			{
				ptr--;
				return *this;
			}
			const_iterator	operator--(int)
			{
				const_iterator it = *this;
				--(*this);
				return it;
			}
		private:
			pointer	ptr;
	};
	
	// template <class T> class iterator_traits<T*>
	// {
		
	// };

	// template <class T> class iterator_traits<const T*>
	// {
		
	// };
}

#endif