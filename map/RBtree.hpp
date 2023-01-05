/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:32 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/04 16:14:18 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP


#define BLACK 0
#define RED 1

#include <iostream>
#include <memory>
#include "RBiterators.hpp"

namespace ft
{

template <typename T, typename Allocator>
class _RBT_base
{
	protected:
		// NOTA BENE
		// The stored instance is not actually of "allocator_type"'s
		// type.  Instead we rebind the type to
		// Allocator<node<Tp>>, which should probably be the same.
		// List_node<Tp> is not the same
		// size as Tp (it's 3 [p, left, right] pointers larger), and specializations on
		// Tp may go unused because List_node<Tp> is being bound
		// instead.
		//

		// types
		typedef typename Allocator::template rebind<node<T> >::other	Node_allocator_type;
		typedef typename Node_allocator_type::size_type					size_type;
		typedef node<T>													Node;

		Node_allocator_type _Node_allocator;

		_RBT_base(const Allocator &a) : _Node_allocator(a) {}

		~_RBT_base() {}

		Node *allocate_node() { return _Node_allocator.allocate(1); }

		void deallocate_node(Node *__p) { _Node_allocator.deallocate(__p, 1); }

		size_type max_size() const { return _Node_allocator.max_size(); }

		Node *create_node(const T &x = T()) {
			Node *p = this->allocate_node();
			_Node_allocator.construct(p, Node(x));
			return p;
		}

		void delete_node(Node *p) {
			_Node_allocator.destroy(p);
			deallocate_node(p);
		}
};

template <typename T, typename Compare, typename Alloc = std::allocator<T> >
class RBtree : protected _RBT_base<T, Alloc>
{

	public: // types
		typedef _RBT_base<T, Alloc>					Base;
		typedef Alloc								allocator_type;
		typedef T									value_type;
		typedef Compare								key_compare;
		typedef node<T>								Node;
		typedef Node*								node_pointer;
		typedef typename Base::size_type			size_type;

	private: // atributes
		key_compare		_comp;
		allocator_type	_alloc;
		node_pointer	_NIL;
		node_pointer	_root;
		size_type		_size;

	public:
		RBtree(
			const key_compare &c = key_compare(),
			const allocator_type &a = allocator_type()
			)
		: Base(a), _comp(c), _alloc(a)
		{
			_NIL = this->create_node();
			_root = _NIL;
			_size = 0;
		}

		RBtree(const RBtree &x)
			: Base(x._alloc), _comp(x._comp), _alloc(x._alloc)
		{
			_NIL = this->create_node();
			_root = x.clone(x._root, _NIL, this->Base::_Node_allocator);
			_root->p = _NIL;
			_size = x._size;
		}

		RBtree &operator=(const RBtree &x)
		{
			if (this != &x)
			{
				// assigne members of x to this members
				_size = x._size;
				_comp = x._comp;
				_alloc = x._alloc;
				// clear this.tree
				clear(_root);
				// get copy of x tree with this allocatore
				_root = x.clone(x._root, _NIL, Base::_Node_allocator);
				_root->p = _NIL;
			}
			return (*this);
		}

		~RBtree()
		{
			// destructor of RBT clear the tree and delete NIL
			clear(_root);
			this->delete_node(_NIL);
		}

		pair<Node *, bool> insert(const value_type &x)
		{
			Node *z = this->create_node(x);
			return insert(z);
		}

		pair<Node *, bool> insert(Node *z)
		{
			Node *y = _NIL;
			Node *x = _root;
			while (x != _NIL)
			{
				y = x;
				if (_comp(z->value, x->value)) // <
					x = x->left;
				else if (_comp(x->value, z->value))
					x = x->right;
				else // if the key already excite return the exicted node and false
				{
					this->delete_node(z);
					return ft::make_pair(x, false);
				}
			}
			z->p = y;
			if (y == _NIL)
				_root = z;
			else if (_comp(z->value, y->value))
				y->left = z;
			else
				y->right = z;
			z->left = _NIL;
			z->right = _NIL;
			z->color = RED;
			insertFIXUP(z);
			// _NIL->p = maximum();
			_size++;
			return ft::make_pair(z, true);
		}

		size_type deleteNode(const value_type &value)
		{
			Node *z = search(value);
			if (z != _NIL)
			{
				deleteNode(z, false);
				_size--;
				return 1;
			}
			return 0;
		}

		void deleteNode(Node *z, bool size)
		{
			Node *y = z;
			Node *x;
			bool OriginalColor = y->color;
			if (z->left == _NIL)
			{
				x = z->right;
				TRANSPLANT(z, z->right);
			}
			else if (z->right == _NIL)
			{
				x = z->left;
				TRANSPLANT(z, z->left);
			}
			else
			{
				y = minimum(z->right);
				OriginalColor = y->color;
				x = y->right;
				if (y->p == z)
					x->p = y;
				else
				{
					TRANSPLANT(y, y->right);
					y->right = z->right;
					y->right->p = y;
				}
				TRANSPLANT(z, y);
				y->left = z->left;
				y->left->p = y;
				y->color = z->color;
			}
			if (OriginalColor == BLACK)
				deleteFIXUP(x);
			this->delete_node(z);
			if (size)
				_size--;
			// _NIL->p = maximum();
		}

		Node *search(const value_type &value) const
		{
			Node *tmp = _root;
			while (tmp != _NIL)
			{
				if (_comp(value, tmp->value))
					tmp = tmp->left;
				else if (_comp(tmp->value, value))
					tmp = tmp->right;
				else
					return tmp;
			}
			return tmp;
		}

		Node *minimum() const
		{
			return minimum(_root);
		}

		Node *minimum(Node *t) const
		{
			if (t == _NIL)
				return t;
			Node *tmp = t;
			while (tmp->left != _NIL)
				tmp = tmp->left;
			return tmp;
		}

		Node *maximum() const
		{
			return maximum(_root);
		}

		Node *maximum(Node *t) const
		{
			if (t == _NIL)
				return t;
			Node *tmp = t;
			while (tmp->right != _NIL)
				tmp = tmp->right;
			return tmp;
		}
		Node *successor(Node *x) const
		{
			if (x == _NIL)
				return x;
			if (x->right != _NIL)
				return minimum(x->right);
			Node *y = x->p;
			while (y != _NIL && x == y->right)
			{
				x = y;
				y = y->p;
			}
			return y;
		}
		Node *predecessor(Node *x) const
		{
			if (x == _NIL)
				return x;
			if (x->left != _NIL)
				return maximum(x->left);
			Node *y = x->p;
			while (y != _NIL && x != y->right)
			{
				x = y;
				y = y->p;
			}
			return y;
		}

		Node *lower_bound(const value_type &value) const
		{
			Node *x = _root;
			Node *y = _NIL;
			while (x != _NIL)
			{
				if (_comp(value, x->value))
				{
					y = x;
					x = x->left;
				}
				else if (_comp(x->value, value))
					x = x->right;
				else
					return x;
			}
			return y;
		}

		Node *upper_bound(const value_type &value) const
		{
			Node *x = lower_bound(value);
			if (!_comp(x->value, value) && !_comp(value, x->value))
				return successor(x);
			return (x);
		}

		void clear()
		{
			clear(_root);
			_root = _NIL;
			_size = 0;
		}

		void swap(RBtree &x)
		{
			std::swap(_NIL, x._NIL);
			std::swap(_root, x._root);
			std::swap(_size, x._size);
			std::swap(_alloc, x._alloc);
			std::swap(_comp, x._comp);
		}

		node_pointer const nil() const { return _NIL; }

		node_pointer const *root() const { return &_root; }
		// node_pointer *n_root() { return &_root; }

		size_type max_size() const { return Base::max_size(); }

		size_type size() const { return _size; }


	private: // mem functions
		// clone a new tree from the subtree rooted at x
		// and use new_nil as the new sentinel in case
		// we have different trees
		Node *clone(Node *x, Node *nil, typename Base::Node_allocator_type &alloc) const
		{
			if (x == _NIL)
				return nil;
			Node *_node = alloc.allocate(1);
			alloc.construct(_node, *x);
			_node->left = clone(x->left, nil, alloc);
			if (_node->left != nil)
				_node->left->p = _node;
			_node->right = clone(x->right, nil, alloc);
			if (_node->right != nil)
				_node->right->p = _node;
			return _node;
		}

		void clear(Node *node)
		{
			if (node == _NIL)
				return;

			/* first delete both subtrees */
			clear(node->left);
			clear(node->right);
			/* then delete the node */
			this->delete_node(node);
		}

		void TRANSPLANT(Node *u, Node *v)
		{
			if (u->p == _NIL)
				_root = v;
			else if (u->p->left == u)
				u->p->left = v;
			else
				u->p->right = v;
			v->p = u->p;
		}

		void LEFT_ROTATE(Node *x)
		{
			Node *y = x->right;
			x->right = y->left;
			if (y->left != _NIL)
				y->left->p = x;
			y->p = x->p;
			if (x->p == _NIL)
				_root = y;
			if (x == x->p->left)
				x->p->left = y;
			else
				x->p->right = y;
			y->left = x;
			x->p = y;
		}

		void RIGHT_ROTATE(Node *x)
		{
			Node *y = x->left;
			x->left = y->right;
			if (y->right != _NIL)
				y->right->p = x;
			y->p = x->p;
			if (x->p == _NIL)
				_root = y;
			if (x == x->p->left)
				x->p->left = y;
			else
				x->p->right = y;
			y->right = x;
			x->p = y;
		}

		void insertFIXUP(Node *z)
		{

			while (z->p->color == RED)
			{

				if (z->p == z->p->p->left)
				{
					Node *y = z->p->p->right;
					if (y->color == RED)
					{ // recolor
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					}
					else
					{ // do suitablle rotation and recolor
						if (z == z->p->right)
						{ // LR
							z = z->p;
							LEFT_ROTATE(z);
						}
						z->p->color = BLACK; // LL
						z->p->p->color = RED;
						RIGHT_ROTATE(z->p->p);
					}
				}
				else
				{ // z.p == z.p.p.right
					Node *y = z->p->p->left;
					if (y->color == RED)
					{ // recolor
						z->p->color = BLACK;
						y->color = BLACK;
						z->p->p->color = RED;
						z = z->p->p;
					}
					else
					{ // do suitablle rotation and recolor
						if (z == z->p->left)
						{ // RL
							z = z->p;
							RIGHT_ROTATE(z);
						}
						z->p->color = BLACK; // RR
						z->p->p->color = RED;
						LEFT_ROTATE(z->p->p);
					}
				}
			}
			_root->color = BLACK;
		}
		void deleteFIXUP(Node *x)
		{

			while (x != _root and x->color == BLACK)
			{
				if (x == x->p->left)
				{
					Node *w = x->p->right;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->p->color = RED;
						LEFT_ROTATE(x->p);
						w = x->p->right;
					}
					if (w->left->color == BLACK && w->right->color == BLACK)
					{
						w->color = RED;
						x = x->p;
					}
					else
					{

						if (w->right->color == BLACK)
						{
							w->left->color = BLACK;
							w->color = RED;
							RIGHT_ROTATE(w);
							w = x->p->right;
						}
						w->color = x->p->color;
						x->p->color = BLACK;
						w->right->color = BLACK;
						LEFT_ROTATE(x->p);
						x = _root;
					}
				}
				else
				{

					Node *w = x->p->left;
					if (w->color == RED)
					{
						w->color = BLACK;
						x->p->color = RED;
						RIGHT_ROTATE(x->p);
						w = x->p->left;
					}
					if (w->right->color == BLACK && w->left->color == BLACK)
					{
						w->color = RED;
						x = x->p;
					}
					else
					{

						if (w->left->color == BLACK)
						{
							w->right->color = BLACK;
							w->color = RED;
							LEFT_ROTATE(w);
							w = x->p->left;
						}
						w->color = x->p->color;
						x->p->color = BLACK;
						w->left->color = BLACK;
						RIGHT_ROTATE(x->p);
						x = _root;
					}
				}
			}
			x->color = BLACK;
		}
};

}




// #include "RBnode.hpp"
// #include "RBiterators.hpp"
// // #include "../utils/vector_Iterators.hpp"
// #include "../utils/reverse_iterator.hpp"
// // #include "../utils/utils.hpp"
// #include "../utils/pair.hpp"
// #include "../utils/equal.hpp"
// #include "../utils/enable_if.hpp"
// #include "../utils/lexicographical_compare.hpp"

// namespace ft
// {
//     template<typename T, typename Compare, typename Alloc=std::allocator<node<T> > > class RBtree
//     {
//         // public:
//             // typedef node<T>	root;
//             // typedef	typename Allocator::template rebind<node<T> >::other				allocator;
//             // typedef	typename allocator::size_type	size_type;
//             // allocator	_allocator;

//         public:
//                 // typedef	Key							key_type;
//                 typedef	T							                    value_type;
//                 // typedef	std::pair<const Key, T>		value_type;
//                 typedef node<T>                                         nvalue_type;
//                 typedef const node<T>                                   const_nvalue_type;
//                 typedef	size_t						                    size_type;
//                 typedef	T											mapped_type;
//                 typedef	ptrdiff_t					                    difference_type;
//                 typedef	Compare						                    compare_type;
//                 typedef	Alloc   					                    allocator_type;
//                 typedef	node<T>&							            reference;
//                 typedef	const node<T>&					                const_reference;
//                 typedef	node<T>*							            pointer;
//                 typedef	const node<T>*					                const_pointer;
//                 typedef typename ft::RBiterator<nvalue_type>            iterator;
//                 typedef typename ft::RBiterator<nvalue_type>            const_iterator;
//                 typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
//                 typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;
        
//         private:
//             allocator_type	_allocator;
//             compare_type    comp;
//             pointer			_root;
//             pointer			_nil;
//             size_type		len;

//         // protected:
//         // 	void	rotateRight( node<T> *&, node<T> *& );
//         // 	void	rotateLeft( node<T> *&, node<T> *& );
//         // 	void	fixViolation( node<T> *&, node<T> *& );
//         public:
//             //----  Constructors
//                 explicit RBtree( allocator_type alloc=allocator_type() ) : _allocator(alloc), comp(compare_type()), _root(NULL), _nil(NULL), len(0)
//                 {
//                     // std::cout << "Yow\n";
//                     new_empty_node();
//                 };
//                 RBtree( const RBtree &other ) : _allocator(other._allocator), _root(NULL), _nil(NULL), len(0)
//                 {
//                     new_empty_node();
//                     copy_tree(other._root, other._nil);
//                 }
//                 RBtree &operator=( const RBtree &other )
//                 {
//                     if (this != &other)
//                     {
//                         clear();
//                         // _allocator.destroy(*this);
//                         // destroy_node();
//                         if (_nil != NULL)
//                         {
//                             _allocator.destroy(_nil);
//                             _allocator.deallocate(_nil, 1);
//                             _nil = NULL;
//                         }
//                         _allocator = other._allocator;
//                         // nl = _allocator.allocate(1);
//                         // nl->parent = other->parent;
//                         // nl->right = other->right;
//                         // nl->left = other->left;
//                         // nl->color = BLACK;
//                         new_empty_node();
//                         // _root = nl;
//                         // len=other.len;
//                         // rbt(other.rbt);
//                         copy_tree(other._root, other._nil);
//                      //   new_rbt(other.rt, other.nl);
//                     }
//                     return *this;
//                 }
//                 void copy_tree(pointer node, pointer nil) {
//                     if (node == NULL || node == nil)
//                         return;
//                     copy_tree(node->left, nil);
//                     // new_node(node->data);
//                     insert_node(node->data);
//                     // std::cout << "0000000am i here " << len << std::endl;
//                     copy_tree(node->right, nil);
//                 }
//                 ~RBtree()
//                 {
//                     clear();
//                     // destroy_node();
//                     if (_nil != NULL)
//                     {
//                         _allocator.destroy(_nil);
//                         _allocator.deallocate(_nil, 1);
//                         _nil = NULL;
//                     }
//                 }

                

//             //----  Iterators

//                 iterator begin()
//                 {
//                     // std::cout << "Why its always you?" << std::endl;
//                     return iterator(_root, min_element(_root), _nil);
//                 }
//                 const_iterator begin() const
//                 {
//                     return const_iterator(_root, min_element(_root), _nil);
//                 }

//                 iterator end()
//                 {
//                     // std::cout << "and you?" << std::endl;
//                     // std::cout << _root->data.first << std::endl;
//                     return iterator(_root, _nil, _nil); // node, nil, root
//                 }
//                 const_iterator end() const
//                 {
//                     return const_iterator(_root, _nil, _nil);
//                 }

//                 reverse_iterator rbegin()
//                 {
//                     return reverse_iterator(end());
//                 }
//                 const_reverse_iterator rbegin() const
//                 {
//                     return const_reverse_iterator(end());
//                 }

//                 reverse_iterator rend()
//                 {
//                     return reverse_iterator(begin());
//                 }
//                 const_reverse_iterator rend() const
//                 {
//                     return const_reverse_iterator(begin());
//                 }
//             //----  Memeber functions

//                 ft::pair<iterator, bool> insert( const value_type& value )
//                 {
//                     // std::cout << "~~~~Shit made it to here~~~~~> " << value.second << std::endl;
//                     return insert_node(value);
//                     // return ft::make_pair(iterator(insert_node(value), _root, _nil), true);
//                 }
//                 iterator insert( iterator pos, const value_type& value )
//                 {
//                     (void)pos;
//                     return insert(value).first;
//                 }
//                 template <class InputIterator> void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL)
//                 {
//                     // while (first != last)
//                     // {
//                     //     insert_node(*first);
//                     //     first++;
//                     // }
//                 // std::cout << "~~~~~~~~~kan hna~~~~~~~~~" << len << std::endl;
                    
//                     for (; first != last; ++first)
//                     {
//                         insert_node(*first);
//                         // std::cout << "zho " << len << std::endl;
//                     }
//                 }

//             // insertion
//                 ft::pair<iterator, bool> insert_node(const value_type &value)
//                 {
//                     pointer temp = search(value);
//                     if (temp)
//                         return ft::make_pair(iterator(_root, temp, _nil), false);
                    
//                     pointer n = new_node(value);
//                     pointer _temp_root=_root, _temp_nil=_nil;
//                     while (_temp_root != _nil)
//                     {
//                         _temp_nil = _temp_root;
//                         // if (value < _temp_root->data)
//                         if (comp(value, _temp_root->data)>0)
//                             _temp_root = _temp_root->left;
//                         else
//                             _temp_root = _temp_root->right;
//                     }
//                     n->parent = _temp_nil;
//                     if (_temp_nil == _nil)
//                         _root = n;
//                     else if (comp(n->data, _temp_nil->data))
//                     // else if (n->data < _temp_nil->data)
//                     {
//                         // std::cout << "why mista\n";
//                         _temp_nil->left = n;
//                     }
//                     else
//                         _temp_nil->right = n;
//                     // std::cout << ">> node data " << _temp_nil->data.second << " X " << n->data.second << std::endl;
//                     // printRBtree();
// 					if (n->parent == _nil)
// 					{
// 						n->color = BLACK;
// 						return ft::make_pair(iterator(_root, n, _nil), true);
// 					}
// 					if (n->parent->parent == _nil)
// 						return ft::make_pair(iterator( _root, n, _nil), true);
//                     // std::cout << "hola\n";
// 					// _fixshiUp(n);
//                     fix_insertion(n);
//                     return ft::make_pair(iterator(_root, n, _nil), true);
//                 }

                

// 				void    fix_insertion( pointer n )
// 				{
// 					pointer temp;

// 					while (n->parent->color == RED)
// 					{
// 						if (n->parent == n->parent->parent->right)
// 						{
// 							temp = n->parent->parent->left;
// 							if (temp->color == RED)
// 							{
// 								temp->color = BLACK;
// 								n->parent->color = BLACK;
// 								n->parent->parent->color = RED;
// 								n = n->parent->parent;
// 							}
// 							else
// 							{
// 								if (n == n->parent->left)
// 								{
// 									n = n->parent;
// 									rotateRight(n);
// 								}
// 								n->parent->color = BLACK;
// 								n->parent->parent->color = RED;
// 								rotateLeft(n->parent->parent);
// 							}
// 						}
// 						else
// 						{
// 							temp = n->parent->parent->right;
// 							if (temp->color == RED)
// 							{
// 								temp->color = BLACK;
// 								n->parent->color = BLACK;
// 								n->parent->parent->color = RED;
// 								n = n->parent->parent;
// 							}
// 							else
// 							{
// 								if (n == n->parent->right)
// 								{
// 									n = n->parent;
// 									rotateLeft(n);
// 								}
// 								n->parent->color = BLACK;
// 								n->parent->parent->color = RED;
// 								rotateRight(n->parent->parent);
//                             // std::cout << "WA LALLA\n";
// 							}
// 						}
// 						if (n == _root)
// 							break;
// 					}
// 					_root->color = BLACK;
// 				}
//     //             void	__insert_fixup(pointer node) {
// 	// 	pointer u;

// 	// 	while (node->parent->color == RED) {
// 	// 		if (node->parent == node->parent->parent->right) {
// 	// 			u = node->parent->parent->left;
// 	// 			if (u->color == RED) {
// 	// 				u->color = BLACK;
// 	// 				node->parent->color = BLACK;
// 	// 				node->parent->parent->color = RED;
// 	// 				node = node->parent->parent;
// 	// 			} else {
// 	// 				if (node == node->parent->left) {
// 	// 					node = node->parent;
// 	// 					__rotate_right(node);
// 	// 				}
// 	// 				node->parent->color = BLACK;
// 	// 				node->parent->parent->color = RED;
// 	// 				__rotate_left(node->parent->parent);
// 	// 			}
// 	// 		} else {
// 	// 			u = node->parent->parent->right;
// 	// 			if (u->color == RED) {
// 	// 				u->color = BLACK;
// 	// 				node->parent->color = BLACK;
// 	// 				node->parent->parent->color = RED;
// 	// 				node = node->parent->parent;
// 	// 			} else {
// 	// 				if (node == node->parent->right) {
// 	// 					node = node->parent;
// 	// 					__rotate_left(node);
// 	// 				}
// 	// 				node->parent->color = BLACK;
// 	// 				node->parent->parent->color = RED;
// 	// 				__rotate_right(node->parent->parent);
// 	// 			}
// 	// 		}

// 	// 		if (node == _root)
// 	// 			break;
// 	// 	}
// 	// 	_root->color = BLACK;
// 	// }

// 	// ft::pair<iterator, bool>	insert_node(const value_type &data) {
// 	// 	pointer look = __lookup_node(data);
// 	// 	if (look)
// 	// 		return ft::make_pair(iterator(look, _root, _nil), false);

// 	// 	pointer node = __alloc_node(data);
// 	// 	if (!node)
// 	// 		throw std::bad_alloc();

// 	// 	pointer y = _nil;
// 	// 	pointer x = _root;

// 	// 	while (x != _nil) {
// 	// 		y = x;
// 	// 		if (comp(data, x->data) > 0)
// 	// 			x = x->left;
// 	// 		else
// 	// 			x = x->right;
// 	// 	}

// 	// 	node->parent = y;
// 	// 	if (y == _nil)
// 	// 		_root = node;
// 	// 	else if (comp(node->data, y->data))
// 	// 		y->left = node;
// 	// 	else
// 	// 		y->right = node;

// 	// 	if (node->parent == _nil) {
// 	// 		node->color = BLACK;
// 	// 		return ft::make_pair(iterator(node, _root, _nil), true);
// 	// 	}

// 	// 	if (node->parent->parent == _nil)
// 	// 		return ft::make_pair(iterator(node, _root, _nil), true);

// 	// 	__insert_fixup(node);
// 	// 	return ft::make_pair(iterator(node, _root, _nil), true);
// 	// }

//     // void	__rotate_left(pointer node) {
// 	// 	pointer tmp = node->right;

// 	// 	node->right = tmp->left;
// 	// 	if (tmp->left != _nil)
// 	// 		tmp->left->parent = node;

// 	// 	tmp->parent = node->parent;
// 	// 	if (node->parent == _nil)
// 	// 		_root = tmp;
// 	// 	else if (node == node->parent->left)
// 	// 		node->parent->left = tmp;
// 	// 	else
// 	// 		node->parent->right = tmp;
// 	// 	tmp->left = node;
// 	// 	node->parent = tmp;
// 	// }

// 	// void	__rotate_right(pointer node) {
// 	// 	pointer tmp = node->left;

// 	// 	node->left = tmp->right;
// 	// 	if (tmp->right != _nil)
// 	// 		tmp->right->parent = node;

// 	// 	tmp->parent = node->parent;
// 	// 	if (node->parent == _nil)
// 	// 		_root = tmp;
// 	// 	else if (node == node->parent->right)
// 	// 		node->parent->right = tmp;
// 	// 	else
// 	// 		node->parent->left = tmp;
// 	// 	tmp->right = node;
// 	// 	node->parent = tmp;
// 	// }

//                 // ft::pair<iterator, bool>	insert_node(const value_type &data)
//                 // {
//                 //     pointer look = __lookup_node(data);
//                 //     if (look)
//                 //         return ft::make_pair(iterator(look, _root, _nil), false);

//                 //     pointer node = new_node(data);
//                 //     if (!node)
//                 //         throw std::bad_alloc();

//                 //     pointer y = _nil;
//                 //     pointer x = _root;

//                 //     while (x != _nil) {
//                 //         y = x;
//                 //         if (comp(data, x->data) > 0)
//                 //             x = x->left;
//                 //         else
//                 //             x = x->right;
//                 //     }

//                 //     node->parent = y;
//                 //     if (y == _nil)
//                 //         _root = node;
//                 //     else if (comp(node->data, y->data))
//                 //         y->left = node;
//                 //     else
//                 //         y->right = node;

//                 //     // std::cout << "------Hna node jdida " << len << std::endl;
//                 //     if (node->parent == _nil) {
//                 //         node->color = BLACK;
//                 //         return ft::make_pair(iterator(node, _root, _nil), true);
//                 //     }

//                 //     if (node->parent->parent == _nil)
//                 //         return ft::make_pair(iterator(node, _root, _nil), true);

//                 //     __insert_fixup(node);
//                 //     return ft::make_pair(iterator(node, _root, _nil), true);
//                 // }
//                     pointer __alloc_node(const value_type &data) {
//                         pointer node = _allocator.allocate(1);

//                         node->data = data;
//                         // std::cout << "Ui\n";
//                         node->color = RED;
//                         node->left = _nil;
//                         node->right = _nil;
//                         node->parent = _nil;
//                         ++len;
//                         return node;
//                     }

//                 // void	__insert_fixup(pointer node) {
//                 //     pointer u;

//                 //     std::cout << "WA LKHARAWATS\n";
//                 //     while (node->parent->color == RED) {
//                 //         if (node->parent == node->parent->parent->right) {
//                 //             u = node->parent->parent->left;
//                 //             if (u->color == RED) {
//                 //                 u->color = BLACK;
//                 //                 node->parent->color = BLACK;
//                 //                 node->parent->parent->color = RED;
//                 //                 node = node->parent->parent;
//                 //             } else {
//                 //                 if (node == node->parent->left) {
//                 //                     node = node->parent;
//                 //                     rotateRight(node);
//                 //                 }
//                 //                 node->parent->color = BLACK;
//                 //                 node->parent->parent->color = RED;
//                 //                 rotateLeft(node->parent->parent);
//                 //             }
//                 //         } else {
//                 //             u = node->parent->parent->right;
//                 //             if (u->color == RED) {
//                 //                 u->color = BLACK;
//                 //                 node->parent->color = BLACK;
//                 //                 node->parent->parent->color = RED;
//                 //                 node = node->parent->parent;
//                 //             } else {
//                 //                 if (node == node->parent->right) {
//                 //                     node = node->parent;
//                 //                     rotateLeft(node);
//                 //                 }
//                 //                 node->parent->color = BLACK;
//                 //                 node->parent->parent->color = RED;
//                 //                 rotateRight(node->parent->parent);
//                 //             }
//                 //         }

//                 //         if (node == _root)
//                 //             break;
//                 //     }
//                 //     _root->color = _nil;
//                 // }


//                 void printHelper(pointer root, std::string indent, bool last) {
//                     if (root != _nil) {
//                     std::cout << indent;
//                     if (last) {
//                         std::cout << "R----";
//                         indent += "   ";
//                     } else {
//                         std::cout << "L----";
//                         indent += "|  ";
//                     }

//                     // std::cout << "root color " << root->color << std::endl;
//                     std::string sColor = root->color ? "RED" : "BLACK";
//                     std::cout << root->data.first << "(" << sColor << ")" << std::endl;
//                     printHelper(root->left, indent, false);
//                     printHelper(root->right, indent, true);
//                     }
//                 }
//                 void printRBtree() {
//                     if (_root) {
//                         printHelper(_root, "", true);
//                     }
//                 }
                
//                 // pointer new_node( value_type value )
//                 // {
//                 //     pointer n = _allocator.allocate(1);
                
//                 //     n->data = value;
//                 //     n->left = NULL;
//                 //     n->right = NULL;
//                 //     return n;
//                 // }
//                 pointer new_node( const value_type &value )
//                 {
//                     pointer n = _allocator.allocate(1);
//                     // if (!_root)
//                     // n->parent = _nil;
//                     // else
//                     n->parent = _nil;
//                     n->left = _nil;
//                     n->right = _nil;
//                     n->color = RED;
//                     // n->data = value;
//                     _allocator.construct(n, value);
//                     len++;
//                     // std::cout << len << "LMACHAKIL!\n";
//                     // rt = nl;
//                     return n;
//                 }

//                 void new_empty_node()
//                 {
//                     // _nil = _allocator.allocate(1);
//                     // // if (!_root)
//                     // _nil->parent = _nil;
//                     // // else
//                     // //     n->parent = _root;
//                     // _nil->left = _nil;
//                     // _nil->right = _nil;
//                     // _nil->color = BLACK;
//                     // _root = _nil;
//                     // // rt = nl;
//                     // // return n;
//                     _nil = _allocator.allocate(1);

//                     _nil->color = BLACK;
//                     _nil->parent = _nil;
//                     _nil->left = _nil;
//                     _nil->right = _nil;
//                     _root = _nil;
//                 }
            
//             // deletion
//                 void erase( iterator pos )
//                 {
//                     if (pos == end())
//                         return;
//                     delete_node(pos._node);
//                 }
//                 size_type erase( const value_type &value )
//                 {
//                     pointer n = search(value);
                    
//                     if (n)
//                     {
//                         // std::cout << "200 found\n";
// 						delete_node(n);
// 						return 1;
//                     }
//                     // std::cout << "404 Not found\n";
//                     return 0;
//                 }
//                 void erase( iterator first, iterator last )
//                 {
//                     while (first != last)
//                     {
//                         erase(first++);
//                         // ++first;
//                     }
//                 }
                
//                 void	delete_node( pointer n )
//                 {
//                     pointer x, y, z=_nil;
// 					bool original_color;
// 					pointer _temp_root = _root;
					
// 					while (_temp_root != _nil) // searching for the node of value
//                     {
// 						if (!comp(n->data, _temp_root->data))
// 						// if (n->data == _temp_root->data)
// 							z = _temp_root;
// 						if (comp(n->data, _temp_root->data) > 0)
// 						// if (n->data > _temp_root->data)
// 							_temp_root = _temp_root->left;
// 						else
// 							_temp_root = _temp_root->right;
//                     }
					
// 					if (z == _nil) // value not found
// 						return;
					
// 					y = z;
// 					original_color = y->color;
// 					if (z->left == _nil) // no children or only right
// 					{
//                         std::cout << "hoy\n";
//                         // std::cout << "rbegin before " << rbegin().p._node->data.first << std::endl;
// 						x = z->right;
//                         // std::cout << brgin()->_node.first << std::endl;
// 						// printRBtree();
//                         ft_transplant(z, z->right);
//                         // std::cout << "rbegin after " << rbegin().p._node->data.first << std::endl;
//                         // printRBtree();
//                         // exit(1);
// 					}
// 					else if (z->right == _nil) // only left
// 					{
// 						x = z->left;
// 						ft_transplant(z, z->left);
// 					}
// 					else // both children
// 					{
// 						y = min_element(z->right);
// 						original_color = y->color;
// 						x = y->right;
// 						if (y->parent == z)
// 							x->parent = y;
// 						else
// 						{
// 							ft_transplant(y, y->right);
// 							y->right = z->right;
// 							y->right->parent = y;
// 						}
// 						ft_transplant(z, y);
// 						y->left = z->left;
// 						y->left->parent = y;
// 						y->color = z->color;
// 					}
//                     // x = z->parent;
// 					_allocator.destroy(z);
// 					_allocator.deallocate(z, 1);
// 					len--;
//                     if (original_color == BLACK)// {}
// 						fix_deletion(x);
//                 }
                
//                 void    fix_deletion( pointer n )
//                 {
//                     pointer temp;
//                     while (n != _root && n->color == BLACK)
//                     {
// 						if (n == n->parent->left)
//                         {
// 							temp = n->parent->right;
// 							if (temp->color == RED)
// 							{
// 								temp->color = BLACK;
// 								n->parent->color = RED;
// 								rotateLeft(n->parent);
// 								temp = n->parent->right;
// 							}

// 							if (temp->left->color == BLACK && temp->right->color == BLACK)
// 							{
// 								temp->color = RED;
// 								n = n->parent;
// 							}
// 							else
// 							{
// 								if (temp->right->color == BLACK)
// 								{
// 									temp->left->color = BLACK;
// 									temp->color = RED;
// 									rotateRight(temp);
// 									temp = n->parent->right;
// 								}
//                                 std::cout << "jaa\n";
// 								temp->color = n->parent->color;
// 								n->parent->color = BLACK;
// 								temp->right->color = BLACK;
//                                 rotateLeft(n->parent);
// 								n = _root;
// 							}
//                         }
//                         else
//                         {
// 							temp = n->parent->left;
// 							if (temp->color == RED)
// 							{
// 								temp->color = BLACK;
// 								n->parent->color = RED;
// 								rotateRight(n->parent);
// 								temp = n->parent->left;
// 							}

// 							if (temp->right->color == BLACK && temp->right->color == BLACK)
// 							{
// 								temp->color = RED;
// 								n = n->parent;
// 							}
// 							else
// 							{
// 								if (temp->left->color == BLACK)
// 								{
// 									temp->right->color = BLACK;
// 									temp->color = RED;
// 									rotateLeft(temp);
// 									temp = n->parent->left;
// 								}
								
// 								temp->color = n->parent->color;
// 								n->parent->color = BLACK;
// 								temp->left->color = BLACK;
// 								rotateRight(n->parent);
// 								n = _root;
// 							}
//                         }
//                     }
// 					n->color = BLACK;
//                 // if (n == _root)
//                 // {
//                 //     rotateLeft(n);
                    
//                 // }
//                 }
//             /*    pointer    delete_node( pointer root, value_type n )
//                 {
//                     if (!root)
//                         return root;
//                     if (n->data > root->data)
//                         root->right = delete_node(root->right, n);
//                     else if (n->data > root->data)
//                         root->left = delete_node(root->left, n);
//                     else
//                     {
//                         if (!root->left)
//                             return root->right;
//                         else if (!root->right)
//                             return root->left;
//                         root->data = inOrderSuccessor(root->right);
//                         root->right = delete_node(root->right, n);
//                     }
//                     return root;
//                 }
//                 void delete_node(*//*pointer root,*/ /*pointer n )
//                 {
//                     if (n->color == BLACK)
//                     {
//                         if (n->right || n->left)
//                         {   
//                             if (n->right->color == RED)
//                                 n->right->color = BLACK;
//                             else if (n->left->color == RED)
//                                 n->left->color = BLACK;
//                             else
//                             {
                                
//                             }
//                         }
//                         else
//                         {
//                             //its leaf taht we wanna delete
//                         }
//                     }

                    
//                     iterator it = find(value);
//                     if (it == end())
//                         return;
//                     bool original_color = it->color;
//                     pointer n = it->_node;
//                     pointer x = NULL, y = NULL;
//                     if (!n->left)
//                     {
//                         x = n->left;
//                         transplate(n, n->left);
//                     }
//                     else if (!n->left)
//                     {
//                         x = n->right;
//                         transplate(n, n->right);
//                     }
//                     else
//                     {
//                         y = min_element(n->right);
//                         original_color = y->color;
//                         x = y->right;
//                         if (y->parent == n)
//                             x->parent = y;
//                         else
//                         {
//                             transplate(y, y->right);
//                             y->right = n->right;
//                             y->right->parent = y;
//                         }
//                     }
//                 }*/












//     //             pointer	__min_node(pointer node) const {
// 	// 	while (node->left != _nil)
// 	// 		node = node->left;
// 	// 	return node;
// 	// }

//     //         void	__rotate_left(pointer node) {
// 	// 	pointer tmp = node->right;

// 	// 	node->right = tmp->left;
// 	// 	if (tmp->left != _nil)
// 	// 		tmp->left->parent = node;

// 	// 	tmp->parent = node->parent;
// 	// 	if (node->parent == _nil)
// 	// 		_root = tmp;
// 	// 	else if (node == node->parent->left)
// 	// 		node->parent->left = tmp;
// 	// 	else
// 	// 		node->parent->right = tmp;
// 	// 	tmp->left = node;
// 	// 	node->parent = tmp;
// 	// }

// 	// void	__rotate_right(pointer node) {
// 	// 	pointer tmp = node->left;

// 	// 	node->left = tmp->right;
// 	// 	if (tmp->right != _nil)
// 	// 		tmp->right->parent = node;

// 	// 	tmp->parent = node->parent;
// 	// 	if (node->parent == _nil)
// 	// 		_root = tmp;
// 	// 	else if (node == node->parent->right)
// 	// 		node->parent->right = tmp;
// 	// 	else
// 	// 		node->parent->left = tmp;
// 	// 	tmp->right = node;
// 	// 	node->parent = tmp;
// 	// }

//     //             void	__delete_fixup(pointer node) {
// 	// 	pointer s;

// 	// 	while (node != _root && node->color == BLACK) {
// 	// 		if (node == node->parent->left) {
// 	// 			s = node->parent->right;
// 	// 			if (s->color == RED) {
// 	// 				s->color = BLACK;
// 	// 				node->parent->color = RED;
// 	// 				__rotate_left(node->parent);
// 	// 				s = node->parent->right;
// 	// 			}
// 	// 			if (s->left->color == BLACK && s->right->color == BLACK) {
// 	// 				s->color = RED;
// 	// 				node = node->parent;
// 	// 			} else {
// 	// 				if (s->right->color == BLACK) {
// 	// 					s->left->color = BLACK;
// 	// 					s->color = RED;
// 	// 					__rotate_right(s);
// 	// 					s = node->parent->right;
// 	// 				}
// 	// 				s->color = node->parent->color;
// 	// 				node->parent->color = BLACK;
// 	// 				s->right->color = BLACK;
// 	// 				__rotate_left(node->parent);
// 	// 				node = _root;
// 	// 			}
// 	// 		} else {
// 	// 			s = node->parent->left;
// 	// 			if (s->color == RED) {
// 	// 				s->color = BLACK;
// 	// 				node->parent->color = RED;
// 	// 				__rotate_right(node->parent);
// 	// 				s = node->parent->left;
// 	// 			}
// 	// 			if (s->right->color == BLACK && s->left->color == BLACK) {
// 	// 				s->color = RED;
// 	// 				node = node->parent;
// 	// 			} else {
// 	// 				if (s->left->color == BLACK) {
// 	// 					s->right->color = BLACK;
// 	// 					s->color = RED;
// 	// 					__rotate_left(s);
// 	// 					s = node->parent->left;
// 	// 				}
// 	// 				s->color = node->parent->color;
// 	// 				node->parent->color = BLACK;
// 	// 				s->left->color = BLACK;
// 	// 				__rotate_right(node->parent);
// 	// 				node = _root;
// 	// 			}
// 	// 		}
// 	// 	}
// 	// 	node->color = BLACK;
// 	// }

// 	// void	delete_node(pointer node) {
// 	// 	if (node == NULL)
// 	// 		return;

// 	// 	pointer root = _root;
// 	// 	pointer z = _nil;

// 	// 	while (root != _nil) {
// 	// 		if (comp(node->data, root->data) == 0)
// 	// 			z = root;

// 	// 		if (comp(node->data, root->data) > 0)
// 	// 			root = root->left;
// 	// 		else
// 	// 			root = root->right;
// 	// 	}

// 	// 	if (z == _nil)
// 	// 		return;

// 	// 	pointer x;
// 	// 	pointer y = z;
// 	// 	bool y_original_color = y->color;
// 	// 	if (z->left == _nil) {
// 	// 		x = z->right;
// 	// 		__transplant(z, z->right);
// 	// 	} else if (z->right == _nil) {
// 	// 		x = z->left;
// 	// 		__transplant(z, z->left);
// 	// 	} else {
// 	// 		y = __min_node(z->right);
// 	// 		y_original_color = y->color;
// 	// 		x = y->right;
// 	// 		if (y->parent == z) {
// 	// 			x->parent = y;
// 	// 		} else {
// 	// 			__transplant(y, y->right);
// 	// 			y->right = z->right;
// 	// 			y->right->parent = y;
// 	// 		}
// 	// 		__transplant(z, y);
// 	// 		y->left = z->left;
// 	// 		y->left->parent = y;
// 	// 		y->color = z->color;
// 	// 	}
// 	// 	__destroy_node(z);
// 	// 	if (y_original_color == BLACK)
// 	// 		__delete_fixup(x);
// 	// }

// 	// void	__destroy_node(pointer n) {
// 	// 	_allocator.destroy(n);
// 	// 	_allocator.deallocate(n, 1);
// 	// 	--len;
// 	// }

//     // void	__transplant(pointer u, pointer v) {
// 	// 	if (u->parent == _nil)
// 	// 		_root = v;
// 	// 	else if (u == u->parent->left)
// 	// 		u->parent->left = v;
// 	// 	else
// 	// 		u->parent->right = v;
// 	// 	if (v)
// 	// 		v->parent = u->parent;
// 	// }














// 				void	ft_transplant( pointer x, pointer y )
// 				{
// 					if (x->parent == _nil) // x is the root
// 						_root = y;
// 					else if (x == x->parent->left) // y is the left child
// 						x->parent->left = y;
// 					else // y is the left child
// 						x->parent->right = y;
// 					// if (y) //       <<<<<<<<<<<<< HADI 3LAAAACH
// 						y->parent = x->parent;
// 				}
                
// 				void    rotateLeft( pointer n )
// 				{
// 					pointer temp = n->right;

// 					n->right = temp->left;
// 					if (temp->left != _nil)
// 						temp->left->parent = n;
// 					temp->parent = n->parent;
// 					if (n->parent == _nil)
// 						_root = temp;
// 					else if (n == n->parent->left)
// 						n->parent->left = temp;
// 					else
// 						n->parent->right = temp;
// 					temp->left = n;
// 					n->parent = temp;
// 				};

// 				void    rotateRight( pointer n )
// 				{
// 					pointer temp = n->left;

// 					n->left = temp->right;
// 					if (temp->right != _nil)
// 						temp->right->parent = n;
// 					temp->parent = n->parent;
// 					if (n->parent == _nil)
// 						_root = temp;
// 					else if (n == n->parent->right)
// 						n->parent->right = temp;
// 					else
// 						n->parent->left = temp;
// 					temp->right = n;
// 					n->parent = temp;
// 				};

                
//                 value_type successor( pointer n )
//                 {
//                     value_type temp_data = n->data;

//                     while (n->left != NULL)
//                     {
//                         n = n->left;
//                         temp_data = n->left->data;
//                     }
//                     return temp_data;
//                 };

                
//                 // pointer insert_node()
//                 // {

//                 // }
//             /*    void delete_node( pointer n )
//                 {
//                     pointer temp_rt = rt, temp_nl = nl;

//                     while (temp__root != nl)
//                     {
//                         if (n->data == temp_rt->data)
//                             temp_nl = temp_rt;
//                         else if (n->data > temp_rt->data)
//                         {
//                             temp_nl = temp_rt;
//                             temp_rt = temp_rt->left;
//                         }
//                         else
//                         {
//                             temp_nl = temp_rt;
//                             temp_rt = temp_rt->right;
//                         }
//                     }
//                     if (temp_nl == nl)
//                         return;
                    
//                     // n->parent = temp_nl;
//                     // if (nl == temp_nl)
//                     //     rt = n;
//                     // else if (n->data > temp_nl->data)
//                     //     temp_nl->right = n;
//                     // else
//                     //     temp_nl->left = n;
//                     // fixViolation(temp_rt, n);
//                     // return ft::make_pair(iterator(rt, n, nl), true);
//                 }*/

//             iterator find( const value_type &value )
//             {
//                 // std::cout << "Ha lmachakil hahoma " << value.second << std::endl;
//                 pointer n = search(value);

//                 if (n)
//                     return iterator(_root, n, _nil);
//                 // std::cout << "shit not found!" << std::endl;
//                 return end();
//             }
//             const_iterator find( const value_type &value ) const
//             {
//                 pointer n = search(value);

//                 if (n)
//                     return const_iterator(_root, n, _nil);
//                 return end();
//             }


//     //         iterator find(const value_type &value) {
// 	// 	pointer tmp = __lookup_node(value);

// 	// 	if (tmp)
// 	// 		return iterator(tmp, _root, _nil);
// 	// 	return end();
// 	// }
// 	// const_iterator find(const value_type &value) const {
// 	// 	pointer tmp = __lookup_node(value);

// 	// 	if (tmp)
// 	// 		return const_iterator(tmp, _root, _nil);
// 	// 	return end();
// 	// }

//             pointer __lookup_node(const value_type &data) const {
//                 pointer node = _root;

//                 while (node != _nil) {
//                     if (comp(data, node->data))
//                         node = node->left;
//                     else if (comp(node->data, data))
//                         node = node->right;
//                     else
//                         return node;
//                 }
//                 return NULL;
//             }

//             bool empty() const
//             {
//                 if (!len)
//                     return true;
//                 return false;
//             }

//             size_type size() const
//             {
//                 return len;
//             }

//             size_type max_size() const
//             {
//                 return _allocator.max_size();
//             }

//             void clear()
//             {
//                 ft_destroy(_root);
//                 _root = _nil;
//                 len = 0;
//             }
//             void ft_destroy( pointer n )
//             {
//                 if (n == NULL || n == _nil)
//                     return;
//                 ft_destroy(n->left);
//                 ft_destroy(n->right);
//                 _allocator.destroy(n);
//                 _allocator.deallocate(n,1);
//                 len--;
//             }

//             void    swap( RBtree &rbt )
//             {
//                 std::swap(_allocator, rbt._allocator);
//                 std::swap(comp, rbt.comp);
//                 std::swap(_root, rbt._root);
//                 std::swap(_nil, rbt._nil);
//                 std::swap(len, rbt.len);
//             }

//             iterator lower_bound( const value_type &value )
// 		    {
//                 for (iterator it = begin(); it != end(); ++it) {
//                     if (comp(it._node->data, value) == false)
//                         return it;
//                 }
//                 return end();
// 		    };
// 		    const_iterator lower_bound( const value_type &value ) const
// 		    {
//                 for (const_iterator it = begin(); it != end(); ++it) {
//                     if (comp(it._node->data, value) == false)
//                         return it;
//                 }
//                 return end();
// 		    };

//             iterator upper_bound( const value_type &value )
// 		    {
//                 for (iterator it = begin(); it != end(); ++it) {
//                     if (comp(value, it._node->data))
//                         return it;
//                 }
//                 return end();
// 		    };
// 		    const_iterator upper_bound( const value_type &value ) const
// 		    {
//                 for (const_iterator it = begin(); it != end(); ++it) {
//                     if (comp(value, it._node->data))
//                         return it;
//                 }
//                 return end();
// 		    };

//             ft::pair<iterator,iterator> equal_range( const value_type &value )
// 		    {
//                 return ft::make_pair(lower_bound(value), upper_bound(value));
// 		    };
// 		    ft::pair<const_iterator,const_iterator> equal_range( const value_type& value ) const
// 		    {
//                 return ft::make_pair(lower_bound(value), upper_bound(value));
// 		    };

//             //----  Utils
//             pointer search(const value_type &value) const {
//                 pointer node = _root;
//                 int i=0;

//                 while (node != _nil)
//                 {
//                     // std::cout << i << " - we got " << node->data.first << " - " << value.first << std::endl;
//                     if (comp(value, node->data))
//                     // if (value < node->data)
//                         node = node->left;
//                     // if (value == node->data)
//                     else if (comp(node->data, value))
//                     // else if (value > node->data)
//                         node = node->right;
//                     else
//                     {
//                         return node;
//                     }
//                     // std::cout << i << " - we got " << node->data.first << " - " << value.first << std::endl;
//                     i++;
//                 }
//                 // std::cout << i << " Yiip\n";
//                 return NULL;
//             }

//             // pointer min_element( pointer n ) const
//             // {
//             //     std::cout << "nil " << _nil->data.first << std::endl;
//             //     std::cout << "n " << n->data.first << std::endl;
//             //     if (n->left == _nil)
//             //         return n;
//             //     return min_element(n->left);
//             // };

//             pointer min_element(pointer node) const {
//                 while (node->left != _nil)
//                     node = node->left;
//                 return node;
//             }
//     };
// }

#endif