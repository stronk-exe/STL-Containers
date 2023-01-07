/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:23:00 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/07 23:46:18 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <cstddef>
#include <string>
#include "../utils/exceptions.hpp"
#include "../utils/random_access_iterator.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/pair.hpp"
#include "../utils/equal.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/lexicographical_compare.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> > class vector
	{
		public:
			typedef T											value_type;
			typedef Allocator									allocator_type;
			typedef	typename	allocator_type::pointer			pointer;
			typedef	typename	allocator_type::const_pointer	const_pointer;
			typedef	typename	allocator_type::reference		reference;
			typedef	typename	allocator_type::const_reference	const_reference;
			typedef	ptrdiff_t									difference_type;
			typedef size_t										size_type;
			typedef ft::random_access_iterator<value_type>								iterator;
			typedef ft::random_access_iterator<const value_type>						const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		private:
			allocator_type	_allocator;
			pointer			v;
			size_type		capcity;
			size_type		len;

		public:
			// >> Member functions
				//----	Constructors
					explicit vector( const Allocator& alloc = Allocator() ) : _allocator(alloc), v(NULL), capcity(0), len(0) {};

					explicit vector( size_type count, const T& value = T(), const allocator_type& alloc = Allocator()) : _allocator(alloc), v(NULL), capcity(0), len(0)
					{
						reserve(count);
						for (size_type i=0; i < count; i++)
							_allocator.construct(v+i, value);
						len = count;
					};

					template< class InputIt >
					vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type = InputIt()) :  _allocator(alloc)
					{
						size_type i=0,count=0;
						InputIt temp1=first, temp2=last;
					
						while (temp1 != temp2)
						{
							count++;
							temp1++;
						}
						capcity = count;
						v = _allocator.allocate(capcity);
						while (first != last)
						{
							_allocator.construct(v+i, *first);
							first++;
							i++;
						}
						len = count;
					};
					
					template<class InputIt> int ft_range( InputIt first, InputIt last, std::random_access_iterator_tag)
					{
						return first - last;
					}
					template<class InputIt> int ft_range( InputIt first, InputIt last, std::bidirectional_iterator_tag)
					{
						return std::distance(first, last);
					}
					template<class InputIt> int ft_range( InputIt , InputIt , std::input_iterator_tag)
					{
						return -1;
					}

					vector( const vector& other ) :  _allocator(other._allocator), v(NULL), capcity(other.capcity), len(other.len)
					{
						v = _allocator.allocate(capcity);
						for (size_type i=0; i < len; i++)
							_allocator.construct(v+i, other.v[i]);
					};

				//----	Destructor
					~vector()
					{
						clear();
						if (v)
							_allocator.deallocate(v, capcity);
					};

				//----	operator=
					vector& operator=( const vector& other )
					{
						if (this != &other)
						{
							clear();
							if (capcity < other.len)
								reserve(other.len);
							if (v)
								_allocator.deallocate(v, capcity);
							len = other.len;
							v = _allocator.allocate(capcity);
							for (size_type i=0; i < len; i++)
								_allocator.construct(v+i, other.v[i]);
						}
						return *this;
					};

				//---	assign
					void assign( size_type count, const T& value )
					{
						if (count > capcity)
							reserve(count);
						clear();
						for (size_type i=0; i < count; i++)
							_allocator.construct(v+i, value);
						len = count;
					};
					template< class InputIt > void assign( InputIt first, InputIt last, typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type = InputIt())
					{
						size_type count = last - first;
						if (count > capcity)
							reserve(count);
						clear();
						for (size_type i=0; i < count; i++)
						{
							_allocator.construct(v+i, *first);
							first++;
						}
						len = count;
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
							if (pos >= len)
								throw std::out_of_range(std::string("ft::vector: std::out_of_range exception called"));
							return v[pos];
						};
						const_reference at( size_type pos ) const
						{
							if (pos >= len)
								throw std::out_of_range(std::string("ft::vector: std::out_of_range exception called"));
							return v[pos];
						};

					// operator[]
						reference operator[]( size_type pos )
						{
							return v[pos];
						};
						const_reference operator[]( size_type pos ) const
						{
							return v[pos];
						};

					// front
						reference front()
						{
							return v[0];
						};
						const_reference front() const
						{
							return v[0];
						};

					// back
						reference back()
						{
							return v[len-1];
						};
						const_reference back() const
						{
							return v[len-1];
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
							return const_iterator(v+len);
						};

					// rbegin
						reverse_iterator rbegin()
						{
							return reverse_iterator(v+len);
						};
						const_reverse_iterator rbegin() const
						{
							return const_reverse_iterator(v+len);
						};

					// rend
						reverse_iterator rend()
						{
							return reverse_iterator(v);
						};
						const_reverse_iterator rend() const
						{
							return const_reverse_iterator(v);
						};

				//----	Capacity
					// empty
						bool empty() const
						{
							return !len ? 1 : 0;
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

							if (new_cap > _allocator.max_size())
								throw std::length_error("bad_alloc");
							if (new_cap > capcity)
							{
								temp_v = _allocator.allocate(new_cap);
								for (size_type i=0; i < len; i++)
									_allocator.construct(temp_v+i, v[i]);
								temp_len = len;
								clear();
								if (v)
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
							for (size_type i=0; i < len; i++)
								_allocator.destroy(v+i);
							len = 0;
						};

					// insert
						iterator insert( iterator pos, const T& value )
						{
							size_type index = pos - begin();

							push_back(value);
							value_type temp = v[len-1];
							for (size_type i=len-1; i > index; i--)
								v[i] = v[i-1];
							v[index] = temp;
							return iterator(v+index);
						};
						void insert( iterator pos, size_type count, const T& value )
						{
							difference_type index = pos - begin();
							
							if (!len)
								reserve(count);
							else if (len+count > capcity)
							{
								if (count > len)
									reserve(len+count);
								else
									reserve(capcity*2);
							}
							for (difference_type i=len-1; i>=index; --i)
								_allocator.construct(v+(i+count), v[i]);
							for (size_type i=0; i<count; ++i)
								_allocator.construct(v+index++, value);
							len += count;
						}
						template< class InputIt > void insert( const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt())
						{
							difference_type index = pos - begin();
							size_type count = last-first;
								
							if (!len)
								reserve(count);
							else if (len+count > capcity)
							{
								if (count > len)
									reserve(len+count);
								else
									reserve(capcity*2);
							}
							for (difference_type i=len-1; i>=index; --i)
								_allocator.construct(v+(i+count), v[i]);
							for (size_type i=0; i<count; ++i)
								_allocator.construct(v+index++, *first);
							len += count;
						};

					// erase
						iterator erase( iterator pos )
						{
							size_type index = pos - begin();

							_allocator.destroy(v+index);
							_allocator.construct(v+index, v[index+1]);
							for (size_type i=index+1; i < len-1; i++)
								v[i] = v[i+1];
							_allocator.destroy(v+(len-1));
							len--;
							return pos;
						};
					
						iterator erase( iterator first, iterator last )
						{
							size_type range = last - first, start = first - begin();

							for (size_type i=0; (i < range && i < len); i++)
							{
								_allocator.destroy(v+start+i);
								if (start+range+i < len)
									_allocator.construct(v+i+start, v[i+start+range]);
							}
							for (size_type i=start+range; i < len; i++)
							{
								_allocator.destroy(v+i);
								if (range+i < len)
									_allocator.construct(v+i, v[i+range]);
							}
							len-=range;
							return iterator(v+start);
						};

					// push_back
						void push_back( const T& value )
						{
							if (len == capcity)
							{
								if (!len)
									reserve(1);
								else
									reserve(len*2);
							}
							_allocator.construct(v+len, value);
							len++;
						};

					// pop_back
						void pop_back()
						{
							len--;
							_allocator.destroy(v+len);
						};

					// resize
						void resize( size_type count, T value = T() )
						{
							if (count < len)
							{
								for (size_type i=count; i < len; i++)
									_allocator.destroy(v+i);
								len = count;
							}
							else
							{
								if (count > capcity*2)
									reserve(count);
								else
								{
									if (!len)
										reserve(1);
									else
										reserve(len*2);
								}
								for (size_type i=len; i < count; i++)
									_allocator.construct(v+i, value);
								len = count;
							}
						};

					// swap
						void swap( vector& other )
						{
							std::swap(_allocator, other._allocator);
							std::swap(v, other.v);
							std::swap(capcity, other.capcity);
							std::swap(len, other.len);
						};

	};

	// >> Non-member functions
		//	operator==
			template< class T, class Alloc > bool operator==( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
			{
				if (lhs.size() != rhs.size())
					return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			};

			//	operator!=
				template< class T, class Alloc > bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
				{
					return !(lhs == rhs);
				};

			//	operator<
				template< class T, class Alloc > bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs )
				{
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
				};

			//	operator<=
				template< class T, class Y, class Alloc > bool operator<=( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
				{
					return !(rhs < lhs);
				};

			//	operator>
				template< class T, class Y, class Alloc > bool operator>( const ft::vector<T,Alloc>& lhs, const ft::vector<Y,Alloc>& rhs )
				{
					return rhs < lhs;
				};

			//	operator>=
				template< class T, class Alloc > bool operator>=( const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs )
				{
					return !(lhs < rhs);
				};

			//	swap
				template <class T , class Allocator> void swap( vector<T, Allocator> &it1, vector<T, Allocator> &it2 )
				{
					it1.swap(it2);
				}
}

#endif