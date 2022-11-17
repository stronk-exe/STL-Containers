/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:23:00 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/17 13:38:01 by ael-asri         ###   ########.fr       */
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
					vector() : capcity(0), len(0) {};
					explicit vector( const Allocator& alloc ) : capcity(0), len(0), v(nullptr), _allocator(alloc)
					{
						v = _allocator.allocate(len);
						std::cout << "vector default constractor called!" << std::endl;
					};

					explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : capcity(count), len(count), _allocator(alloc)
					{
						v = _allocator.allocate(len);
						for (size_type i=0; i<len; i++)
							v[i] = value;
						std::cout << "vector fill constractor called!" << std::endl;
					};

					template< class iterator > vector( iterator first, iterator last, const Allocator& alloc = Allocator() ) : _allocator(alloc)
					{
						int i=0;
						for (iterator it=first; it != last; ++it)
							i++;
						capcity = i;
						len = i;
						v = _allocator.allocate(i);
						std::cout << "vector range constractor called!" << std::endl;
					};

					vector( const vector& other ) : capcity(other.capcity), len(other.len), v(other.v)
					{
						std::cout << "vector copy constractor called!" << std::endl;
					};

				//----	Destructor
					~vector()
					{
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
						// v = _allocator.allocate(count);
						for (unsigned int i=0; i<count; i++)
						{
							v[i] = value;
							// std::cout << v[i] << std::endl;
							// i++;
						}
						capcity = count;
						len = count;
					};
					template< class InputIt > void assign( InputIt first, InputIt last )
					{
						int i=0;
						for (iterator it=first; it != last; ++it)
						{
							v[i] = it;
							// std::cout << v[i] << std::endl;
							i++;
						}
						capcity = i;
						len = i;
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
							return v;
						};
						const_iterator begin() const
						{
							return v;
						};

					// end
						iterator end()
						{
							return v+len;
						};
						const_iterator end() const
						{
							return v+len;
						};

					// rbegin
						reverse_iterator rbegin()
						{
							return v;
						};
						const_reverse_iterator rbegin() const
						{
							return v;
						};

					// rend
						reverse_iterator rend()
						{
							return v+len;
						};
						const_reverse_iterator rend() const
						{
							return v+len;
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
							// typedef ft::vector<int>::iterator ci;
							// ci from (v->begin());
							// typedef const_iterator ci=v->begin();
							
							unsigned int i=0,x=0;
							value_type temp = _allocator.alloc(len+1);
							value_type val = _allocator.alloc(sizeof(T));
							val = value;
							// while (first != last)
							// while (ci != pos)
							iterator it;
							for (it=v->begin(); it != pos; ++it)
							{
								temp[x] = v[i];
								// ci++;
								i++;
							}
							temp[x] = val;
							x++;
							while (i<len)
							{
								temp[x] = v[i];
								i++;
							}
							return it;
						};
						iterator insert( const_iterator pos, size_type count, const T& value )
						{
							unsigned int i=0,x=0;
							T temp = _allocator.alloc(len+1);
							T val = _allocator.alloc(sizeof(T));
							val = value;
							// while (first != last)
							// while (ci != pos)
							(void)count;
							iterator it;
							for (it=v->begin(); it != pos; ++it)
							{
								temp[x] = v[i];
								// ci++;
								i++;
							}
							temp[x] = val;
							x++;
							while (i<len)
							{
								temp[x] = v[i];
								i++;
							}
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
							// this->insert(val, data.end());
							len+=1;
							T *temp = v;
							v = _allocator.allocate(len); // resize() here!
							v = temp;
							v[len-1] = value;
							// for (size_type i=0; i<len; i++)
							// 	std::cout << "hlwa's data " << v[i] << std::endl;
						};

					// pop_back
						void pop_back()
						{
							// for (size_type i=0; i<len; i++)
							// 	std::cout << "hlwa before popin " << this->v[i] << std::endl;
							_allocator.destroy(v+(len-1));
							len-=1;
							// for (size_type i=0; i<len; i++)
							// 	std::cout << "hlwa after popin " << v[i] << std::endl;
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

			// >> Non-member functions
				//	operator==
				//	operator!=
				//	operator<
				//	operator<=
				//	operator>
				//	operator>=
	};
}

#endif