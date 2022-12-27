/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:23:00 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/27 13:31:16 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "../utils/exceptions.hpp"
// #include "../utils/Iterator_traits.hpp"
// #include "../utils/vector_Iterators.hpp"
// #include "../utils/reverse_iterator.hpp"
#include "../utils/random_access_iterator.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/utils.hpp"
#include <cstddef>

	#include <string>
#include <sstream>
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
			typedef ft::random_access_iterator<T>								iterator;
			typedef ft::random_access_iterator<const T>						const_iterator;
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
						// v = _allocator.allocate(count);
						for (size_type i=0; i < count; i++)
							_allocator.construct(v+i, value);
						len = count;
					};

					template< class InputIt >
					vector( InputIt first, InputIt last, const Allocator& alloc = Allocator(), typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type = InputIt()) :  _allocator(alloc), v(NULL)
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
						v = _allocator.allocate(capcity);
						while (first != last)
						{
							_allocator.construct(v+i, *first);
							first++;
							i++;
						}
					};

					vector( const vector& other ) :  _allocator(other._allocator), v(NULL), capcity(other.capcity), len(other.len)
					{
						v = _allocator.allocate(capcity);
						for (size_type i=0; i < len; i++)
							_allocator.construct(v+i, other.v[i]);
					};

				//----	Destructor
					~vector()
					{
						_allocator.deallocate(v, capcity);
						// this->clear();
					};

				//----	operator=
					vector& operator=( const vector& other )
					{
						if (*this != other)
						{
							clear();
							if (capcity < other.len)
								reserve(other.len);
							len = other.len;
							if (v)
								_allocator.deallocate(v, len);
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
						// {
						// 	capcity = count;
						// 	v = _allocator.allocate(capcity);
						// }
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

						// // int i=0;
						// // for (iterator it=first; it != last; ++it)
						// // 	v[i++] = it;
						// size_type i=0;
						// InputIt tempf, templ;

						// tempf = first;
						// templ = last;
						// // std::cout << "holla\n";
						// // while (tempf != templ)
						// // {
						// // 	i++;
						// // }
						// i = templ-tempf;
						// clear();
						// if (i > capcity)
						// {
						// 	capcity = i;
						// 	v = _allocator.allocate(capcity);
						// }
						// len = capcity;
						// i=0;
						// // pointer tmp= _allocator.allocate(capcity);
						// while (first != last)
						// {
						// 	// std::cout << "whota"<< i<<"\n";
						// 	_allocator.construct(v+i, *first);
						// 	first++;
						// 	i++;
						// }
						// // v = tmp;

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
								// throw invalidIndex();
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

							// if (capcity < len+1)
							// 	throw std::length_error("bad_alloc");
							if (len == 0)
								reserve(1);
							if (len + 1 > capcity)
								reserve(len*2);
							for (size_type i=len; i > index; i--)
							{
								_allocator.construct(v+i, v[i-1]);
								// _allocator.destroy(v+i);
							}
							_allocator.construct(v+index, value);
							len++;
							return iterator(v+index);

							// size_type index;
							// value_type temp;

							// index = &(*pos) - v;
							// if (!capcity)
							// {
							// 	// capcity+=1;
							// 	// len+=1;
							// 	reserve(1);
							// }
							// else if (len+1 > capcity)
							// 	capcity *= 2;
							// std::cout << v+len << "holla\n";
							// for (size_type i=len; i > index; i--)
							// {
							// 	temp = v[i];
							// 	v[i] = v[i-1];
							// 	v[i-1] = temp;
							// }
						};
						// void insert( iterator pos, size_type count, const T& value )
						// {
						// 	size_type index = pos - begin();

						// 	if (len == 0)
						// 		reserve(count);
						// 	else if (len + count > capcity)
						// 	{
						// 		if (count > len)
						// 			reserve(len + count);
						// 		else
						// 			reserve(capcity*2);
						// 	}
						// 	for (size_type i=len; i > index; --i)
						// 	{
						// 	// std::cout << "LMACHAKIL!!\n";
						// 		_allocator.construct(v+i+index, v[i]);
						// 		// _allocator.destroy(v+i);

						// 	}
						// 	for (size_type i=0; i < count; ++i)
						// 		_allocator.construct(v+ index++, value);
						// 	len+=count;

						// 	// size_type index;
						// 	// value_type temp;

						// 	// index = &(*pos) - v;
						// 	// if (len+count > capcity)
						// 	// 	capcity *= 2;
						// 	// for (size_type i=0; i < count; i++)
						// 	// {
						// 	// 	_allocator.construct(v+len, value);
						// 	// 	len += 1;
						// 	// }
						// 	// for (size_type x=0; x < count; x++)
						// 	// {
						// 	// 	for (size_type i=len-count+x; i > index; i--)
						// 	// 	{
						// 	// 		temp = v[i];
						// 	// 		v[i] = v[i-1];
						// 	// 		v[i-1] = temp;
						// 	// 	}
						// 	// 	index+=1;
						// 	// }
						// 	// return iterator(v+index);
						// };
						void insert( iterator pos, size_type count, const T& value )
						{
								size_type index = pos - begin();

								if (len+count <= capcity)
								{
									for (size_type i = len - 1; i >= index; --i) {
											if (i + count < len)
												v[i + count] = v[i];
											else
												_allocator.construct(v + i + count, v[i]);
										}
										for (size_type i = index; i < index + count; i++) {
											if (i < len)
												v[i] = value;
											else
												_allocator.construct(v + i, value);
										}
									len+=count;
								}
								else
								{
									// if (len == 0)
									// 	reserve(count);
									size_type new_cap;
									if (count > len)
										new_cap = len+count;
									else
										new_cap = len*2;
									pointer temp = _allocator.allocate(new_cap);
									for (size_type i=0; i<index; i++)
										_allocator.construct(temp+i, v[i]);
									for (size_type i=index; i < (index+count); i++)
										_allocator.construct(temp+i, value);
									for (size_type i=(index+count); i< (len+count); i++)
										_allocator.construct(temp+i, v[i-count]);
									size_type temp_len = len;
									clear();
									_allocator.deallocate(v, capcity);
									capcity = new_cap;
									v = temp;
									len = temp_len+count;
								}
								
						}
						// void insert(iterator position, size_type n, const_reference x) {
						// 	size_type pos = position - begin();
						// 	if (pos > len)
						// 		return ;
						// 	if (len + n <= capcity) {
						// 		for (size_type i = len - 1; i >= pos; --i) {
						// 			if (i + n < len)
						// 				v[i + n] = v[i];
						// 			else
						// 				_allocator.construct(v + i + n, v[i]);
						// 		}
						// 		for (size_type i = pos; i < pos + n; i++) {
						// 			if (i < len)
						// 				v[i] = x;
						// 			else
						// 				_allocator.construct(v + i, x);
						// 		}
						// 		len += n;
						// 	}
						// 	else if (len + n > capcity) {
						// 		size_type newCap = n > len ? len + n : len * 2;
						// 		pointer tmp = _allocator.allocate(newCap);
						// 		for (size_type i = 0; i < pos; i++)
						// 			_allocator.construct(tmp + i, v[i]);
						// 		for (size_type i = pos; i < pos + n; i++)
						// 			_allocator.construct(tmp + i, x);
						// 		for (size_type i = pos + n; i < len + n ; i ++)
						// 			_allocator.construct(tmp + i, v[i - n]);
						// 		size_type sz = len;
						// 		clear();
						// 		_allocator.deallocate(v, capcity);
						// 		capcity = newCap;
						// 		v = tmp;
						// 		len = sz + n;
						// 	}
						// }
						/*constexpr iterator  insert( const_iterator pos, size_type count, const T& value )
						{
							
						};
					*/	template< class InputIt > void insert( const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type = InputIt())
						{
							size_type index = pos - begin(), count = last-first;

								if (len+count < capcity)
								{
									for (size_type i = len - 1; i >= index; --i) {
											if (i + count < len)
												v[i + count] = v[i];
											else
												_allocator.construct(v + i + count, v[i]);
										}
										for (size_type i = index; i < index + count; i++) {
											if (i < len)
												v[i] = *first++;
											else
												_allocator.construct(v + i, *first++);
										}
									len+=count;
								}
								else
								{
									// if (len == 0)
									// 	reserve(count);
									size_type new_cap;
									if (count > len)
										new_cap = len+count;
									else
										new_cap = len*2;
									pointer temp = _allocator.allocate(new_cap);
									for (size_type i=0; i<index; i++)
										_allocator.construct(temp+i, v[i]);
									for (size_type i=index; i < (index+count); i++)
										_allocator.construct(temp+i, *first++);
									for (size_type i=(index+count); i< (len+count); i++)
										_allocator.construct(temp+i, v[i-count]);
									size_type temp_len = len;
									clear();
									_allocator.deallocate(v, capcity);
									capcity = new_cap;
									v = temp;
									len = temp_len+count;
								}

							// size_type index = pos - begin(), range = last - first;

							// if (len+range > capcity)
							// {
							// 	if (!len)
							// 		reserve(1);
							// 	else if (len+range > len*2)
							// 		reserve(len*2);
							// 	else
							// 		reserve(len+range);
							// }
							// for (size_type i=len; i > index; i--)
							// {
							// 	_allocator.construct(v+i+range, v[i]);
							// 	_allocator.destroy(v+i);

							// }
							// for (size_type i=0; i < range; i++)
							// {
							// // std::cout << "LMACHAKIL!!!\n";
							// 	_allocator.construct(v+(i+index), *first);
							// 	first++;
							// }
							// len+=range;



							// if (len + count > capcity)
							// 	reserve(capcity + count);

							// size_type index, count;
							// value_type temp;
							// InputIt tempf = first, templ = last;

							// count = templ-tempf;
							// index = &(*pos) - v;
							// if (len+count > capcity)
							// 	capcity *= 2;
							// for (size_type i=0; i < count; i++)
							// {
							// 	_allocator.construct(v+len, *first++);
							// 	len += 1;
							// }
							// for (size_type x=0; x < count; x++)
							// {
							// 	for (size_type i=len-count+x; i > index; i--)
							// 	{
							// 		temp = v[i];
							// 		v[i] = v[i-1];
							// 		v[i-1] = temp;
							// 	}
							// 	index+=1;
							// }
						};

					// erase
						iterator erase( iterator pos )
						{
							size_type index = pos - begin();

							// index = &(*pos) - v;
							_allocator.destroy(v+index);
							for (size_type i=index; i < len; i++)
							{
								_allocator.construct(v+i, v[index+1]);
								_allocator.destroy(v+i+1);

							}
							len--;
							return iterator(v+index);
							// for (size_type i=index; i<len-1; i++)
							// 	v[i] = v[i+1];
						};
						iterator erase( iterator first, iterator last )
						{
							size_type range = last - first, start = first - begin();

							for (; *first != *last; *first++)
								_allocator.destroy(&(*first));
							for (size_type i=start; i < len; i++)
							{
								_allocator.construct(v+start, v[start+range]);
								_allocator.destroy(v+start+range);
							}
							len-=range;
							return iterator(v+range);

							// index = &(*pos) - v;

							// size_type index, count, i;

							// index = &(*first) - v;
							// count = &(*last) - &(*first);
							// for (i=index; i<count; i++)
							// 	_allocator.destroy(v+i);
							// for (size_type x=index; x<len; x++)
							// {
							// 	v[x] = v[x+count];
							// 	i+=1;
							// }
							// len-=count;
							// return iterator(v+index);
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
							// if (!capcity)
							// 	reserve(1);
							// else if (len+1 > capcity)
							// 	reserve(capcity * 2);
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
							// else if (count <= capcity)
							// {
							// 	for (size_type i=len; i<count; i++)
							// 		_allocator.construct(v+i, value);
							// 	len += count;
							// }
							// else
							// {
							// 	// if (count > capcity*2)
							// 		capcity = count;
							// 	// else
							// 	// 	capcity *= 2;
							// 	pointer temp;
							// 	temp = _allocator.allocate(capcity);
							// 	for (size_type i=0; i<len; i++)
							// 		_allocator.construct(temp+i, v[i]);
							// 	for (size_type i=len; i<count; i++)
							// 		_allocator.construct(temp+i, value);
							// 	for (size_type i=0; i<len; i++)
							// 		_allocator.destroy(v+i);
							// 	v = temp;
							// 	len = count;
							// }
						};

					// swap
						void swap( vector& other )
						{
							// int temp_len = len;
							// T *temp_v = v;
							// len = other.len;
							// v = other.v;
							// other.len = temp_len;
							// other.v = temp_v;

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