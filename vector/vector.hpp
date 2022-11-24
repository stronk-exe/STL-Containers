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
#include "../utils/exceptions.hpp"
#include "../utils/Iterator_traits.hpp"
#include "../utils/Iterators.hpp"
#include "../utils/utils.hpp"
#include <cstddef>
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
			allocator_type	_allocator;

		public:
			// >> Member functions
				//----	Constructors
					vector() : capcity(0), len(0), v(NULL)
					{
						// v = _allocator.allocate(len);
					};

					explicit vector( const Allocator& alloc ) : capcity(0), len(0), _allocator(alloc), v(NULL)
					{
						// v = _allocator.allocate(len);
						// std::cout << "vector default constractor called!" << std::endl;
					};

					explicit vector( size_type count, const T& value = T(), const Allocator& alloc = Allocator()) : capcity(count), len(count), v(NULL), _allocator(alloc)
					{
						v = _allocator.allocate(len);
						for (size_type i=0; i<len; i++)
							_allocator.construct(v+i, value);
							// v[i] = value;
						// std::cout << "vector fill constractor called!" << std::endl;
					};

					// template< class iterator > vector( iterator first, iterator last, const Allocator& alloc = Allocator() ) : _allocator(alloc)
				/*	template< class InputIt >
					vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!is_integeal<InputIt>::value, InputIt>::type = InputIt()) : capcity(0), len(0), _allocator(alloc), v(NULL)
					{
						size_type i=0,count=0;
						InputIt temp1=first, temp2=last;
						while (temp1 != temp2)
						{
							count+=1;
							temp1++;
						}
						len = count;
						capcity = len;
						v = alloc.allocate(capcity);
						while (first != last)
						{
							alloc.construct(v+i, *first);
							first++;
							i++;
						}
						std::cout << "vector range constractor called!" << std::endl;
					};*/

					vector( const vector& other ) : capcity(other.capcity), len(other.len), v(NULL), _allocator(other._allocator)
					{
						// std::cout << "vector copy constractor called!" << std::endl;
						// *this = other;
						int i=0;
						v = _allocator.allocate(len);
						while (i<len)
						{
							_allocator.construct(v+i, other.v[i]);
							i+=1;
						}
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
						if (*this != other)
						{
							for (size_type i=0; i<len; i++)
								_allocator.destroy(v+i);
							if (capcity)
								_allocator.deallocate(v, capcity);
							capcity = other.capcity;
							len = other.len;
							v = other.v;
							_allocator = other._allocator;
							for (size_type i=0; i<len; i++)
								_allocator.construct(v+i, other.v[i]);
						}
						return *this;
					};

				//---	assign
				/*	void assign( size_type count, const T& value )
					{
						// unsigned int	i;
						// for (i=0; i<count; i++)
						// 	v[i] = value;
						if (!capcity())
						{
							v = _allocator.allocate(count);
							capcity = count;
							len = count;

						}
						else if (count > capcity)
						{
							_allocator.deallocate(v, capcity);
							capcity = count;
							len = count;
							v = _allocator.allocate(capcity);
						}
						for (size_type i=0; i < count; i++)
							_allocator.construct(v+i, value);
					};
					template< class iterator > void assign( iterator first, iterator last )
					{
						int i=0;
						for (iterator it=first; it != last; ++it)
							v[i++] = it;
					};*/

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
							return _allocator.max_size();
						};

					// reserve
						void reserve( size_type new_cap )
						{
							size_type	temp_len;
							pointer		temp_v;
						
							if (new_cap > capcity)
							{
								temp_v = _allocator.allocate(new_cap);
								for (size_type i=0; i < len; i++)
									_allocator.construct(temp_v+i, v[i]);
								temp_len = len;
								clear();
								_allocator.deallocate(v, capcity);
								len = temp_len;
								v = temp_v;
								capcity = new_cap;

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
							for (size_type i=0; i < capcity; i++)
								_allocator.destroy(v+i);
							len = 0;
						};

					// insert
					/*	iterator insert( const_iterator pos, const T& value )
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
						};*/
						/*constexpr iterator  insert( const_iterator pos, size_type count, const T& value )
						{
							
						};
						template< class InputIt > iterator insert( const_iterator pos, InputIt first, InputIt last )
						{
							
						};*/

					// erase
					/*	iterator erase( iterator pos )
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
						};*/

					// push_back
						void push_back( const T& value )
						{
							if (!capcity)
								reserve(1);
							else if (len+1 > capcity)
								reserve(capcity * 2);
							_allocator.construct(v+len, value);
							len+=1;
						};

					// pop_back
						void pop_back()
						{
							_allocator.destroy(v+(len-1));
							len-=1;
						};

					// resize
					/*	void resize( size_type count, T value = T() )
						{
							if (count < len)
								for (size_type i=count; i<len; i++)
									_allocator.destroy(v+i);
							else
								for (size_type i=len; i < count; i++)
									push_back(value);
							len = count;
							// capcity = n;
						};*/

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
			template< class T, class Alloc > bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
			{
				// return lhs.size() == rhs.size();
				if (lhs.size() != rhs.size())
					return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			};

			//	operator!=
				template< class T, class Alloc > bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
				{
					// return lhs.size() != rhs.size();
					return !(lhs == rhs);
				};

			//	operator<
				template< class T, class Alloc > bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
				{
					// return lhs.size() < rhs.size();
					// return lhs < rhs;
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
				};

			//	operator<=
				template< class T, class Y, class Alloc > bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
				{
					// return lhs.size() <= rhs.size();
					return !(rhs < lhs);
				};

			//	operator>
				template< class T, class Y, class Alloc > bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
				{
					// return lhs.size() > rhs.size();
					return rhs < lhs;
				};

			//	operator>=
				template< class T, class Alloc > bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
				{
					// return lhs.size() >= rhs.size();
					return !(lhs < rhs);
				};
}

#endif