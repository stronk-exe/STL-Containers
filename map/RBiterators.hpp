/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBiterators.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:47 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/28 22:03:33 by ael-asri         ###   ########.fr       */
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
            n_pointer it_root;
            n_pointer it_nil;
        
        public:
            RBiterator() : _node(NULL), it_root(NULL), it_nil(NULL) {};
            RBiterator( n_pointer n, n_pointer root, n_pointer nil ) : _node(n), it_root(root), it_nil(nil) {};
            RBiterator( const RBiterator &rbtit ) : _node(rbtit._node), it_root(rbtit.it_root), it_nil(rbtit.it_nil) {};
            ~RBiterator() {};

            RBiterator& operator=( const RBiterator& rbtit )
            {
                if (*this != rbtit)
                {
                    _node = rbtit._node;
                    it_root = rbtit.it_root;
                    it_nil = rbtit.it_nil;
                }
                return *this;
            }

            operator RBiterator<T const>() const
            {
                return RBiterator<T const>(_node, it_root, it_nil);
            }

            bool operator==( const RBiterator& rbtit ) const
            {
                return _node == rbtit._node;
            }
            bool operator!=( const RBiterator& rbtit ) const
            {
                return _node != rbtit._node;
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
}
#endif