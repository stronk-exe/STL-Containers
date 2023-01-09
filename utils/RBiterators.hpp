/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBiterators.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:47 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/09 19:44:47 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBITERATORS_HPP
#define RBITERATORS_HPP

#include "RBnode.hpp"
#include "../utils/Iterator_traits.hpp"

namespace ft
{
    template<typename T> class RBiterator
    {
        public:
            typedef T*											n_pointer;
            typedef typename T::value_type						value_type;
            typedef value_type*									pointer;
            typedef value_type const*							const_pointer;
            typedef value_type&									reference;
            typedef value_type const&							const_reference;
            typedef typename std::ptrdiff_t						difference_type;
            typedef typename std::bidirectional_iterator_tag	iterator_category;
        
        private:
            n_pointer	_node;
            n_pointer	it_nil;
            n_pointer	const *it_root;
        
        public:
            RBiterator() : _node(NULL), it_nil(NULL), it_root(NULL) {};
            RBiterator( const n_pointer *root, const n_pointer n, const n_pointer nil) : _node(n), it_nil(nil), it_root(root) {};
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
                    _node = max_element(*it_root);
                return *this;
            };

            RBiterator operator--( int )
            {
                RBiterator _rbtit(*this);

                --(*this);
                return _rbtit;
            };

            n_pointer get_itnode()
            {
                return _node;
            }
            
        private:
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