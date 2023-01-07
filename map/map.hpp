/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:44:38 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/07 23:42:22 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include "../utils/RBtree.hpp"

namespace ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > class map
	{
		public:
			typedef	Key											key_type;
			typedef	T											mapped_type;
			typedef	ft::pair<key_type, mapped_type>				value_type;
			typedef	size_t										size_type;
			typedef	ptrdiff_t									difference_type;
			typedef	Compare										key_compare;
			typedef	Allocator									allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
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

		private:
			allocator_type					_allocator;
			key_compare						_key_comp;
			value_comp						val_comp;
			RBtree<value_type, value_comp>	rbt;

		public:
			// >> Member functions
				//----	Constructors
					explicit map( const key_compare& comp=key_compare(), const allocator_type& alloc = allocator_type() ) : _allocator(alloc), _key_comp(comp) , val_comp(value_comp()), rbt(_allocator) {};
					
					template< class InputIt > map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : _allocator(alloc), _key_comp(comp), val_comp(value_comp()), rbt(_allocator)
					{
						insert(first, last);
					};
					map( const map& other ) : _allocator(other._allocator), _key_comp(other._key_comp), val_comp(other.val_comp), rbt(other.rbt) {};

				//----	Destructor
					~map() {};

				//----	operator=
					map& operator=( const map& other )
					{
						if (this != &other)
						{
							_allocator = other._allocator;
							_key_comp = other._key_comp;
							val_comp = other.val_comp;
							rbt = other.rbt;
						}
						return *this;
					};

				//----	get_allocator
					allocator_type get_allocator() const
					{
						return _allocator;
					};

				//----	Element access
					//	operator[]
						mapped_type& operator[]( const key_type& key )
						{
							iterator it = find(key);

							if (it != end())
								return it->second;
							ft::pair<iterator, bool> temp = insert(ft::make_pair(key, mapped_type()));
							return temp.first.get_itnode()->data.second;
						};

				//----	Iterators
					//	begin
						iterator begin()
						{
							return rbt.begin();
						};
						const_iterator begin() const
						{
							return rbt.begin();
						};

					//	end
						iterator end()
						{
							return rbt.end();
						};
						const_iterator end() const
						{
							return rbt.end();
						};

					//	rbegin
						reverse_iterator rbegin()
						{
							return rbt.rbegin();
						};
						const_reverse_iterator rbegin() const
						{
							return rbt.rbegin();
						};

					//	rend
						reverse_iterator rend()
						{
							return rbt.rend();
						};
						const_reverse_iterator rend() const
						{
							return rbt.rend();
						};

				//----	Capacity
					//	empty
						bool empty() const
						{
							return rbt.empty();
						};

					//	size
						size_type size() const
						{
							return rbt.size();
						};

					//	max_size
						size_type max_size() const
						{
							return rbt.max_size();
						};

				//----	Modifiers
					//	clear
						void clear()
						{
							return rbt.clear();
						};

					//	insert
						ft::pair<iterator, bool> insert( const value_type& value )
						{
							return rbt.insert(value);
						};
						iterator insert( iterator pos, const value_type& value )
						{
							return rbt.insert(pos, value);
						};
						template< class InputIt >void insert( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = NULL )
						{
							return rbt.insert(first, last);
						};

					//	erase
						void erase( iterator pos)
						{
							rbt.erase(pos);
						};
						size_type erase( const Key& key )
						{
							return rbt.erase(ft::make_pair(key, mapped_type()));
						};
						void erase( iterator first, iterator last )
						{
							rbt.erase(first, last);
						};

					//	swap
						void swap( map& other )
						{
							std::swap(_allocator, other._allocator);
							std::swap(_key_comp, other._key_comp);
							std::swap(val_comp, other.val_comp);
							rbt.swap(other.rbt);
						};

				//----	Lookup
					//	count
						size_type count( const Key& key ) const
						{
							iterator it = find(key);
							if (it != end())
								return 1;
							return 0;
						};

					//	find
						iterator find( const Key& key )
						{
							return rbt.find(ft::make_pair(key, mapped_type()));
						};
						const_iterator find( const Key& key ) const
						{
							return rbt.find(ft::make_pair(key, mapped_type()));
						};

					//	equal_range
						ft::pair<iterator,iterator> equal_range( const Key& key )
						{
							return rbt.equal_range(ft::make_pair(key, mapped_type()));
						};
						ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
						{
							return rbt.equal_range(ft::make_pair(key, mapped_type()));
						};

					//	lower_bound
						iterator lower_bound( const Key& key )
						{
							return rbt.lower_bound(ft::make_pair(key, mapped_type()));
						};
						const_iterator lower_bound( const Key& key ) const
						{
							return rbt.lower_bound(ft::make_pair(key, mapped_type()));
						};

					//	upper_bound
						iterator upper_bound( const Key& key )
						{
							return rbt.upper_bound(ft::make_pair(key, mapped_type()));
						};
						const_iterator upper_bound( const Key& key ) const
						{
							return rbt.upper_bound(ft::make_pair(key, mapped_type()));
						};

				//----	Observers
					//	key_comp
						key_compare key_comp() const
						{
							return _key_comp;
						};

					//	value_comp
						map::value_comp value_comp() const
						{
							return val_comp;
						};

					private:
						void printTree() {
							rbt.printRBtree();
						}
	};

	// >> Non-member functions
		//	operator==
			template< class Key, class T, class Compare, class Alloc > bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
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
			
			//	swap
				template< class Key, class T, class Compare, class Alloc > void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )
				{
					lhs.swap(rhs);
				};
};

#endif