#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "Iterator_traits.hpp"
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
			typedef ft::random_access_iterator_tag	iterator_category;

			// typedef	T														iter_type;
			// typedef	typename	ft::random_access_iterator_traits<T>::value_type			value_type;
			// typedef	typename	ft::random_access_iterator_traits<T>::difference_type		difference_type;
			// typedef	typename	ft::random_access_iterator_traits<T>::reference			reference;
			// typedef	typename	ft::random_access_iterator_traits<T>::pointer				pointer;
			// typedef	typename	ft::random_access_iterator_traits<T>::random_access_iterator_category	random_access_iterator_category;
		private:
			T	*p;

		public:
			random_access_iterator() : p(NULL) {};
			random_access_iterator( const random_access_iterator &other ) : p(other.p) {};
			explicit random_access_iterator( pointer _p ) : p(_p) {};
			~random_access_iterator() {};

			random_access_iterator& operator=( const random_access_iterator &other )
			{
				if (*this != other)
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
				++p;
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
				--p;
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
			template< class T > random_access_iterator<T> operator+( typename random_access_iterator<T>::difference_type d, const random_access_iterator<T> &it )
			{
				return d + it;
			};
			template< class T > random_access_iterator<T> operator-( typename random_access_iterator<T>::difference_type d, const random_access_iterator<T> &it )
			{
				return d - it;
			};
		/*	template< class X, class Y > bool operator==( const random_access_iterator<X>& it1, const random_access_iterator<Y>& it2 )
			{
				return it1.base() == it2.base();
			};

		//	operator!=
			template< class X, class Y > bool operator!=( const random_access_iterator<X>& it1, const random_access_iterator<Y>& it2 )
			{
				return it1.base() != it2.base();
			};

		//	operator<
			template< class X, class Y > bool operator<( const random_access_iterator<X>& it1, const random_access_iterator<Y>& it2 )
			{
				return it1.base() < it2.base();
			};

		//	operator<=
			template< class X, class Y > bool operator<=( const random_access_iterator<X>& it1, const random_access_iterator<Y>& it2 )
			{
				return it1.base() <= it2.base();
			};

		//	operator>
			template< class X, class Y > bool operator>( const random_access_iterator<X>& it1, const random_access_iterator<Y>& it2 )
			{
				return it1.base() > it2.base();
			};

		//	operator>=
			template< class X, class Y > bool operator>=( const random_access_iterator<X>& it1, const random_access_iterator<Y>& it2 )
			{
				return it1.base() >= it2.base();
			};

		//	operator +
			template< class X > random_access_iterator<X> operator+( typename random_access_iterator<X>::difference_type n, const random_access_iterator<X>& it1 )
			{
				return it1.base() + n;
			};
		//	operator -
			template< class X, class Y > typename random_access_iterator<X>::difference_type operator-( const random_access_iterator<X>& it1, const random_access_iterator<Y>& it2 )
			{
				return it1.base() - it2.base();
			};*/
}

#endif