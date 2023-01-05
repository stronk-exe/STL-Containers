/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:44:38 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/04 13:51:20 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include "../utils/pair.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/lexicographical_compare.hpp"
#include "RBtree.hpp"
#include <memory>

namespace ft {

template <
			typename Key,
			typename T,
			typename Compare = std::less<Key>,
			typename Allocator = std::allocator<pair<const Key, T> >
		>
class map
{


	public: // types:
		typedef Key 													key_type;
		typedef T 														mapped_type;
		typedef pair<const key_type, mapped_type>						value_type;
		typedef Compare 												key_compare;
		typedef Allocator 												allocator_type;
		typedef typename allocator_type::size_type						size_type;
		typedef typename allocator_type::difference_type				difference_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;

	private:
		class	value_compare;
		typedef RBtree<value_type, value_compare, Allocator>				RBT;
		typedef typename RBT::Node										Node;
		typedef Node*													Node_ptr;

	public: // iterators
		typedef node_iterator<value_type>								iterator;
		typedef node_iterator<const value_type>							const_iterator;
		typedef ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;

	private:
		key_compare		_Comp;
		allocator_type	_Alloc;
		value_compare	_Value_Comp;
		RBT			rbt;

	public:
		// 23.3.1.1 construct/copy/destroy:
		// initializing tree with value compair that will be responsible of compairing keys of value_type
		// so we don't have to compair key of value type inside the tree to make it general
		explicit map(
					const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type() )
			: _Comp(comp), _Alloc(alloc), _Value_Comp(comp), rbt(_Value_Comp, alloc) {}

		template <class InputIterator>
		map(
			InputIterator first,
			InputIterator last,
			const Compare &comp = Compare(),
			const Allocator &alloc = Allocator() )
			: _Comp(comp), _Alloc(alloc), _Value_Comp(comp), rbt(_Value_Comp, alloc)
		{
			while (first != last)
				rbt.insert(*first++);
		}


		map (const map& x)
		: _Comp(x._Comp), _Alloc(x._Alloc), _Value_Comp(x._Value_Comp), rbt(x.rbt) {}

		map& operator= (const map& x) {
			if (this != &x)
				rbt = x.rbt;
			return *this;
		}

		~map(){};


		void printBT() { rbt.printBT();}
		// iterators:
		iterator begin() { return iterator(rbt.minimum(), rbt.root()); }
		const_iterator begin() const { return const_iterator( iterator(rbt.minimum(), rbt.root()) ); }
		iterator end() { return iterator(rbt.nil(), rbt.root()); }
		const_iterator end() const { return const_iterator( iterator(rbt.nil(), rbt.root()) ); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

		// capacity:
		bool empty() const { return !rbt.size(); }
		size_type size() const { return rbt.size(); }
		size_type max_size() const { return rbt.max_size(); }
		allocator_type get_allocator() const { return _Alloc; }

		// 23.3.1.2 element access:
		T &operator[](const key_type &x)
		{
			value_type v(x, mapped_type());
			Node_ptr ret = rbt.insert(v).first;
			return ret->value.second;
		}

		// modifiers:
		pair<iterator, bool> insert(const value_type &x)
		{
			pair<Node_ptr, bool> ret = rbt.insert(x);

			iterator it(ret.first, rbt.root());
			return ft::make_pair(it, ret.second);
		}

		iterator insert(iterator position, const value_type &x)
		{
			(void)position;
			Node_ptr z = rbt.insert(x).first;
			return iterator(z, rbt.root());
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				rbt.insert(*first);
				first++;
			}
		}

		void erase(iterator position) {
			rbt.deleteNode(position.get_node(), true);
		}

		size_type erase(const key_type &x) {
			value_type tmp(x, mapped_type());
			return rbt.deleteNode(tmp);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last) {
				iterator it(rbt.successor(first.get_node()), rbt.root());
				rbt.deleteNode(first.get_node(), true);
				first = it;
			}
		}

		void swap(map<Key,T,Compare,Allocator> &x) {
			rbt.swap(x.rbt);
			std::swap(_Alloc, x._Alloc);
			std::swap(_Comp, x._Comp);
		}

		void clear() { rbt.clear(); }

		// observers:
		key_compare key_comp() const { return _Comp; }

		value_compare	value_comp() const { return _Value_Comp; }

		// 23.3.1.3 map operations:
		iterator find(const key_type &x)
		{
			value_type tmp(x, mapped_type());
			return iterator(rbt.search(tmp), rbt.root());
		}

		const_iterator find(const key_type &x) const
		{
			value_type tmp(x, mapped_type());
			return const_iterator(rbt.search(tmp), rbt.root());
		}

		size_type count(const key_type &x) const
		{
			value_type tmp(x, mapped_type());
			Node_ptr p = rbt.search(tmp);
			if (p != rbt.nil())
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type &x)
		{
			value_type tmp(x, mapped_type());
			Node_ptr z = rbt.lower_bound(tmp);
			return iterator(z, rbt.root());
		}

		const_iterator lower_bound(const key_type &x) const
		{
			value_type tmp(x, mapped_type());
			Node_ptr z = rbt.lower_bound(tmp);
			return const_iterator( iterator(z, rbt.root()) );
		}
		iterator upper_bound(const key_type &x)
		{
			value_type tmp(x, mapped_type());
			Node_ptr z = rbt.upper_bound(tmp);
			return iterator(z, rbt.root());
		}
		const_iterator upper_bound(const key_type &x) const
		{
			value_type tmp(x, mapped_type());
			Node_ptr z = rbt.upper_bound(tmp);
			return const_iterator( iterator(z, rbt.root()) );
		}

		pair<iterator, iterator> equal_range(const key_type &x)
		{
			iterator it1(lower_bound(x));
			iterator it2(upper_bound(x));
			return ft::make_pair(it1, it2);
		}

		pair<const_iterator, const_iterator> equal_range(const key_type &x) const
		{
			const_iterator it1(lower_bound(x));
			const_iterator it2(upper_bound(x));
			return ft::make_pair(it1, it2);
		}
};

template <class Key, class T, class Compare, class Allocator>
bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y){
	if ( x.size() == y.size() ) {
		return std::equal ( x.begin(), x.end(), y.begin() );
	}
	return false;
}

template <class Key, class T, class Compare, class Allocator>
bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
	return !(x == y);
}

template <class Key, class T, class Compare, class Allocator>
bool operator< (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
	return ft::lexicographical_compare( x.begin(), x.end(), y.begin(), y.end() );
}

template <class Key, class T, class Compare, class Allocator>
bool operator> (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
	return (y < x);
}

template <class Key, class T, class Compare, class Allocator>
bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
	return !(x < y);
}

template <class Key, class T, class Compare, class Allocator>
bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y) {
	return !(y < x);
}

	// // specialized algorithms:
template <class Key, class T, class Compare, class Allocator>
void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y) {
	x.swap(y);
}

		// function object template inside map
	// uses the internal comparison object to generate the appropriate comparison
	// functional class
	template <typename Key, typename T, typename Compare, typename Alloc>
	class map< Key, T, Compare, Alloc>::value_compare
		: public std::binary_function<typename map::value_type, typename map::value_type, bool>
	{
		friend class map;

		protected:
			Compare comp;
			value_compare (Compare c): comp (c) {}
		public:
			typedef bool			result_type;
			typedef	value_type		first_argument_type;
			typedef value_type		second_argument_type;
			bool operator () (const value_type& x, const value_type& y) const{
				return comp (x.first, y.first);
			}
	};

}

// #include <iostream>
// // #include "../utils/exceptions.hpp"
// // #include "../utils/utils.hpp"
// // #include "../utils/Iterator_traits.hpp"
// // #include "../utils/map_Iterators.hpp"
// // #include "../utils/map_utils.hpp"
// // #include "RBiterators.hpp"
// #include "RBtree.hpp"
// // #include "../utils/reverse_iterator.hpp"
// #include <cstddef>

// namespace ft
// {
// 	template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > class map
// 	{
// 		public:
// 			typedef	Key											key_type;
// 			typedef	T											mapped_type;
// 			typedef	ft::pair<key_type, mapped_type>				value_type;
// 			typedef	size_t										size_type;
// 			typedef	ptrdiff_t									difference_type;
// 			typedef	Compare										key_compare;
// 			typedef	Allocator									allocator_type;
// 			typedef typename allocator_type::pointer			pointer;
// 			typedef typename allocator_type::const_pointer		const_pointer;
// 			typedef typename allocator_type::reference			reference;
// 			typedef typename allocator_type::const_reference	const_reference;
// 			// typedef	T&							reference;
// 			// typedef	const T&					const_reference;
// 			// typedef	T*							pointer;
// 			// typedef	const T*					const_pointer;
// 			class value_comp
// 			{
// 				public:
// 					bool operator()( const value_type &a, const value_type &b ) const
// 					{
// 						return (key_compare()(a.first, b.first));
// 					}
// 					value_comp &operator=( const value_comp& )
// 					{
// 						return *this;
// 					}
// 			};
// 			typedef typename ft::RBtree<value_type, value_comp>::iterator				iterator;
// 			typedef typename ft::RBtree<value_type, value_comp>::const_iterator			const_iterator;
// 			typedef typename ft::RBtree<value_type, value_comp>::reverse_iterator		reverse_iterator;
// 			typedef typename ft::RBtree<value_type, value_comp>::const_reverse_iterator	const_reverse_iterator;
// 			// typedef RDtree_reverse_iterator<T>			reverse_iterator;
// 			// typedef RDtree_reverse_iterator<const T>	const_reverse_iterator;


// 		private:
// 			// size_type		capcity;
// 			// T				*m;
// 			// Allocator		_allocator;
// 			// Compare			cmp;
// 			// T				*r;
// 			// T				*l;
// 			// T				first;
// 			// T				second;

// 			allocator_type					_allocator;
// 			key_compare						_key_comp;
// 			value_comp						val_comp;
// 			RBtree<value_type, value_comp>	rbt;
// 			// size_type		len;

// 		public:
// 			// >> Member functions
// 				//----	Constructors
// 					// map() : _allocator(), _key_comp() , val_comp(), rbt()
// 					// {
// 					// 	std::cout << "map default constractor called" << std::endl;
// 					// };
// 					// explicit map( const Compare& comp, const Allocator& alloc = Allocator() ) : _allocator(alloc), _key_comp(comp) , val_comp(value_comp()), rbt(_allocator)
// 					explicit map( const key_compare& comp=key_compare(), const allocator_type& alloc = allocator_type() ) : _allocator(alloc), _key_comp(comp) , val_comp(value_comp()), rbt(_allocator) {};
					
// 					template< class InputIt > map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) : _allocator(alloc), _key_comp(comp), val_comp(value_comp()), rbt(_allocator)
// 					{
// 						insert(first, last);
// 					};
// 					map( const map& other ) : _allocator(other._allocator), _key_comp(other._key_comp), val_comp(other.val_comp), rbt(other.rbt) {};

// 				//----	Destructor
// 					~map() {};

// 				//----	operator=
// 					map& operator=( const map& other )
// 					{
// 						if (this != &other)
// 						{
// 							_allocator = other._allocator;
// 							_key_comp = other._key_comp;
// 							val_comp = other.val_comp;
// 							rbt = other.rbt;
// 						}
// 						// std::cout << "map assignement operator called" << std::endl;
// 						return *this;
// 					};

// 				//----	get_allocator
// 					allocator_type get_allocator() const
// 					{
// 						return _allocator;
// 					};

// 				//----	Element access
// 					//	operator[]
// 						mapped_type& operator[]( const key_type& key )
// 						{
// 							iterator it = find(key);

// 							if (it != end())
// 							{
// 								// std::cout << "Ladies and gentlemans we got him\n";
// 								// std::cout << it._node->data.first << std::endl;
// 								return it._node->data.second;
// 							}
// 							// std::cout << "Not Found\n";
// 							// value_type gg = ft::make_pair(key, mapped_type());
// 							// // std::cout << "wwaww node " << gg.second << std::endl;
// 							// // exit(1);
// 							// rpointer vv = rbt.new_node(gg);
// 							ft::pair<iterator, bool> temp = insert(ft::make_pair(key, mapped_type()));
// 							// ft::pair<iterator, bool> temp = rbt.insert_node(value_type(key, mapped_type()));
// 							return temp.first._node->data.second;

// 							// reference ret = rbt.insert(v).first;
// 							// return ret->data.second;
// 						};

// 				//----	Iterators
// 					//	begin
// 						iterator begin()
// 						{
// 							return rbt.begin();
// 						};
// 						const_iterator begin() const
// 						{
// 							return rbt.begin();
// 						};

// 					//	end
// 						iterator end()
// 						{
// 							return rbt.end();
// 						};
// 						const_iterator end() const
// 						{
// 							return rbt.end();
// 						};

// 					//	rbegin
// 						reverse_iterator rbegin()
// 						{
// 							return rbt.rbegin();
// 						};
// 						const_reverse_iterator rbegin() const
// 						{
// 							return rbt.rbegin();
// 						};

// 					//	rend
// 						reverse_iterator rend()
// 						{
// 							return rbt.rend();
// 						};
// 						const_reverse_iterator rend() const
// 						{
// 							return rbt.rend();
// 						};

// 				//----	Capacity
// 					//	empty
// 						bool empty() const
// 						{
// 							return rbt.empty();
// 						};

// 					//	size
// 						size_type size() const
// 						{
// 							return rbt.size();
// 						};

// 					//	max_size
// 						size_type max_size() const
// 						{
// 							return rbt.max_size();
// 						};

// 				//----	Modifiers
// 					//	clear
// 						void clear()
// 						{
// 							return rbt.clear();
// 						};

// 					//	insert
// 						ft::pair<iterator, bool> insert( const value_type& value )
// 						{
// 							return rbt.insert(value);
// 						};
// 						iterator insert( iterator pos, const value_type& value )
// 						{
// 							return rbt.insert(pos, value);
// 						};
// 						template< class InputIt >void insert( InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type * = NULL )
// 						{
// 							return rbt.insert(first, last);
// 						};

// 					//	erase
// 						void erase( iterator pos )
// 						{
// 							rbt.erase(pos);
// 						};
// 						size_type erase( const Key& key )
// 						{
// 							return rbt.erase(ft::make_pair(key, mapped_type()));
// 						};
// 						void erase( iterator first, iterator last )
// 						{
// 							rbt.erase(first, last);
// 						};

// 					//	swap
// 						void swap( map& other )
// 						{
// 							std::swap(_allocator, other._allocator);
// 							std::swap(_key_comp, other._key_comp);
// 							std::swap(val_comp, other.val_comp);
// 							rbt.swap(other.rbt);
// 						};

// 				//----	Lookup
// 					//	count
// 						size_type count( const Key& key ) const
// 						{
// 							iterator it = find(key);
// 							if (it != end())
// 								return 1;
// 							// std::cout << "thereee\n";
// 							return 0;
// 						};

// 					//	find
// 						iterator find( const Key& key )
// 						{
// 							return rbt.find(ft::make_pair(key, mapped_type()));
// 						};
// 						const_iterator find( const Key& key ) const
// 						{
// 							return rbt.find(ft::make_pair(key, mapped_type()));
// 						};

// 					//	equal_range
// 						ft::pair<iterator,iterator> equal_range( const Key& key )
// 						{
// 							return rbt.equal_range(ft::make_pair(key, mapped_type()));
// 						};
// 						ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
// 						{
// 							return rbt.equal_range(ft::make_pair(key, mapped_type()));
// 						};

// 					//	lower_bound
// 						iterator lower_bound( const Key& key )
// 						{
// 							return rbt.lower_bound(ft::make_pair(key, mapped_type()));
// 						};
// 						const_iterator lower_bound( const Key& key ) const
// 						{
// 							return rbt.lower_bound(ft::make_pair(key, mapped_type()));
// 						};

// 					//	upper_bound
// 						iterator upper_bound( const Key& key )
// 						{
// 							return rbt.upper_bound(ft::make_pair(key, mapped_type()));
// 						};
// 						const_iterator upper_bound( const Key& key ) const
// 						{
// 							return rbt.upper_bound(ft::make_pair(key, mapped_type()));
// 						};

// 				//----	Observers
// 					//	key_comp
// 						key_compare key_comp() const
// 						{
// 							return _key_comp;
// 						};

// 					//	value_comp
// 						map::value_comp value_comp() const
// 						{
// 							return val_comp;
// 						};

// 						void printTree() {
// 							rbt.printRBtree();
// 						}

// 			// >> Non-member functions
// 				//	operator==
// 				//	operator!=
// 				//	operator<
// 				//	operator<=
// 				//	operator>
// 				//	operator>=
// 	};

// 	// >> Non-member functions
// 		//	operator==
// 			template< class Key, class T, class Compare, class Alloc > bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs )
// 			{
// 				if (lhs.size() != rhs.size())
// 					return false;
// 				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
// 			};

// 			//	operator!=
// 				template< class Key, class T, class Compare, class Alloc > bool operator!=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
// 				{
// 					return !(lhs == rhs);
// 				};

// 			//	operator<
// 				template< class Key, class T, class Compare, class Alloc > bool operator<( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
// 				{
// 					return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
// 				};

// 			//	operator<=
// 				template< class Key, class T, class Compare, class Alloc > bool operator<=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
// 				{
// 					return !(rhs < lhs);
// 				};

// 			//	operator>
// 				template< class Key, class T, class Compare, class Alloc > bool operator>( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
// 				{
// 					return rhs < lhs;
// 				};

// 			//	operator>=
// 				template< class Key, class T, class Compare, class Alloc > bool operator>=( const map<Key,T,Compare,Alloc>& lhs, const map<Key,T,Compare,Alloc>& rhs )
// 				{
// 					return !(lhs < rhs);
// 				};
			
// 			//	swap
// 				template< class Key, class T, class Compare, class Alloc > void swap( map<Key,T,Compare,Alloc>& lhs, map<Key,T,Compare,Alloc>& rhs )
// 				{
// 					lhs.swap(rhs);
// 				};
// };

#endif