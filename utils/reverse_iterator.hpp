/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:08:58 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/26 17:13:00 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "Iterator_traits.hpp"
#include "vector_Iterators.hpp"

namespace ft
{
	// template <class Iterator> class reverse_iterator
	// {
	// 	private:
	// 		size_type	pos;
	// 		typedef Iterator										iterator_type;
	// 		typedef iterator_traits<Iterator>::iterator_category	iterator_category;
	// 		typedef iterator_traits<Iterator>::value_type			value_type
	// 		typedef iterator_traits<Iterator>::difference_type		difference_type;
	// 		typedef iterator_traits<Iterator>::pointer				pointer;
	// 		typedef iterator_traits<Iterator>::reference			reference;
	// 	public:
	// 		// Member functions
	// 				//----	Constractors
	// 					// default
	// 					reverse_iterator() {};

	// 					// initialization
	// 					explicit	reverse_iterator(iterator_type it) {};

	// 					// copy
	// 					template <class Iter>reverse_iterator(const reverse_iterator<Iter>& rev_it) {};

	// 					// base
	// 					iterator_type	base() const {};

	// 					// oprator*
	// 					reference	operator*() const
	// 					{
	// 						return this->iterator[this->pos];
	// 					};

	// 					// operator+
	// 					reverse_iterator	operator+(difference_type n) const
	// 					{
	// 						return this->iterator[this->pos];
	// 					};

	// 					// operator++
	// 					reverse_iterator&	operator++()
	// 					{
	// 						++this->pos;
	// 						return *this;
	// 					};
	// 					reverse_iterator	operator++(int)
	// 					{
	// 						return {&:this->iterator, pos++};
	// 					};
						
	// 					// operator+=
	// 					reverse_iterator&	operator+=(difference_type n) {};

	// 					// operator-
	// 					reverse_iterator	operator-(difference_type n) const {};

	// 					// operator--
	// 					reverse_iterator&	operator--()
	// 					{
	// 						--this->pos;
	// 						return *this;
	// 					};
	// 					reverse_iterator	operator--(int)
	// 					{
	// 						return {&:this->iterator, pos--};
	// 					};

	// 					// operator-=
	// 					reverse_iterator&	operator-=(difference_type n) {};

	// 					// operator->
	// 					pointer	operator->() const {};

	// 					// operator[]
	// 					reference	operator[](difference_type n) const {};
	// 	// Non-member function overloads
	// 		//---- relational operators
	// 		template <class Iterator> bool	operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	// 		{
	// 			return &lhs.data == &rhs.data && lhs.pos == rhs.pos;
	// 		};
	// 		template <class Iterator> bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	// 		{
	// 			return !(lhs == rhs);
	// 		};
	// 		template <class Iterator> bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {};
	// 		template <class Iterator> bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {};
	// 		template <class Iterator> bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {};
	// 		template <class Iterator> bool	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {};
			
	// 		// operator+
	// 		template <class Iterator> reverse_iterator<Iterator>operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {};
			
	// 		// operator-
	// 		template <class Iterator> reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rev_it) {};
	// };
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
			reverse_iterator() : p(iterator()) {};
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