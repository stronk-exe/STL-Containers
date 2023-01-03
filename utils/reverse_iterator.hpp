/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:08:58 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/03 16:04:05 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "Iterator_traits.hpp"
#include "random_access_iterator.hpp"

namespace ft
{
	//----	Reverse_iterator
	template <typename iterator> class reverse_iterator
	{
		public:
			// typedef T			value_type;
			// typedef ptrdiff_t	difference_type;
			// typedef T*			pointer;
			// typedef T&			reference;
			typedef	iterator	iter_type;
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
			iter_type	p;

		public:
			reverse_iterator() : p(iterator()) {};
			explicit reverse_iterator(iter_type _p) : p(_p) {};
			// explicit reverse_iterator(pointer _p) : p(_p) {};
			template<class iter> reverse_iterator( const reverse_iterator<iter> &other ) : p(other.base()) {};
			~reverse_iterator() {};

			reverse_iterator& operator=( const reverse_iterator &other )
			{
				if (this != &other)
					p = other.p;
				return *this;
			};

			iter_type base() const
			{
				return p;
			}

			reference	operator[](difference_type index) const
			{
				return p[index-1];
			};
			reference	operator*() const
			{
				// return *p;
				iter_type rit = p;
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

			reverse_iterator operator+(difference_type n)   const
			{
				return reverse_iterator(p-n);
			}
			reverse_iterator operator-(int n)   const
			{
				return reverse_iterator(p+n);
			}
			reverse_iterator& operator+=(difference_type n)
			{
				p -= n;
				return *this;
			}
			reverse_iterator& operator-=(difference_type n)
			{
				p += n;
				return *this;
			}

			// bool operator==( const iterator &it ) const
			// {
			// 	return p == it.p;
			// }
			// bool operator!=( const iterator &it ) const
			// {
			// 	return p != it.p;
			// }
			// bool operator<( const iterator &it ) const
			// {
			// 	return p < it.p;
			// }
			// bool operator<=( const iterator &it ) const
			// {
			// 	return p <= it.p;
			// }
			// bool operator>( const iterator &it ) const
			// {
			// 	return p > it.p;
			// }
			// bool operator>=( const iterator &it ) const
			// {
			// 	return p >= it.p;
			// }

	};

	// >> Non-member functions
				// template< class T > reverse_iterator<T> operator+( typename reverse_iterator<T>::difference_type d, const reverse_iterator<T> &rit )
				// {
				// 	return d + rit;
				// };
				// template< class X, class Y > reverse_iterator<X> operator+( typename reverse_iterator<X>::difference_type d, const reverse_iterator<Y> &rit )
				// {
				// 	return d + rit;
				// };

				template< class T > typename reverse_iterator<T>::difference_type operator-( const reverse_iterator<T> &rit1, const reverse_iterator<T> &rit2 )
				{
					return rit2 - rit1;
				};
				template< class X, class Y > typename reverse_iterator<X>::difference_type operator-( const reverse_iterator<X> &rit1, const reverse_iterator<Y> &rit2 )
				{
					return rit2 - rit1;
				};
			
		//	operator==
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
			template< class T > reverse_iterator<T> operator+( typename ft::reverse_iterator<T>::difference_type d, typename ft::reverse_iterator<T> &it )
			{
				return it + d;
			};
			template< class X, class Y > bool operator+( typename reverse_iterator<X>::difference_type d, const reverse_iterator<Y> &it )
			{
				return it + d;
			};
		//	operator -
			// template< class T > typename reverse_iterator<T>::difference_type operator-( const reverse_iterator<T> &it1, const reverse_iterator<T> &it2 )
			// {
			// 	return it1.base() - it2.base();
			// };
			template< class X, class Y > typename ft::reverse_iterator<X>::difference_type operator-( typename ft::reverse_iterator<X> &it1, typename ft::reverse_iterator<Y> &it2 )
			{
				return it2.base() - it1.base();
			};
}

#endif