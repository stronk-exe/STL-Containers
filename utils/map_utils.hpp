/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:20:30 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/13 15:46:33 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_HPP
#define MAP_UTILS_HPP

#include <iostream>
/*


template <typename T> RB_Tree()
{

};
template<typename T> class bst
{
	public:
		T	data;
		bst	*parent;
		bst	*right;
		bst	*left;
		int	color;
		
		bst() : data(0), parent(0), right(0), left(0), color(0) {};
		bst( T value ) : data(value), parent(0), right(0), left(0), color(0) {};
		~bst() {};

		
};
*/


/*
template<typename T> class node
{
	public:
		T		data;
		node	*parent;
		node	*right;
		node	*left;
		int		color;

		node *new_node( T value )
		{
			node *n = new node<T>;

			n->data = value;
			n->parent = n->right = n->left = NULL;
			n->color = 0;
			return n;
		};

		node *insert_node( node *root, T value )
		{
			if (!root)
				return new_node(value);
			if (value > root->data)
				root->right = insert_node(root->right, value);
			else if (value < root->data)
				root->left = insert_node(root->left, value);
			root->color = 0;
			std::cout << "root color " << root->color << std::endl;
			return root;
		};

		node *minval_node( node *root )
		{
			node *current = root;

			while (current && current->left != NULL)
				current = current->left;
			return current;
		};

		node *maxval_node( node *root )
		{
			node *current = root;

			while (current && current->right != NULL)
				current = current->right;
			return current;
		};

		node *delete_node( node *root, T value )
		{
			if (!root)
				return root;
			if (value > root->data)
				root->right = delete_node(root->right, value);
			else if (value < root->data)
				root->left = delete_node(root->left, value);
			else
			{
				if (!root->right && !root->left)
					return NULL;
				else if (!root->right)
				{
					struct node *temp = root->left;
					free(root);
					return temp;
				}
				else if (!root->left)
				{
					struct node *temp = root->right;
					free(root);
					return temp;
				}
				struct node *temp = minval_node(root->right);
				root->data = temp->data;
				root->right = delete_node(root->right, temp->data);
			}
			return root;
		};

		void	inorder( node* root )
		{
			if (!root)
				return;
			inorder(root->left);
			std::cout << root->data << std::endl;
			inorder(root->right);
		}
};
*/

/*
template <typename T> struct node
{
	T		data;
	node	*parent;
	node	*right;
	node	*left;
	int		color;

	// node() : parent(0), left(0), right(0) {};
	// node( T &n ) : value(p), parent(0), left(0), right(0) {};
};

template<typename T> node *new_node( T value )
{
	node *n = new node<T>;

	n->data = value;
	n->parent = n->right = n->left = NULL;
	n->color = 0;
	return n;
};

template<typename T> node *insert_node( node *root<T>, T value )
{
	if (!root)
		return new_node(value);
	if (value > root->data)
		root->right = insert(root->right, value);
	else if (value < root->data)
		root->left = insert(root->left, value);
	root->color = 0;
	std::cout << "root color " << root->color << std::endl;
	return root;
};



void	inorder( node* root )
{
	if (!root)
		return;
	inorder(root->left);
	std::cout << root->data << std::endl;
	inorder(root->right);
}*/
/*
// #include "../map/map.hpp"
#include "map_Iterators.hpp"

int	check_violation()
{
	return 1;
}
void	ft_balance(t_node node)
{
	if (node.color == "red")
	{
		// we color-flipp
	}
	else
	{
		// we rotate
		// if (case 1)
		// {
			
		// }
		// else if (case 2)
		// {
			
		// }
		// else if (case 3)
		// {
			
		// }
		// else if (case 4)
		// {
			
		// }
	}
}
int	key_exists(map m, Key key)
{
	for (ft::map<>::iterator it = m.begin(); it != m.end(); it++)
	{
		if (it.key == key)
			return 1;
	}
	return 0;
}
*/

////////////////////////////////////////////////////

enum Color { RED, BLACK };

template<typename T> struct node
{
	T		data;
	bool	color;
	node	*parent, *right, *left;

	node( T value )
	{
		data = value;
		parent = right = left = NULL;
		color = RED;
	};
};

template<typename T> class RBtree
{
	private:
		node<T>	*root;
	protected:
		void	rotateRight( node<T> *&, node<T> *& );
		void	rotateLeft( node<T> *&, node<T> *& );
		void	fixViolation( node<T> *&, node<T> *& );
	public:
		RBtree() { root = NULL; };
		void	insert( const T &n );
		node<T>	*search( T n );
		void	inorder();
		// void	levelOrder();
};

template<typename T> node<T> *insert_bst( node<T> *root, node<T> *n )
{
	if (!root)
		return n;
	if (n->data > root->data)
	{
		root->right = insert_bst(root->right, n);
		root->right->parent = root;
	}
	else if (n->data < root->data)
	{
		root->left = insert_bst(root->left, n);
		root->left->parent = root;
	}
	return root;
};

template<typename T> void inorderHelper( node<T> *root )
{
	if (!root)
		return;
	inorderHelper(root->left);
	std::cout << root->data << std::endl;
	inorderHelper(root->right);
}

template<typename T> void	RBtree<T>::rotateLeft( node<T> *&root, node<T> *&n )
{
	node<T> *temp = n->right;

	n->right = temp->left;
	if (n->right != NULL)
		n->right->parent = n;
	temp->parent = n->parent;
	if (n->parent == NULL)
		root = n->right;
	else if (n == n->parent->left)
		n->parent->left = temp;
	else
		n->parent->right = temp;
	temp->left = n;
	n->parent = temp;
};

template<typename T> void	RBtree<T>::rotateRight( node<T> *&root, node<T> *&n )
{
	node<T> *temp = n->left;

	n->left = temp->right;
	if (n->left != NULL)
		n->left->parent = n;
	temp->parent = n->parent;
	if (n->parent == NULL)
		root = temp;
	else if (n == n->parent->left)
		n->parent->left = temp;
	else
		n->parent->right = temp;
	temp->right = n;
	n->parent = temp;
};

template<typename T> void	RBtree<T>::fixViolation( node<T> *&root, node<T> *&n )
{
	node<T> *temp_parent = NULL, *temp_gparent = NULL, *temp_uncle;

	while (n != root && n->color != BLACK && n->parent->color == RED)
	{
		temp_parent = n->parent;
		temp_gparent = n->parent->parent;
		
		// case-1: parent of n is the left child of grand-parent of n
		if (temp_parent == temp_gparent->left)
		{
			temp_uncle = temp_gparent->right;
			
			// case-1.1: the uncle of n is also red so only recoloring required
			if (temp_uncle && temp_uncle->color == RED)
			{
				temp_gparent->color = RED;
				temp_parent->color = BLACK;
				temp_uncle->color = BLACK;
				n = temp_gparent;
			}
			else
			{
				// case-1.2: n is the right child of its parent so leftRotation required
				if (n == temp_parent->right)
				{
					rotateLeft(root, temp_parent);
					n = temp_parent;
					temp_parent = n->parent;
				}
				// case-1.3: n is the left child of its parent so rightRotation required
				rotateRight(root, temp_gparent);
				std::swap(temp_parent->color, temp_gparent->color);
				n = temp_parent;
			}
		}
		// case-2: parent of n is the right child of grand-parent of n
		else
		{
			temp_uncle = temp_gparent->left;

			// case-2.1: the uncle of n is also red so only recoloring required
			if (temp_uncle != NULL && temp_uncle->color == RED)
			{
				temp_gparent->color = RED;
				temp_parent->color = BLACK;
				temp_uncle->color = BLACK;
				n = temp_gparent;
			}
			else
			{
				// case-2.2: n is the left child of its parent so rightRotation required
				if (n == temp_parent->left)
				{
					rotateRight(root, temp_parent);
					n = temp_parent;
					temp_parent = n->parent;
				}
				// case-2.3: n is the right child of its parent so leftRotation required
				rotateLeft(root, temp_gparent);
				std::swap(temp_parent->color, temp_gparent->color);
				n = temp_parent;
			}
		}
	}
	root->color = BLACK;
};

template<typename T> void	RBtree<T>::insert( const T &value )
{
	node<T> *n = new node<T>(value);

	root = insert_bst(root, n);
	fixViolation(root, n);
};

template<typename T> node<T> *RBtree<T>::search( T n )
{
	node<T> *temp = root;

	while (temp != NULL)
	{
		if (n < temp->data)
		{
			if (!temp->left)
				break;
			else
				temp = temp->right;
		}
		else if (n == temp->data)
			break;
		else
		{
			if (!temp->right)
				break;
			else
				temp = temp->right;
		}
	}
	return temp;
};

template<typename T> void	RBtree<T>::inorder( void )
{
	inorderHelper(root);
}

template<typename T> node<T> *min_element( node<T> *root )
{
	if (!root || !root->left)
		return root;
	return min_element(root->left);
};

template<typename T> node<T> *successor( node<T> *n )
{
	node<T> *temp = n;

	while (temp->left != NULL)
		temp = temp->left;
	return temp;
};

// template<typename T> void	RBtree<T>::levelOrder( void )
// {
// 	levelOrderHelper(root);
// }

#endif