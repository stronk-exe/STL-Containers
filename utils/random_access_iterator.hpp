/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:32:38 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/09 19:44:50 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include <cstddef>

namespace ft
{
    //----	random_access_random_access_iterator
	template <class T> class random_access_iterator
	{
		public:
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef T*								pointer;
			typedef T&								reference;
			typedef std::random_access_iterator_tag	iterator_category;

		private:
			pointer	p;

		public:
			random_access_iterator() : p(NULL) {};
			random_access_iterator( const random_access_iterator &other ) : p(other.p) {};
			random_access_iterator( pointer _p ) : p(_p) {};
			~random_access_iterator() {};

			random_access_iterator& operator=( const random_access_iterator &other )
			{
				if (this != &other)
					p = other.p;
				return *this;
			};
            operator random_access_iterator<T const>() const
            {
                return random_access_iterator<T const>(p);
            }
			pointer base() const
			{
				return p;
			}

			reference	operator[](difference_type index) const
			{
				return p[index];
			};
			reference	operator*() const
			{
				return *p;
			}
			pointer operator->() const
			{
				return p;
			};

			random_access_iterator&	operator++()
			{
				p++;
				return *this;
			}
			random_access_iterator	operator++(int)
			{
				random_access_iterator it(*this);
				++p;
				return it;
			}
			random_access_iterator&	operator--()
			{
				p--;
				return *this;
			}
			random_access_iterator	operator--(int)
			{
				random_access_iterator it(*this);
				--p;
				return it;
			}

			random_access_iterator operator+(const difference_type &n)   const
			{
				return random_access_iterator(p+n);
			}
			difference_type operator+(const random_access_iterator &it)   const
			{
				return p + it.p;
			}
			random_access_iterator operator-(const difference_type &n)   const
			{
				return random_access_iterator(p-n);
			}
			difference_type operator-( const random_access_iterator &it ) const
			{
				return p - it.p;
			}
    
			random_access_iterator& operator+=(difference_type n)
			{
				p += n;
				return *this;
			}
			random_access_iterator& operator-=(difference_type n)
			{
				p -= n;
				return *this;
			}

			bool operator==( const random_access_iterator &it ) const
			{
				return p == it.p;
			}
			bool operator!=( const random_access_iterator &it ) const
			{
				return p != it.p;
			}

			bool operator<( const random_access_iterator &it ) const
			{
				return p < it.p;
			}
			bool operator<=( const random_access_iterator &it ) const
			{
				return p <= it.p;
			}
			bool operator>( const random_access_iterator &it ) const
			{
				return p > it.p;
			}
			bool operator>=( const random_access_iterator &it ) const
			{
				return p >= it.p;
			}
	};

	// >> Non-member functions
		//	operator+=
		template< class T > ft::random_access_iterator<T> operator+( typename ft::random_access_iterator<T>::difference_type d, typename ft::random_access_iterator<T> &it )
		{
			return it + d;
		};
		template< class T > ft::random_access_iterator<T> operator-( typename ft::random_access_iterator<T>::difference_type d, typename ft::random_access_iterator<T> &it )
		{
			return d - it;
		};
}

#endif