/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:23:00 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/22 16:54:44 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "../exceptions.hpp"
#include "Iterator_traits.hpp"
#include "Iterators.hpp"
// #include "reverse_iterator.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> > class vector
	{
		public:
			typedef T							value_type;
			typedef T*							pointer;
			typedef T&							reference;
			typedef const T*					const_pointer;
			typedef const T&					const_reference;
			typedef size_t						size_type;
			typedef ptrdiff_t					difference_type;
			typedef Allocator					allocator_type;
			typedef Iterator<T>					iterator;
			typedef Iterator<const T >			const_iterator;
			typedef Reverse_iterator<T>			reverse_iterator;
			typedef Reverse_iterator<const T>	const_reverse_iterator;

		private:
			size_type		capcity;
			size_type		len;
			T				*v;
			Allocator		_allocator;

		public:
			// >> Member functions
				//----	Constructors
					vector() : capcity(0), len(0)
					{
						v = _allocator.allocate(len);
					};

					explicit vector( const Allocator& alloc ) : capcity(0), len(0), _allocator(alloc)
					{
						v = _allocator.allocate(len);
						// std::cout << "vector default constractor called!" << std::endl;
					};

					explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : capcity(count), len(count), _allocator(alloc)
					{
						v = _allocator.allocate(len);
						for (size_type i=0; i<len; i++)
							v[i] = value;
						// std::cout << "vector fill constractor called!" << std::endl;
					};

					// template< class iterator > vector( iterator first, iterator last, const Allocator& alloc = Allocator() ) : _allocator(alloc)
				/*	template< class InputIt > vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) : _allocator(alloc)
					{
						int i=0;
						for (iterator it=first; it != last; ++it)
							i++;
						capcity = i;
						len = i;
						v = _allocator.allocate(i);
						std::cout << "vector range constractor called!" << std::endl;
					};*/

					vector( const vector& other ) : capcity(other.capcity), len(other.len), v(other.v)
					{
						// std::cout << "vector copy constractor called!" << std::endl;
					};

				//----	Destructor
					~vector()
					{
						this->clear();
						std::cout << "vector Deconstractor called!" << std::endl;
					};

				//----	operator=
					vector& operator=( const vector& other )
					{
						capcity = other.capcity;
						len = other.len;
						v = other.v;
						return *this;
					};

				//---	assign
					void assign( size_type count, const T& value )
					{
						unsigned int	i;
						for (i=0; i<count; i++)
							v[i] = value;
					};
					template< class iterator > void assign( iterator first, iterator last )
					{
						int i=0;
						for (iterator it=first; it != last; ++it)
							v[i++] = it;
					};

				//----	get_allocator
					allocator_type get_allocator() const
					{
						return _allocator;
					};

				//----	Element access
					// at
						reference at( size_type pos )
						{
							if (pos < 0 || pos > len)
								throw invalidIndex();
							return *(v+pos);
						};
						const_reference at( size_type pos ) const
						{
							if (pos < 0 || pos > len)
								throw invalidIndex();
							return *(v+pos);
						};

					// operator[]
						reference operator[]( size_type pos )
						{
							if (pos < 0 || pos > len)
								throw invalidIndex();
							return v[pos];
						};
						const_reference operator[]( size_type pos ) const
						{
							if (pos < 0 || pos > len)
								throw invalidIndex();
							return v[pos];
						};

					// front
						reference front()
						{
							return *v;
						};
						const_reference front() const
						{
							return *v;
						};

					// back
						reference back()
						{
							return *(v+(len-1));
						};
						const_reference back() const
						{
							return *(v+(len-1));
						};

					// data
						T* data()
						{
							return v;
						};
						const T* data() const
						{
							return v;
						};

				//----	Iterators
					// begin
						iterator begin()
						{
							return iterator(v);
						};
						const_iterator begin() const
						{
							return const_iterator(v);
						};

					// end
						iterator end()
						{
							return iterator(v+len);
						};
						const_iterator end() const
						{
							return const_iterator( v+len);
						};

					// rbegin
						reverse_iterator rbegin()
						{
							return reverse_iterator(v);
						};
						const_reverse_iterator rbegin() const
						{
							return const_reverse_iterator(v);
						};

					// rend
						reverse_iterator rend()
						{
							return reverse_iterator(v+len);
						};
						const_reverse_iterator rend() const
						{
							return const_reverse_iterator( v+len);
						};

				//----	Capacity
					// empty
						bool empty() const
						{
							if (!len)
								return true;
							return false;
						};

					// size
						size_type size() const
						{
							return len;
						};

					// max_size
						size_type max_size() const
						{
							return capcity-len;
						};

					// reserve
						void reserve( size_type new_cap )
						{
							if (new_cap > capcity)
							{
								capcity = new_cap;
								this->_allocator(capcity);
							}
						};

					// capacity
						size_type capacity() const
						{
							return capcity;
						};

				//----	Modifiers
					// clear
						void clear()
						{
							_allocator.destroy(v);
							capcity = 0;
							len = 0;
						};

					// insert
						iterator insert( const_iterator pos, const T& value )
						{
							unsigned int i=0,x=0;
							value_type *temp;
							
							temp = _allocator.allocate(len+1);
							iterator it;
							if (pos == this->end())
								pos--;
							for (it=this->begin(); const_iterator(it) != pos; it++)
							{
								temp[x] = v[i];
								x++;
								i++;
							}
							temp[x] = value;
							x++;
							while (i<=len)
							{
								temp[x] = v[i];
								x++;
								i++;
							}
							this->v=temp;
							len+=1;
							return it;
						};
						iterator insert( const_iterator pos, size_type count, const T& value )
						{
							unsigned int i=0,x=0;
							value_type *temp;
							
							temp = _allocator.allocate(len+count);
							iterator it;
							if (pos == this->end())
								pos--;
							for (it=this->begin(); const_iterator(it) != pos; it++)
							{
								temp[x] = v[i];
								x++;
								i++;
							}
							while (count>0)
							{
								temp[x] = value;
								x++;
								count--;
							}
							while (i<len)
							{
								temp[x] = v[i];
								// std::cout << temp[x] << " mal ngliz b3d zmtat iran\n";
								x++;
								i++;
							}
							this->v=temp;
							len=x;
							// std::cout << len << " mal ngliz 9bl zmtat iran\n";
							// if (!count)
							// 	return pos;
							return it;
						};
						/*constexpr iterator  insert( const_iterator pos, size_type count, const T& value )
						{
							
						};
						template< class InputIt > iterator insert( const_iterator pos, InputIt first, InputIt last )
						{
							
						};*/

					// erase
						iterator erase( iterator pos )
						{
							unsigned int i=0;
							// while (first != last)
							iterator it;
							for (it=v->begin(); it != pos; ++it)
							{
								// v[i] = val;
								// std::cout << v[i] << std::endl;
								i++;
							}
							_allocator.deallocate(v[i]);
							return it;
						};
						iterator erase( iterator first, iterator last )
						{
							// unsigned int i=0;
							iterator it;
							for (it=first; it!=last; ++it)
							{
								_allocator.deallocate(*this);
							}
							return it;
						};

					// push_back
						void push_back( const T& value )
						{
							len+=1;
							T *temp = v;
							v = _allocator.allocate(len); // resize() here!
							v = temp;
							v[len-1] = value;
						};

					// pop_back
						void pop_back()
						{
							_allocator.destroy(v+(len-1));
							len-=1;
						};

					// resize
						void resize( size_type count, T value = T() )
						{
							if (count < len)
								for (size_type i=count; i<len; i++)
									_allocator.destroy(v+i);
							else
								for (size_type i=len; i < count; i++)
									push_back(value);
							len = count;
							// capcity = n;
						};

					// swap
						void swap( vector& other )
						{
							int temp_len = len;
							T *temp_v = v;
							len = other.len;
							v = other.v;
							other.len = temp_len;
							other.v = temp_v;
						};

	};

	// >> Non-member functions
		//	operator==
			template< class T, class Y, class Alloc > bool operator==( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
			{
				return lhs->len == rhs->len;
			};

			//	operator!=
				template< class T, class Y, class Alloc > bool operator!=( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
				{
					return lhs->len != rhs->len;
				};

			//	operator<
				template< class T, class Y, class Alloc > bool operator<( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
				{
					return lhs->len < rhs->len;
				};

			//	operator<=
				template< class T, class Y, class Alloc > bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
				{
					return lhs->len <= rhs->len;
				};

			//	operator>
				template< class T, class Y, class Alloc > bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
				{
					return lhs->len > rhs->len;
				};

			//	operator>=
				template< class T, class Y, class Alloc > bool operator>=( const std::vector<T,Alloc>& lhs, const std::vector<Y,Alloc>& rhs )
				{
					return lhs->len >= rhs->len;
				};
}

#endif