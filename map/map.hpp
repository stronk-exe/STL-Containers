/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:44:38 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/28 12:36:15 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "../utils/exceptions.hpp"
// #include "../utils/utils.hpp"
// #include "../utils/Iterator_traits.hpp"
// #include "../utils/map_Iterators.hpp"
// #include "../utils/map_utils.hpp"
// #include "RBiterators.hpp"
#include "RBtree.hpp"
#include "../utils/reverse_iterator.hpp"
#include <cstddef>

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > class map
	{
		public:
			typedef	Key											key_type;
			typedef	T											mapped_type;
			typedef	ft::pair<key_type, mapped_type>							value_type;
			typedef	size_t										size_type;
			typedef	ptrdiff_t									difference_type;
			typedef	Compare										key_compare;
			typedef	Allocator									allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			// typedef	T&							reference;
			// typedef	const T&					const_reference;
			// typedef	T*							pointer;
			// typedef	const T*					const_pointer;
			class value_comp
			{
				public:
					bool operator()( const value_type &a, const value_type &b ) const
					{
						return (key_compare()(a.first, b.first));
					}
					value_comp &operator=( const value_comp& )
					{
						return *this;
					}
			};
			typedef typename ft::RBtree<value_type, value_comp>::iterator				iterator;
			typedef typename ft::RBtree<value_type, value_comp>::const_iterator			const_iterator;
			typedef typename ft::RBtree<value_type, value_comp>::reverse_iterator		reverse_iterator;
			typedef typename ft::RBtree<value_type, value_comp>::const_reverse_iterator	const_reverse_iterator;
			// typedef RDtree_reverse_iterator<T>			reverse_iterator;
			// typedef RDtree_reverse_iterator<const T>	const_reverse_iterator;


		private:
			// size_type		capcity;
			// T				*m;
			// Allocator		_allocator;
			// Compare			cmp;
			// T				*r;
			// T				*l;
			// T				first;
			// T				second;

			allocator_type					_allocator;
			key_compare						_key_comp;
			value_comp						val_comp;
			RBtree<value_type, value_comp>	rbt;
			// size_type		len;

		public:
			// >> Member functions
				//----	Constructors
					// map() : _allocator(), _key_comp() , val_comp(), rbt()
					// {
					// 	std::cout << "map default constractor called" << std::endl;
					// };
					// explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : _allocator(alloc), _key_comp(comp) , val_comp(value_comp()), rbt(_allocator)
					explicit map( const key_compare& comp=key_compare(), const allocator_type& alloc = allocator_type() ) : _allocator(alloc), _key_comp(comp) , val_comp(value_comp()), rbt(_allocator) {};
					
					template< class InputIt > map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : _allocator(alloc), _key_comp(comp), val_comp(value_comp()), rbt(_allocator)
					{
						// int i=0;
						// // while (first != last)
						// for (iterator it=first; it != last; ++it)
						// {
						// 	// v[i] = val;
						// 	// std::cout << v[i] << std::endl;
						// 	i++;
						// }
						// capcity = i;
						// len = i;
						// m = _allocator.allocate(i);
						// // (void)comp;
						// // cmp = comp;
						// std::cout << "map range constractor called!" << std::endl;
						// size_type i=0,count=0;
						// InputIt temp1=first, temp2=last;
					
						// while (temp1 != temp2)
						// {
						// 	count+=1;
						// 	temp1++;
						// }
						// len = count;
						// capcity = len;
						// m = _allocator.allocate(capcity);
						// while (first != last)
						// {
						// 	_allocator.construct(m+i, *first);
						// 	first++;
						// 	i++;
						// }
						// while (first != last)
						// {
						// 	rbt.insert(*first);
						// 	*first++;
						// }
						insert(first, last);
					};
					map( const map& other ) : _allocator(other._allocator), _key_comp(other._key_comp), val_comp(other.val_comp), rbt(other.rbt) {};

				//----	Destructor
					~map() {};

				//----	operator=
					map& operator=( const map& other )
					{
						if (*this != other)
						{
							_allocator = other._allocator;
							_key_comp = other._key_comp;
							val_comp = other.val_comp;
							rbt = other.rbt;
						}
						std::cout << "map assignement operator called" << std::endl;
						return *this;
					};

				//----	get_allocator
					allocator_type get_allocator() const
					{
						return _allocator;
					};

				//----	Element access
					//	operator[]
						T& operator[]( const Key& key )
						{
							// if (key<0 || key>len)
							// 	throw invalidIndex();
							// return m[key];
							// if (key_exists(key))
							// {
							// 	for (iterator it=begin(); it != end(); it++)
							// 		if (it.key == key)
							// 			return it.val;
							// }
							// insert(key);
							// return m[len].val;
							// iterator it;
							
							// it = find(key);
							// if (it != end())
							// 	insert(ft::make_pair(key, mapped_type()));
							// it = find(key);
							// return it.second;
							iterator it = rbt.find(ft::make_pair(key, mapped_type()));

							if (it == end())
							{
								// ft::pair<iterator, bool> n = insert(ft::make_pair(key, mapped_type()));
								// return n.first._node->data.second;
								insert(ft::make_pair(key, mapped_type()));
								iterator gg = find(key);
								return gg._node->data.second;
								
							}
							return it._node->data.second;
						};

				//----	Iterators
					//	begin
						iterator begin()
						{
							// return m;
							// size_type h=5;
							// for (size_type i=0; i<h; i++)
							// {
							// 	m = m.l;
							// }
							// return iterator(m);
							// return iterator(min_element(root));
							return rbt.begin();
						};
						const_iterator begin() const
						{
							// return m;
							// size_type h=5;
							// for (size_type i=0; i<h; i++)
							// {
							// 	m = m.l;
							// }
							// return const_iterator(m);
							// return const_iterator(min_element(root));
							return rbt.begin();
						};

					//	end
						iterator end()
						{
							// return m+len;
							// size_type h=5;
							// for (size_type i=0; i<h; i++)
							// {
							// 	m = m.r;
							// }
							// return iterator(m);
							// return iterator(nullptr);
							return rbt.end();
						};
						const_iterator end() const
						{
							// return m+len;
							// size_type h=5;
							// for (size_type i=0; i<h; i++)
							// {
							// 	m = m.r;
							// }
							// return const_iterator(m);
							// return const_iterator(nullptr);
							return rbt.end();
						};

					//	rbegin
						reverse_iterator rbegin()
						{
							// return m;
							// size_type h=5;
							// for (size_type i=0; i<h; i++)
							// {
							// 	m = m.r;
							// }
							// return reverse_iterator(m);
							// return reverse_iterator(nullptr);
							return rbt.rbegin();
						};
						const_reverse_iterator rbegin() const
						{
							// return m;
							// size_type h=5;
							// for (size_type i=0; i<h; i++)
							// {
							// 	m = m.r;
							// }
							// return const_reverse_iterator(m);
							// return const_reverse_iterator(nullptr);
							return rbt.rbegin();
						};

					//	rend
						reverse_iterator rend()
						{
							// return m+len;
							// size_type h=5;
							// for (size_type i=0; i<h; i++)
							// {
							// 	m = m.l;
							// }
							// return reverse_iterator(m);
							// return reverse_iterator(min_element(root));
							return rbt.rend();
						};
						const_reverse_iterator rend() const
						{
							// return m+len;
							// size_type h=5;
							// for (size_type i=0; i<h; i++)
							// {
							// 	m = m.l;
							// }
							// return const_reverse_iterator(m);
							// return const_reverse_iterator(min_element(root));
							return rbt.rend();
						};

				//----	Capacity
					//	empty
						bool empty() const
						{
							// if (!len || !rbt->root)
							// 	return true;
							// return false;
							// return !rbt.size();
							return rbt.empty();
						};

					//	size
						size_type size() const
						{
							// return len;
							return rbt.size();
						};

					//	max_size
						size_type max_size() const
						{
							// return capcity-len;
							return rbt.max_size();
						};

				//----	Modifiers
					//	clear
						void clear()
						{
							// _allocator.deallocate(m);
							// capcity = 0;
							// len = 0;
							// for (size_type i=0; i < capcity; i++)
							// 	_allocator.destroy(m+i);
							// len = 0;
							return rbt.clear();
						};

					//	insert
						ft::pair<iterator, bool> insert( const value_type& value )
						{
							// bool temp = rbt.insert(value);
							// if (temp)
							// 	len++;
							// iterator it = find(temp.first, rbt.root());
							return rbt.insert(value);
						};
						iterator insert( iterator pos, const value_type& value )
						{
							// t_node	temp = node;
							// size_type	i=0;
							// while (it)
							// for (iterator it = m.begin(); it != m.end(); it++)
							// {
							// 	if (it.val > m)
							// 	{
							// 		// go rigth
							// 		it = it.r;
							// 	}
							// 	else
							// 	{
							// 		// go left
							// 		it = it.l;
							// 	}
							// 	// break;
							// 	i++;
							// }
							// _allocator(m+i, value);
							// (void)pos;
							// rbt.insert(value);
							// len++;
							// return find(value.first);
							return rbt.insert(pos, value);
						};
						template< class InputIt >void insert( InputIt first, InputIt last )
						{
							return rbt.insert(first, last);
						};

					//	erase
						iterator erase( iterator pos )
						{
							return rbt.erase(pos);
						};
						iterator erase( iterator first, iterator last )
						{
							return rbt.erase(first, last);
						};
						size_type erase( const Key& key )
						{
							return rbt.erase(ft::make_pair(key, mapped_type()));
						};

					//	swap
						void swap( map& other )
						{
							// int	temp_len = len;
							// T	temp_m = m;
							// len = other.len;
							// m = other.m;
							// other.len = temp_len;
							// other.m = temp_m;
							std::swap(_allocator, other._allocator);
							std::swap(_key_comp, other._key_comp);
							std::swap(val_comp, other.val_comp);
							rbt.swap(other.rbt);
						};

				//----	Lookup
					//	count
						size_type count( const Key& key ) const
						{
							// int	count;
							// for (size_type i=0; i<len; i++)
							// 	if (m[i] == key)
							// 		count+=1;
							// return count;
							iterator it = find(key);
							if (it != end())
								return 1;
							return 0;
						};

					//	find
						iterator find( const Key& key )
						{
							// T temp(key, mapped_type());
							// return iterator(rbt.search(temp), rbt.root());
							return rbt.find(ft::make_pair(key, mapped_type()));
						};
						const_iterator find( const Key& key ) const
						{
							return rbt.find(ft::make_pair(key, mapped_type()));
						};

					//	equal_range
						ft::pair<iterator,iterator> equal_range( const Key& key )
						{
							return rbt.equal_range(key);
						};
						ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
						{
							return rbt.equal_range(key);
						};

					//	lower_bound
						iterator lower_bound( const Key& key )
						{
							return rbt.lower_bound(key);
						};
						const_iterator lower_bound( const Key& key ) const
						{
							return rbt.lower_bound(key);
						};

					//	upper_bound
						iterator upper_bound( const Key& key )
						{
							return rbt.upper_bound(key);
						};
						const_iterator upper_bound( const Key& key ) const
						{
							return rbt.upper_bound(key);
						};

				//----	Observers
					//	key_comp
						key_compare key_comp() const
						{
							return key_comp;
						};

					//	value_comp
						map::value_comp value_comp() const
						{
							return val_comp;
						};

			// >> Non-member functions
				//	operator==
				//	operator!=
				//	operator<
				//	operator<=
				//	operator>
				//	operator>=
	};

	// >> Non-member functions
		//	operator==
			template< class Key, class T, class Compare, class Alloc > bool operator==( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
			{
				if (lhs.size() != rhs.size())
					return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			};

			//	operator!=
				template< class Key, class T, class Compare, class Alloc > bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
					return !(lhs == rhs);
				};

			//	operator<
				template< class Key, class T, class Compare, class Alloc > bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
				};

			//	operator<=
				template< class Key, class T, class Compare, class Alloc > bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
					return !(rhs < lhs);
				};

			//	operator>
				template< class Key, class T, class Compare, class Alloc > bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
					return rhs < lhs;
				};

			//	operator>=
				template< class Key, class T, class Compare, class Alloc > bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
				{
					return !(lhs < rhs);
				};
};

#endif