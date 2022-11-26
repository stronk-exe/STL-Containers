/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:37:29 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/21 15:29:20 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include "Iterator_traits.hpp"
// #include "utils.hpp"
// #include "../vector/vector.hpp"
#include <cstddef>

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
	
	template <typename T> class Iterator
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
			typedef T			value_type;
			typedef ptrdiff_t	difference_type;
			typedef T*			pointer;
			typedef T&			reference;
			// typedef T													it_type;
			// typedef typename ft::iterator_traits<T>::value_type			value_type;
			// typedef typename ft::iterator_traits<T>::pointer			pointer;
			// typedef typename ft::iterator_traits<T>::reference			reference;
			// typedef typename ft::iterator_traits<T>::differece_type		differece_type;
			// typedef typename ft::iterator_traits<T>::iterator_category	iterator_category;
		// private:
		// 	it_type p;
			// using valueType = typename vector::valueType;
			// using pointerType = valueType*;
			// using pointerType = valueType&;
			// Iterator(Iterator &i, size_t pos=0) {};
			// Iterator	&operator++() {};

			// iterator_traits() {};
			// explicit	iterator_traits(T *data) {};
			// iterator_traits(iterator_traits &v) {};
		public:
			Iterator() : p(NULL) {};
			Iterator(pointer _p) : p(_p) {};
			Iterator( const Iterator &other ) : p(other.p) {};
			~Iterator() {};

			Iterator& operator=( const Iterator &other )
			{
				if (*this != other)
					p = other.p;
				return *this;
			};
			pointer base() const
			{
				return p;
			}

			reference	operator[](int index)
			{
				return p[index];
			};
			reference	operator*()
			{
				return *p;
			}
			pointer operator->() const
			{
				return p;
			};

			Iterator&	operator++()
			{
				p++;
				return *this;
			}
			Iterator	operator++(int)
			{
				Iterator it = *this;
				++(*this);
				return it;
			}
			Iterator&	operator--()
			{
				p--;
				return *this;
			}
			Iterator	operator--(int)
			{
				Iterator it = *this;
				--(*this);
				return it;
			}

			Iterator operator+(int n)   const
			{
				// Iterator it = *this;
				// it.p += n;
				// return it;
				return Iterator(p+n);
			}
			Iterator operator-(int n)   const
			{
				// Iterator p(*this);
				// return p -= n;
				return Iterator(p-n);
			}
			Iterator& operator+=(int n)
			{
				p += n;
				return *this;
			}
			Iterator& operator-=(int n)
			{
				p -= n;
				return *this;
			}


			/*bool operator<(Iterator const& other)  const
			{
				return p <  other.p;
			}
			bool operator<=(Iterator const& other) const
			{
				return p <= other.p;
			}
			bool operator>(Iterator const& other)  const
			{
				return p >  other.p;
			}
			bool operator>=(Iterator const& other) const
			{
				return p >= other.p;
			}
			bool operator!=(const Iterator &other) const
			{
				return p != other.p;
			}
			bool operator==(const Iterator &other) const
			{
				return p == other.p;
			}*/

			// template< class X, class Y > friend bool operator==( const Iterator<X>& it1, const Iterator<Y>& it2 );
			// template< class X, class Y > friend bool operator!=( const Iterator<X>& it1, const Iterator<Y>& it2 );
			// template< class X, class Y > friend bool operator<( const Iterator<X>& it1, const Iterator<Y>& it2 );
			// template< class X, class Y > friend bool operator<=( const Iterator<X>& it1, const Iterator<Y>& it2 );
			// template< class X, class Y > friend bool operator>( const Iterator<X>& it1, const Iterator<Y>& it2 );
			// template< class X, class Y > friend bool operator>=( const Iterator<X>& it1, const Iterator<Y>& it2 );
		private:
			pointer	p;
	};

	// >> Non-member functions
		//	operator==
			template< class X, class Y > bool operator==( const Iterator<X>& it1, const Iterator<Y>& it2 )
			{
				return it1.base() == it2.base();
			};

		//	operator!=
			template< class X, class Y > bool operator!=( const Iterator<X>& it1, const Iterator<Y>& it2 )
			{
				return it1.base() != it2.base();
			};

		//	operator<
			template< class X, class Y > bool operator<( const Iterator<X>& it1, const Iterator<Y>& it2 )
			{
				return it1.base() < it2.base();
			};

		//	operator<=
			template< class X, class Y > bool operator<=( const Iterator<X>& it1, const Iterator<Y>& it2 )
			{
				return it1.base() <= it2.base();
			};

		//	operator>
			template< class X, class Y > bool operator>( const Iterator<X>& it1, const Iterator<Y>& it2 )
			{
				return it1.base() > it2.base();
			};

		//	operator>=
			template< class X, class Y > bool operator>=( const Iterator<X>& it1, const Iterator<Y>& it2 )
			{
				return it1.base() >= it2.base();
			};

		//	operator +
			template< class X > Iterator<X> operator+( typename Iterator<X>::differece_type n, const Iterator<X>& it1 )
			{
				return it1.base() + n;
			};
		//	operator -
			template< class X, class Y > typename Iterator<X>::difference_type operator-( const Iterator<X>& it1, const Iterator<Y>& it2 )
			{
				return it1.base() - it2.base();
			};
	// template <class Vectoriterator> bool operator<()
	// template <typename vector> class const_iterator
	// {
	// 	// private:
	// 	// 	typedef Iterator					iterator_traits_iterator;
			
	// 	// 	typedef Iterator::differece_type	difference_type;
	// 		// typedef typename Iterator::value_type		value_type;
	// 		// typedef typename Iterator::pointer			pointer;

	// 		// typedef typename vetor::T				value_type;
	// 		// typedef typename vetor::T*				pointer;
	// 		// typedef typename vetor::T&				reference;
	// 	// 	typedef Iterator::iterator_category	iterator_category;
		
	// 	public:
	// 		typedef typename vector::T				value_type;
	// 		typedef typename vector::T*				pointer;
	// 		typedef typename vector::T&				reference;
	// 		// using valueType = typename vector::valueType;
	// 		// using pointerType = valueType*;
	// 		// using pointerType = valueType&;
	// 		// Iterator(Iterator &i, size_t pos=0) {};
	// 		// Iterator	&operator++() {};

	// 		// iterator_traits() {};
	// 		// explicit	iterator_traits(T *data) {};
	// 		// iterator_traits(iterator_traits &v) {};
	// 		const_iterator(pointer _ptr) : ptr(_ptr) {};

	// 		const_iterator&	operator++()
	// 		{
	// 			ptr++;
	// 			return *this;
	// 		}
	// 		const_iterator	operator++(int)
	// 		{
	// 			const_iterator it = *this;
	// 			++(*this);
	// 			return it;
	// 		}
	// 		const_iterator&	operator--()
	// 		{
	// 			ptr--;
	// 			return *this;
	// 		}
	// 		const_iterator	operator--(int)
	// 		{
	// 			const_iterator it = *this;
	// 			--(*this);
	// 			return it;
	// 		}
	// 	private:
	// 		pointer	ptr;
	// };
	
	// template <class T> class iterator_traits<T*>
	// {
		
	// };

	// template <class T> class iterator_traits<const T*>
	// {
		
	// };
/*	template< class Iter > class Reverse_iterator
	{
		public:
			typedef Iter													iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type			value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type	difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer			pointer;
			typedef typename ft::iterator_traits<Iter>::reference			reference;
			
			Reverse_iterator(pointer _p) : p(_p) {};
			Reverse_iterator&	operator++()
			{
				p--;
				return *this;
			}
			Reverse_iterator	operator++(int)
			{
				Reverse_iterator it = *this;
				--(*this);
				return it;
			}
			Reverse_iterator&	operator--()
			{
				p++;
				return *this;
			}
			Reverse_iterator	operator--(int)
			{
				Reverse_iterator it = *this;
				++(*this);
				return it;
			}
			Reverse_iterator	operator[](int index)
			{
				return *(p+index);
			};
			Reverse_iterator	operator*()
			{
				return *p;
			}
			bool	operator==(const Reverse_iterator& other) const
			{
				return p == other.p;
			}
			bool	operator!=(const Reverse_iterator& other) const
			{
				return !(*this == other);
			}
			operator Reverse_iterator<const Iter>()
			{
				return (const pointer) p;
			}
			// ~reverse_iterator()
			// {
				
			// };
		private:
			pointer p;
	};
*/
}

#endif