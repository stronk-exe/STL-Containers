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

#include "map_utils.hpp"

template<typename T> struct RDtree_Iterator
{
	typedef	T								value_type;
	typedef	T*								pointer;
	typedef	T&								reference;
	typedef	ptrdiff_t						difference_type;
	typedef	ft::bidirectional_iterator_tag	iterator_category;

	const node::node<T>* n;
	// RDtree_Iterator() = default;
	// RDtree_Iterator( const node::node<T>* n );

	const T& operator*() const;

	RDtree_Iterator& operator++()
	{
		// If the current node has a non-null right child,
		// 	Take a step down to the right
		// 	Then run down to the left as far as possible
		// If the current node has a null right child,
		// 	Move up the tree until we have moved over a left child link
		if (!node)
			return *this;
		if (node->right != nullptr)
			node = min_element(node->right);
		else
		{
			node *parent = n;
			while (parent != nullptr && n == parent->right)
			{
				node = parent;
				parent = parent->parent;
			}
			node = parent;
		}
		return *this;
	};

	RDtree_Iterator& operator++( int );

	RDtree_Iterator& operator--()
	{
		if (!node)
			return *this;
		if (node->left != nullptr)
			// node = min_element(node->right);
		else
		{
			node *parent = n;
			while (parent != nullptr && n == parent->right)
			{
				node = parent;
				parent = parent->parent;
			}
			node = parent;
		}
		return *this;
	};

	RDtree_Iterator& operator--( int );

	
};