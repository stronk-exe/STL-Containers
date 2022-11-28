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
	//----	random_access_iterator
	template <typename T> class Iterator
	{	
		public:
			typedef T			value_type;
			typedef ptrdiff_t	difference_type;
			typedef T*			pointer;
			typedef T&			reference;

			// typedef	T														iter_type;
			// typedef	typename	ft::iterator_traits<T>::value_type			value_type;
			// typedef	typename	ft::iterator_traits<T>::difference_type		difference_type;
			// typedef	typename	ft::iterator_traits<T>::reference			reference;
			// typedef	typename	ft::iterator_traits<T>::pointer				pointer;
			// typedef	typename	ft::iterator_traits<T>::iterator_category	iterator_category;

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

			reference	operator[](difference_type index)
			{
				return *(p+index);
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
				return Iterator(p+n);
			}
			Iterator operator-(int n)   const
			{
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

	//----	Reverse_iterator
	template <typename iterator> class Reverse_iterator
	{	
		public:
			// typedef T			value_type;
			// typedef ptrdiff_t	difference_type;
			// typedef T*			pointer;
			// typedef T&			reference;
			typedef	iterator	iterator_type;
			typedef	typename	ft::iterator_traits<iterator>::differece_type	differece_type;
			typedef	typename	ft::iterator_traits<iterator>::reference		reference;
			typedef	typename	ft::iterator_traits<iterator>::pointer			pointer;

		public:
			Reverse_iterator() : p(NULL) {};
			Reverse_iterator(iterator_type _p) : p(_p) {};
			Reverse_iterator( const Reverse_iterator &other ) : p(other.p) {};
			~Reverse_iterator() {};

			Reverse_iterator& operator=( const Reverse_iterator &other )
			{
				if (*this != other)
					p = other.p;
				return *this;
			};
			pointer base() const
			{
				return p;
			}

			reference	operator[](differece_type index)
			{
				return *(*this+index);
			};
			reference	operator*()
			{
				// return *p;
				Reverse_iterator rit = p;
				--rit;
				return *rit;
			}
			pointer operator->() const
			{
				return &(operator*());
			};

			Reverse_iterator&	operator++()
			{
				--p;
				return *this;
			}
			Reverse_iterator	operator++(int)
			{
				Reverse_iterator it = *this;
				++(*this);
				return it;
			}
			Reverse_iterator&	operator--()
			{
				++p;
				return *this;
			}
			Reverse_iterator	operator--(int)
			{
				Reverse_iterator it = *this;
				--(*this);
				return it;
			}

			Reverse_iterator operator+(int n)   const
			{
				return Reverse_iterator(p-n);
			}
			Reverse_iterator operator-(int n)   const
			{
				return Reverse_iterator(p+n);
			}
			Reverse_iterator& operator+=(int n)
			{
				p -= n;
				return *this;
			}
			Reverse_iterator& operator-=(int n)
			{
				p += n;
				return *this;
			}

		private:
			iterator_type	p;
	};

	// >> Non-member functions
		//	operator==
			template< class X, class Y > bool operator==( const Reverse_iterator<X>& it1, const Reverse_iterator<Y>& it2 )
			{
				return it1.base() == it2.base();
			};

		//	operator!=
			template< class X, class Y > bool operator!=( const Reverse_iterator<X>& it1, const Reverse_iterator<Y>& it2 )
			{
				return it1.base() != it2.base();
			};

		//	operator<
			template< class X, class Y > bool operator<( const Reverse_iterator<X>& it1, const Reverse_iterator<Y>& it2 )
			{
				return it1.base() > it2.base();
			};

		//	operator<=
			template< class X, class Y > bool operator<=( const Reverse_iterator<X>& it1, const Reverse_iterator<Y>& it2 )
			{
				return it1.base() >= it2.base();
			};

		//	operator>
			template< class X, class Y > bool operator>( const Reverse_iterator<X>& it1, const Reverse_iterator<Y>& it2 )
			{
				return it1.base() < it2.base();
			};

		//	operator>=
			template< class X, class Y > bool operator>=( const Reverse_iterator<X>& it1, const Reverse_iterator<Y>& it2 )
			{
				return it1.base() <= it2.base();
			};

		//	operator +
			template< class X > Reverse_iterator<X> operator+( typename Reverse_iterator<X>::differece_type n, const Reverse_iterator<X>& it1 )
			{
				return it1.base() - n;
			};
		//	operator -
			template< class X, class Y > typename Reverse_iterator<X>::difference_type operator-( const Reverse_iterator<X>& it1, const Reverse_iterator<Y>& it2 )
			{
				return it1.base() + it2.base();
			};
}

#endif