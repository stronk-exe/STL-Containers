/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_Iterators.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:37:29 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/08 17:09:49 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATORS_HPP
#define VECTOR_ITERATORS_HPP

#include "Iterator_traits.hpp"
// #include "utils.hpp"
// #include "../vector/vector.hpp"
#include <cstddef>

namespace ft
{
	//----	random_access_iterator
	template <typename T> class iterator
	{	
		public:
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef ft::random_access_iterator_tag	iterator_category;

			// typedef	T														iter_type;
			// typedef	typename	ft::iterator_traits<T>::value_type			value_type;
			// typedef	typename	ft::iterator_traits<T>::difference_type		difference_type;
			// typedef	typename	ft::iterator_traits<T>::reference			reference;
			// typedef	typename	ft::iterator_traits<T>::pointer				pointer;
			// typedef	typename	ft::iterator_traits<T>::iterator_category	iterator_category;
		private:
			pointer	p;

		public:
			iterator() : p(NULL) {};
			explicit iterator( pointer _p ) : p(_p) {};
			iterator( const iterator &other ) : p(other.p) {};
			~iterator() {};

			iterator& operator=( const iterator &other )
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

			iterator&	operator++()
			{
				p++;
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
				p--;
				return *this;
			}
			iterator	operator--(int)
			{
				iterator it = *this;
				--(*this);
				return it;
			}

			iterator operator+(int n)   const
			{
				return iterator(p+n);
			}
			iterator operator-(int n)   const
			{
				return iterator(p-n);
			}
			difference_type operator-( const iterator &it ) const
			{
				return p - it.p;
			}
			iterator& operator+=(int n)
			{
				p += n;
				return *this;
			}
			iterator& operator-=(int n)
			{
				p -= n;
				return *this;
			}

			bool operator==( const iterator &it ) const
			{
				return p == it.p;
			}
			bool operator!=( const iterator &it ) const
			{
				return p != it.p;
			}
			bool operator<( const iterator &it ) const
			{
				return p < it.p;
			}
			bool operator<=( const iterator &it ) const
			{
				return p <= it.p;
			}
			bool operator>( const iterator &it ) const
			{
				return p > it.p;
			}
			bool operator>=( const iterator &it ) const
			{
				return p >= it.p;
			}

	};

	// >> Non-member functions
		//	operator+=
				template< class T > iterator<T> operator+( typename iterator<T>::difference_type d, const iterator<T> &it )
				{
					return d + it;
				};
				template< class T > iterator<T> operator-( typename iterator<T>::difference_type d, const iterator<T> &it )
				{
					return d - it;
				};
		/*	template< class X, class Y > bool operator==( const iterator<X>& it1, const iterator<Y>& it2 )
			{
				return it1.base() == it2.base();
			};

		//	operator!=
			template< class X, class Y > bool operator!=( const iterator<X>& it1, const iterator<Y>& it2 )
			{
				return it1.base() != it2.base();
			};

		//	operator<
			template< class X, class Y > bool operator<( const iterator<X>& it1, const iterator<Y>& it2 )
			{
				return it1.base() < it2.base();
			};

		//	operator<=
			template< class X, class Y > bool operator<=( const iterator<X>& it1, const iterator<Y>& it2 )
			{
				return it1.base() <= it2.base();
			};

		//	operator>
			template< class X, class Y > bool operator>( const iterator<X>& it1, const iterator<Y>& it2 )
			{
				return it1.base() > it2.base();
			};

		//	operator>=
			template< class X, class Y > bool operator>=( const iterator<X>& it1, const iterator<Y>& it2 )
			{
				return it1.base() >= it2.base();
			};

		//	operator +
			template< class X > iterator<X> operator+( typename iterator<X>::difference_type n, const iterator<X>& it1 )
			{
				return it1.base() + n;
			};
		//	operator -
			template< class X, class Y > typename iterator<X>::difference_type operator-( const iterator<X>& it1, const iterator<Y>& it2 )
			{
				return it1.base() - it2.base();
			};*/

	//----	Reverse_iterator
	template <typename iterator> class reverse_iterator
	{	
		public:
			// typedef T			value_type;
			// typedef ptrdiff_t	difference_type;
			// typedef T*			pointer;
			// typedef T&			reference;
			typedef	iterator	iterator_type;
			typedef	typename	ft::iterator_traits<iterator>::value_type			value_type;
			typedef	typename	ft::iterator_traits<iterator>::iterator_category	iterator_category;
			typedef	typename	ft::iterator_traits<iterator>::difference_type		difference_type;
			typedef	typename	ft::iterator_traits<iterator>::reference			reference;
			typedef	typename	ft::iterator_traits<iterator>::pointer				pointer;

			// typedef T								value_type;
			// typedef ptrdiff_t						difference_type;
			// typedef T*								pointer;
			// typedef T&								reference;
			// typedef ft::random_access_iterator_tag	iterator_category;
		private:
			iterator_type	p;

		public:
			reverse_iterator() : p(NULL) {};
			explicit reverse_iterator(iterator_type _p) : p(_p) {};
			reverse_iterator( const reverse_iterator &other ) : p(other.p) {};
			~reverse_iterator() {};

			reverse_iterator& operator=( const reverse_iterator &other )
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
				return *(*this+index);
			};
			reference	operator*()
			{
				// return *p;
				reverse_iterator rit = p;
				--rit;
				return *rit;
			}
			pointer operator->() const
			{
				return &(operator*());
			};

			reverse_iterator&	operator++()
			{
				--p;
				return *this;
			}
			reverse_iterator	operator++(int)
			{
				reverse_iterator it = *this;
				++(*this);
				return it;
			}
			reverse_iterator&	operator--()
			{
				++p;
				return *this;
			}
			reverse_iterator	operator--(int)
			{
				reverse_iterator it = *this;
				--(*this);
				return it;
			}

			reverse_iterator operator+(int n)   const
			{
				return reverse_iterator(p-n);
			}
			reverse_iterator operator-(int n)   const
			{
				return reverse_iterator(p+n);
			}
			reverse_iterator& operator+=(int n)
			{
				p -= n;
				return *this;
			}
			reverse_iterator& operator-=(int n)
			{
				p += n;
				return *this;
			}

			bool operator==( const iterator &it ) const
			{
				return p == it.p;
			}
			bool operator!=( const iterator &it ) const
			{
				return p != it.p;
			}
			bool operator<( const iterator &it ) const
			{
				return p < it.p;
			}
			bool operator<=( const iterator &it ) const
			{
				return p <= it.p;
			}
			bool operator>( const iterator &it ) const
			{
				return p > it.p;
			}
			bool operator>=( const iterator &it ) const
			{
				return p >= it.p;
			}

	};

	// >> Non-member functions
		//	operator==
				template< class T > bool operator+( typename iterator<T>::difference_type d, const iterator<T> &it )
				{
					return d + it;
				};
				template< class T > bool operator-( typename iterator<T>::difference_type d, const iterator<T> &it )
				{
					return d - it;
				};
			
			template< class T > bool operator==( const reverse_iterator<T>& it1, const reverse_iterator<T>& it2 )
			{
				return it1.base() == it2.base();
			};
			template< class X, class Y > bool operator==( const reverse_iterator<X>& it1, const reverse_iterator<Y>& it2 )
			{
				return it1.base() == it2.base();
			};

		//	operator!=
			template< class T > bool operator!=( const reverse_iterator<T>& it1, const reverse_iterator<T>& it2 )
			{
				return it1.base() != it2.base();
			};
			template< class X, class Y > bool operator!=( const reverse_iterator<X>& it1, const reverse_iterator<Y>& it2 )
			{
				return it1.base() != it2.base();
			};

		//	operator<
			template< class T > bool operator<( const reverse_iterator<T>& it1, const reverse_iterator<T>& it2 )
			{
				return it1.base() > it2.base();
			};
			template< class X, class Y > bool operator<( const reverse_iterator<X>& it1, const reverse_iterator<Y>& it2 )
			{
				return it1.base() > it2.base();
			};

		//	operator<=
			template< class T > bool operator<=( const reverse_iterator<T>& it1, const reverse_iterator<T>& it2 )
			{
				return it1.base() >= it2.base();
			};
			template< class X, class Y > bool operator<=( const reverse_iterator<X>& it1, const reverse_iterator<Y>& it2 )
			{
				return it1.base() >= it2.base();
			};

		//	operator>
			template< class T > bool operator>( const reverse_iterator<T>& it1, const reverse_iterator<T>& it2 )
			{
				return it1.base() < it2.base();
			};
			template< class X, class Y > bool operator>( const reverse_iterator<X>& it1, const reverse_iterator<Y>& it2 )
			{
				return it1.base() < it2.base();
			};

		//	operator>=
			template< class T > bool operator>=( const reverse_iterator<T>& it1, const reverse_iterator<T>& it2 )
			{
				return it1.base() <= it2.base();
			};
			template< class X, class Y > bool operator>=( const reverse_iterator<X>& it1, const reverse_iterator<Y>& it2 )
			{
				return it1.base() <= it2.base();
			};

		//	operator +
			template< class T > reverse_iterator<T> operator+( typename reverse_iterator<T>::difference_type d, const reverse_iterator<T> &it )
			{
				return it + d;
			};
			template< class X, class Y > bool operator>=( typename reverse_iterator<X>::difference_type d, const reverse_iterator<Y> &it )
			{
				return it + d;
			};
		//	operator -
			template< class T > typename reverse_iterator<T>::difference_type operator-( const reverse_iterator<T> &it1, const reverse_iterator<T> &it2 )
			{
				return it1.p - it2.p;
			};
			template< class X, class Y > typename reverse_iterator<X>::difference_type operator-( reverse_iterator<X> &it1, const reverse_iterator<Y> &it2 )
			{
				return it1.p - it2.p;
			};
}

#endif