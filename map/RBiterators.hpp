/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBiterators.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:47 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/04 16:21:43 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBITERATORS_HPP
#define RBITERATORS_HPP


#include <iterator>
#include "../utils/enable_if.hpp"

namespace ft {

// node struct
template <typename T>
struct node
{
	T value;
	node *p;	 // parent
	node *left;	 // child
	node *right; // child;
	bool color;
	node( const T &x = T() ) : value(x) {
		p = NULL;
		left = NULL;
		right = NULL;
		color = BLACK;
	}
};

template <typename T>
class node_iterator: public std::iterator <std::bidirectional_iterator_tag,T>
{

	typedef ft::node<T>*				node_ptr;
	typedef ft::node<const T>*			const_node_ptr;

	public:

		typedef T																						value_type;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::reference			reference;
		typedef const T&																				const_reference;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::pointer			pointer;
		typedef const T*																				const_pointer;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
		typedef typename std::iterator<std::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;

	private:
		node_ptr		_node;
		node_ptr const *_root;
		node_ptr		_nil;

	public:

		node_iterator (const node_ptr node = 0x0, const node_ptr *root = 0x0): _root(root) {
			_node = node;
			if ( _root)
				_nil  = *_root ? (*_root)->p : 0x00;
			else _nil = 0x0;
		}


		node_iterator (const node_iterator& x)
		: _node (x._node), _root(x._root), _nil (x._nil) {}

		~node_iterator(){}

		// convertion from non const iter to const iter
		template <class U>
		node_iterator(const node_iterator<U>& other,
		typename ft::enable_if<std::is_convertible<U, T>::value>::type* = 0)
		{
			_node = (const_node_ptr)other.base();
			_root = (const_node_ptr *)other.get_root();
			_nil = (const_node_ptr)other.get_nil();
		}

		node_iterator& operator = (const node_iterator& x) {
			if (this != &x) {
				_node = x._node;
				_root = x._root;
				_nil = x._nil;
			}
			return *this;
		}

		bool operator == (const node_iterator& iter) const { return _node == iter._node; }

		bool operator != (const node_iterator& iter) const { return _node != iter._node; }

		reference		operator * () { return _node->value; }
		const_reference	operator * () const { return _node->value; }

		pointer			operator-> () { return &(_node->value); };
		const_pointer	operator-> () const { return &(_node->value); };

		node_iterator& operator ++ () {
			_node = next(_node);
			return (*this);
		}

		node_iterator operator ++ (int) {
			node_iterator tmp (*this);
			_node = next(_node);
			return tmp;
		}

		node_iterator& operator -- () {
			if (_node == _nil)
				_node = maximum(*_root);
			else
				_node = prev (_node);
			return (*this);
		}

		node_iterator operator -- (int) {
			node_iterator tmp (*this);
			if (_node == _nil)
				_node = maximum(*_root);
			else
				_node = prev (_node);
			return (tmp);
		}

		node_ptr	get_node () const { return _node; }
		node_ptr const *get_root () const { return _root; }
		node_ptr	get_nil () const { return _nil; }
		node_ptr	base() const { return _node; }
		private:

			node_ptr minimum(node_ptr t)
			{
				if (t == _nil)
					return t;
				node_ptr tmp = t;
				while (tmp->left != _nil)
					tmp = tmp->left;
				return tmp;
			}

			node_ptr maximum(node_ptr t)
			{
				if (t == _nil)
					return t;
				node_ptr tmp = t;
				while (tmp->right != _nil)
					tmp = tmp->right;
				return tmp;
			}

			node_ptr next(node_ptr x)
			{
				if (x == _nil)
					return x;
				if (x->right != _nil)
					return minimum(x->right);
				node_ptr y = x->p;
				while (y != _nil && x == y->right)
				{
					x = y;
					y = y->p;
				}
				return y;
			}

			node_ptr prev(node_ptr x)
			{
				if (x == _nil)
					return x;
				if (x->left != _nil)
					return maximum(x->left);
				node_ptr y = x->p;
				while (y != _nil && x != y->right)
				{
					x = y;
					y = y->p;
				}
				return y;
			}

};

}

// #include "RBnode.hpp"
// #include <iostream>
// #include "../utils/Iterator_traits.hpp"

// namespace ft
// {
//     template<typename T> class RBiterator
//     {
//         public:
//             typedef T*                                      n_pointer;
//             typedef typename T::value_type             value_type;
//             typedef value_type*                                      pointer;
//             typedef value_type const*                                const_pointer;
//             typedef value_type&                                      reference;
//             typedef value_type const&                                const_reference;

//             typedef typename std::ptrdiff_t                 difference_type;
//             typedef typename std::bidirectional_iterator_tag iterator_category;
        
//         // private:
//             n_pointer _node;
//             n_pointer it_nil;
//             n_pointer it_root;
        
//         public:
//             RBiterator() : _node(NULL), it_nil(NULL), it_root(NULL) {};
//             RBiterator( n_pointer root, n_pointer n, n_pointer nil) : _node(n), it_nil(nil), it_root(root) {};
//             RBiterator( const RBiterator &rbtit ) : _node(rbtit._node), it_nil(rbtit.it_nil), it_root(rbtit.it_root) {};
//             ~RBiterator() {};

//             RBiterator& operator=( const RBiterator& other )
//             {
//                 if (this != &other)
//                 {
//                     _node = other._node;
//                     it_nil = other.it_nil;
//                     it_root = other.it_root;
//                 }
//                 return *this;
//             }

//             operator RBiterator<T const>() const
//             {
//                 return RBiterator<T const>(it_root, _node, it_nil);
//             }

//             bool operator==( const RBiterator& other ) const
//             {
//                 return _node == other._node;
//             }
//             bool operator!=( const RBiterator& other ) const
//             {
//                 return _node != other._node;
//             }

//             reference	operator*()
//             {
//                 return _node->data;
//             };
//             const_reference	operator*() const
//             {
//                 return _node->data;
//             };
//             pointer	operator->()
//             {
//                 return &_node->data;
//             };
//             const_pointer	operator->() const
//             {
//                 return &_node->data;
//             };

//             RBiterator& operator++()
//             {
//                 // If the current node has a non-null right child,
//                 // 	Take a step down to the right
//                 // 	Then run down to the left as far as possible
//                 // If the current node has a null right child,
//                 // 	Move up the tree until we have moved over a left child link
//                 // if (!_node)
//                 //     return *this;
//                 // if (_node->right != NULL)
//                 //     _node = min_element(_node->right);
//                 // else
//                 // {
//                 //     pointer parent = _node;
//                 //     while (parent != NULL && n == parent->right)
//                 //     {
//                 //         _node = parent;
//                 //         parent = parent->parent;
//                 //     }
//                 //     _node = parent;
//                 // }
//                 // return *this;
//                 // std::cout << "mal mok mnlkhr\n";
//                 if (_node != it_nil)
//                 {
//                     if (_node->right != it_nil)
//                         _node = min_element(_node->right);
//                     else
//                     {
//                         while (_node->parent != it_nil && _node == _node->parent->right)
//                             _node = _node->parent;
//                         _node = _node->parent;
//                     }
//                 }
//                 return *this;
//             };

//             RBiterator operator++( int )
//             {
//                 // std::cout << "mal mok mnlkhr\n";
//                 RBiterator _rbtit(*this);

//                 ++(*this);
//                 return _rbtit;
//             };

//             RBiterator& operator--()
//             {
//                 // if (!node)
//                 //     return *this;
//                 // if (node->left != NULL)
//                     // node = min_element(node->right);
//                 // else
//                 // {
//                 //     node *parent = n;
//                 //     while (parent != NULL && n == parent->right)
//                 //     {
//                 //         node = parent;
//                 //         parent = parent->parent;
//                 //     }
//                 //     node = parent;
//                 // }
//                 if (_node != it_nil)
//                 {
//                     if (_node->left != it_nil)
//                         _node = max_element(_node->left);
//                     else
//                     {
//                         while (_node->parent != it_nil && _node == _node->parent->left)
//                             _node = _node->parent;
//                         _node = _node->parent;
//                     }
//                 }
//                 else
//                     _node = max_element(it_root);
//                 return *this;
//             };

//             RBiterator operator--( int )
//             {
//                 RBiterator _rbtit(*this);

//                 --(*this);
//                 return _rbtit;
//             };

//             n_pointer min_element( n_pointer n )
//             {
//                 if (n->left == it_nil)
//                     return n;
//                 return min_element(n->left);
//             };
//             n_pointer max_element( n_pointer n )
//             {
//                 if (n->right == it_nil)
//                     return n;
//                 return max_element(n->right);
//             };
//     };
// }

#endif