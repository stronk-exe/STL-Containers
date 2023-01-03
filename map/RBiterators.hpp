/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBiterators.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:47 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/01 20:52:50 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBITERATORS_HPP
#define RBITERATORS_HPP

#include "RBnode.hpp"
#include <iostream>
#include "../utils/Iterator_traits.hpp"

namespace ft
{
    template<typename T> class RBiterator
    {
        public:
            typedef T*                                      n_pointer;
            typedef typename T::value_type const            value_type;
            typedef value_type*                                      pointer;
            typedef value_type const*                                const_pointer;
            typedef value_type&                                      reference;
            typedef value_type const&                                const_reference;

            typedef typename std::ptrdiff_t                 difference_type;
            typedef typename std::bidirectional_iterator_tag iterator_category;
        
            n_pointer _node;
        // private:
            n_pointer it_nil;
            n_pointer it_root;
        
        public:
            RBiterator() : _node(NULL), it_nil(NULL), it_root(NULL) {};
            RBiterator( n_pointer root, n_pointer n,  n_pointer nil) : _node(n), it_nil(nil), it_root(root) {};
            RBiterator( const RBiterator &rbtit ) : _node(rbtit._node), it_nil(rbtit.it_nil), it_root(rbtit.it_root) {};
            ~RBiterator() {};

            RBiterator& operator=( const RBiterator& other )
            {
                if (this != &other)
                {
                    _node = other._node;
                    it_nil = other.it_nil;
                    it_root = other.it_root;
                }
                return *this;
            }

            operator RBiterator<T const>() const
            {
                return RBiterator<T const>(it_root, _node, it_nil);
            }

            bool operator==( const RBiterator& other ) const
            {
                return _node == other._node;
            }
            bool operator!=( const RBiterator& other ) const
            {
                return _node != other._node;
            }

            reference	operator*()
            {
                return _node->data;
            };
            const_reference	operator*() const
            {
                return _node->data;
            };
            pointer	operator->()
            {
                return &_node->data;
            };
            const_pointer	operator->() const
            {
                return &_node->data;
            };

            RBiterator& operator++()
            {
                // If the current node has a non-null right child,
                // 	Take a step down to the right
                // 	Then run down to the left as far as possible
                // If the current node has a null right child,
                // 	Move up the tree until we have moved over a left child link
                // if (!_node)
                //     return *this;
                // if (_node->right != NULL)
                //     _node = min_element(_node->right);
                // else
                // {
                //     pointer parent = _node;
                //     while (parent != NULL && n == parent->right)
                //     {
                //         _node = parent;
                //         parent = parent->parent;
                //     }
                //     _node = parent;
                // }
                // return *this;
                // std::cout << "mal mok mnlkhr\n";
                if (_node != it_nil)
                {
                    if (_node->right != it_nil)
                        _node = min_element(_node->right);
                    else
                    {
                        while (_node->parent != it_nil && _node == _node->parent->right)
                            _node = _node->parent;
                        _node = _node->parent;
                    }
                }
                return *this;
            };

            RBiterator operator++( int )
            {
                // std::cout << "mal mok mnlkhr\n";
                RBiterator _rbtit(*this);

                ++(*this);
                return _rbtit;
            };

            RBiterator& operator--()
            {
                // if (!node)
                //     return *this;
                // if (node->left != NULL)
                    // node = min_element(node->right);
                // else
                // {
                //     node *parent = n;
                //     while (parent != NULL && n == parent->right)
                //     {
                //         node = parent;
                //         parent = parent->parent;
                //     }
                //     node = parent;
                // }
                if (_node != it_nil)
                {
                    if (_node->left != it_nil)
                        _node = max_element(_node->left);
                    else
                    {
                        while (_node->parent != it_nil && _node == _node->parent->left)
                            _node = _node->parent;
                        _node = _node->parent;
                    }
                }
                else
                    _node = max_element(it_root);
                return *this;
            };

            RBiterator operator--( int )
            {
                RBiterator _rbtit(*this);

                --(*this);
                return _rbtit;
            };

            n_pointer min_element( n_pointer n )
            {
                if (n->left == it_nil)
                    return n;
                return min_element(n->left);
            };
            n_pointer max_element( n_pointer n )
            {
                if (n->right == it_nil)
                    return n;
                return max_element(n->right);
            };
    };

//     template <class T>
// class RBiterator {
//  public:
// 	typedef T*			node_pointer;

// 	/*
// 		this is some serious magic (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧
// 		use the value_type of T which is the node,
// 		instead of rb_node<T> we only get the T of the node.
// 	*/
// 	typedef typename T::value_type const value_type;

// 	/* reserved for reverse iterator && iterators traits */
// 	typedef typename std::ptrdiff_t difference_type;
// 	typedef typename std::bidirectional_iterator_tag iterator_category;

// 	typedef value_type &reference;
// 	typedef value_type const &const_reference;
// 	typedef value_type *pointer;
// 	typedef value_type const *const_pointer;

// 	node_pointer _node;
// 	node_pointer RB_NULL;

//  private:
// 	node_pointer	_root;

//  public:
// 	RBiterator()
// 	:	_node(NULL),
// 		RB_NULL(NULL),
// 		_root(NULL) {}

// 	RBiterator(node_pointer root, node_pointer _node, node_pointer null)
// 	:	_node(_node),
// 		RB_NULL(null),
// 		_root(root) {}

// 	RBiterator(const RBiterator& x)
// 	:	_node(x._node),
// 		RB_NULL(x.RB_NULL),
// 		_root(x._root) {}

// 	RBiterator &operator=(const RBiterator& rhs) {
// 		if (this != &rhs) {
// 			_node = rhs._node;
// 			RB_NULL = rhs.RB_NULL;
// 			_root = rhs._root;
// 		}
// 		return *this;
// 	}

// 	~RBiterator() {}

// 	/* const_iterator cast support */
// 	operator RBiterator<T const>() const {
// 		return RBiterator<T const>(_root, _node, RB_NULL);
// 	}

// 	/*
// 		Operators used to compare iterators
// 	*/
// 	bool	operator==	(const RBiterator& rhs) const {
// 		return _node == rhs._node;
// 	}
// 	bool	operator!=	(const RBiterator& rhs) const {
// 		return _node != rhs._node;
// 	}

// 	reference	operator*		() {
// 		return _node->value;
// 	}

// 	const_reference	operator*	() const {
// 		return _node->value;
// 	}

// 	pointer		operator->		() {
// 		return &_node->value;
// 	}

// 	const_pointer	operator->	() const {
// 		return &_node->value;
// 	}

// 	RBiterator&	operator++ () {
// 		if (_node != RB_NULL)
// 			_node = __next(_node);
// 		return *this;
// 	}
// 	RBiterator	operator++ (int) {
// 		RBiterator tmp(*this);
// 		++(*this);
// 		return tmp;
// 	}

// 	RBiterator&	operator-- () {
// 		if (_node != RB_NULL)
// 			_node = __prev(_node);
// 		else
// 			_node = __max_leaf(_root);
// 		return *this;
// 	}
// 	RBiterator	operator-- (int) {
// 		RBiterator tmp(*this);
// 		--(*this);
// 		return tmp;
// 	}

//  private:
// 	node_pointer __max_leaf(node_pointer node) const {
// 		while (node->right != RB_NULL)
// 			node = node->right;
// 		return node;
// 	}

// 	node_pointer	__prev(node_pointer node) const {
// 		if (node->left != RB_NULL)
// 			return __max_leaf(node->left);

// 		while (node->parent != RB_NULL && node == node->parent->left)
// 			node = node->parent;
// 		return node->parent;
// 	}

// 	node_pointer	__min_leaf(node_pointer node) const {
// 		while (node->left != RB_NULL)
// 			node = node->left;
// 		return node;
// 	}

// 	node_pointer	__next(node_pointer node) const {
// 		if (node->right != RB_NULL)
// 			return __min_leaf(node->right);

// 		while (node->parent != RB_NULL && node == node->parent->right)
// 			node = node->parent;
// 		return node->parent;
// 	}
// };
}
#endif