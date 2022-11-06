/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:33:44 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/06 13:26:06 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

namespace ft
{
	template <typename vector> class InputIterator
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
	};
	
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
			iterator(pointer _ptr) : ptr(_ptr) {};

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
			iterator	operator*(int)
			{
				// iterator it = *this;
				// --(*this);
				return *this;
			}
			iterator	operator!=(int)
			{
				iterator it = *this;
				--(*this);
				return it;
			}
			iterator	operator=(int)
			{
				iterator it = *this;
				--(*this);
				return it;
			}
		private:
			pointer	ptr;
	};
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