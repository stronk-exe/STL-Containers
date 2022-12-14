/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_Iterators.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:49:07 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/13 15:46:10 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATORS_HPP
#define MAP_ITERATORS_HPP

#include "map_utils.hpp"

template<typename T> struct RBtree_Iterator
{
	typedef node<T>			*ptr;
	typedef node<const T>	*const_ptr;

	public:
		typedef	T								value_type;
		typedef	T*								pointer;
		typedef	T&								reference;
		typedef	ptrdiff_t						difference_type;
		typedef	ft::bidirectional_iterator_tag	iterator_category;

	private:
		node<T>	*_node;
		node<T>	**const_root;
		node<T>	*nil;

	//const node::node<T>* n;
	// RDtree_Iterator() = default;
	// RDtree_Iterator( const node::node<T>* n );

	public:
		RBtree_Iterator() : _node(NULL), root(NULL), nil(NULL) {};
		RBtree_Iterator( const RBtree_Iterator* rbti ) : _node(rbti._node), root(rbti.root), nil(rbti.nil) {};
		~RBtree_Iterator() {};

		RBtree_Iterator& operator=( const RBtree_Iterator& rbti )
		{
			if (this != rbti)
			{
				_node = rbti._node;
				root = rbti.root;
				nil = rbti.nil;
			}
			return *this;
		}

		bool operator==( const RBtree_Iterator& it ) const
		{
			return _node == it._node;
		}
		bool operator!=( const RBtree_Iterator& it ) const
		{
			return _node != it._node;
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
			return &(_node->data);
		};
		const_pointer	operator->() const
		{
			return &(_node->data);
		};

		RBtree_Iterator& operator++()
		{
			// If the current node has a non-null right child,
			// 	Take a step down to the right
			// 	Then run down to the left as far as possible
			// If the current node has a null right child,
			// 	Move up the tree until we have moved over a left child link
			if (!node)
				return *this;
			if (node->right != NULL)
				node = min_element(node->right);
			else
			{
				node *parent = n;
				while (parent != NULL && n == parent->right)
				{
					node = parent;
					parent = parent->parent;
				}
				node = parent;
			}
			return *this;
		};

		RBtree_Iterator& operator++( int )
		{

		};

		RBtree_Iterator& operator--()
		{
			if (!node)
				return *this;
			if (node->left != NULL)
				// node = min_element(node->right);
			else
			{
				node *parent = n;
				while (parent != NULL && n == parent->right)
				{
					node = parent;
					parent = parent->parent;
				}
				node = parent;
			}
			return *this;
		};

		RBtree_Iterator& operator--( int )
		{

		};

	
};

#endif