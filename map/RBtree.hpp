/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:32 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/30 13:06:05 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "RBnode.hpp"
#include "RBiterators.hpp"
// #include "../utils/vector_Iterators.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/utils.hpp"

namespace ft
{
    template<typename T, typename Compare, typename Alloc=std::allocator<node<T> > > class RBtree
    {
        // public:
            // typedef node<T>	root;
            // typedef	typename Allocator::template rebind<node<T> >::other				allocator;
            // typedef	typename allocator::size_type	size_type;
            // allocator	_allocator;

        public:
                // typedef	Key							key_type;
                typedef	T							                    value_type;
                // typedef	std::pair<const Key, T>		value_type;
                typedef node<T>                                         nvalue_type;
                typedef const node<T>                                   const_nvalue_type;
                typedef	size_t						                    size_type;
                typedef	T											mapped_type;
                typedef	ptrdiff_t					                    difference_type;
                typedef	Compare						                    compare_type;
                typedef	Alloc   					                    allocator_type;
                typedef	node<T>&							            reference;
                typedef	const node<T>&					                const_reference;
                typedef	node<T>*							            pointer;
                typedef	const node<T>*					                const_pointer;
                typedef typename ft::RBiterator<nvalue_type>            iterator;
                typedef typename ft::RBiterator<nvalue_type>            const_iterator;
                typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
                typedef typename ft::reverse_iterator<const_iterator>   const_reverse_iterator;
        
        private:
            allocator_type	_allocator;
            compare_type    comp;
            pointer			_root;
            pointer			_nil;
            size_type		len;

        // protected:
        // 	void	rotateRight( node<T> *&, node<T> *& );
        // 	void	rotateLeft( node<T> *&, node<T> *& );
        // 	void	fixViolation( node<T> *&, node<T> *& );
        public:
            //----  Constructors
                explicit RBtree( allocator_type alloc=allocator_type() ) : _allocator(alloc), comp(compare_type()), _root(NULL), _nil(NULL), len(0)
                {
                    new_empty_node();
                };
                RBtree( const RBtree &other ) : _allocator(other._allocator), comp(compare_type()), _root(NULL), _nil(NULL), len(0)
                {
                    new_empty_node();
                    copy_tree(other._root, other._nil);
                }
                RBtree &operator=( const RBtree &other )
                {
                    if (this != &other)
                    {
                        clear();
                        // _allocator.destroy(*this);
                        // destroy_node();
                        if (_nil != NULL)
                        {
                            _allocator.destroy(_nil);
                            _allocator.deallocate(_nil, 1);
                            _nil = NULL;
                        }
                        _allocator = other._allocator;
                        // nl = _allocator.allocate(1);
                        // nl->parent = other->parent;
                        // nl->right = other->right;
                        // nl->left = other->left;
                        // nl->color = BLACK;
                        new_empty_node();
                        // _root = nl;
                        // rbt(other.rbt);
                        copy_tree(other._root, other._nil);
                     //   new_rbt(other.rt, other.nl);
                    }
                    return *this;
                }
                void copy_tree(pointer node, pointer _nil) {
                    if (node == NULL || node == _nil)
                        return;
                    copy_tree(node->left, _nil);
                    new_node(node->data);
                    copy_tree(node->right, _nil);
                }
                ~RBtree()
                {
                    clear();
                    // destroy_node();
                    if (_nil != NULL)
                    {
                        _allocator.destroy(_nil);
                        _allocator.deallocate(_nil, 1);
                        _nil = NULL;
                    }
                }

                

            //----  Iterators

                iterator begin()
                {
                    return iterator(min_element(_root), _root, _nil);
                }
                const_iterator begin() const
                {
                    return const_iterator(min_element(_root), _root, _nil);
                }

                iterator end()
                {
                    return iterator(_nil, _root, _nil);
                }
                const_iterator end() const
                {
                    return const_iterator(_nil, _root, _nil);
                }

                reverse_iterator rbegin()
                {
                    return reverse_iterator(end());
                }
                const_reverse_iterator rbegin() const
                {
                    return const_reverse_iterator(end());
                }

                reverse_iterator rend()
                {
                    return reverse_iterator(begin());
                }
                const_reverse_iterator rend() const
                {
                    return const_reverse_iterator(begin());
                }
            //----  Memeber functions

                ft::pair<iterator, bool> insert( const value_type& value )
                {
                    return insert_node(value);
                    // return ft::make_pair(iterator(insert_node(value), _root, _nil), true);
                }
                iterator insert( iterator pos, const value_type& value )
                {
                    (void)pos;
                    return insert_node(value).first;
                }
                template <class InputIterator> void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL)
                {
                    while (first != last)
                    {
                        insert_node(*first);
                        first++;
                    }
                }

            // insertion
                ft::pair<iterator, bool> insert_node(const value_type &value)
                {
                    pointer temp = search(value);
                    if (temp)
                        {
                        return ft::make_pair(iterator(temp, _root, _nil), false);}
                            std::cout << "502\n";
                    
                    pointer n = new_node(value);
                    pointer _temp_root=_root, _temp_nil=_nil;
                    while (_temp_root != _nil)
                    {
                        _temp_nil = _temp_root;
                        if (value < _temp_root->data)
                        // if (comp(value, _temp_root->data))
                            _temp_root = _temp_root->left;
                        else
                            _temp_root = _temp_root->right;
                    }
                    n->parent = _temp_nil;
                    if (_temp_nil == _nil)
                        _root = n;
                    // else if (comp(n->data, _temp_nil->data))
                    else if (value < _temp_nil->data)
                        _temp_nil->left = n;
                    else
                        _temp_nil->right = n;
					if (n->parent == _nil)
					{
						n->color = BLACK;
						return ft::make_pair(iterator(n, _root, _nil), true);
					}
					if (n->parent->parent == _nil)
						return ft::make_pair(iterator(n, _root, _nil), true);
					_fixshiUp(n);
                    // __insert_fixup(n);
                    return ft::make_pair(iterator(n, _root, _nil), true);
                }

				void    _fixshiUp( pointer n )
				{
					pointer temp;

					while (n->parent->color == RED)
					{
						if (n->parent == n->parent->parent->right)
						{
							temp = n->parent->parent->left;
							if (temp->color == RED)
							{
								temp->color = BLACK;
								n->parent->color = BLACK;
								n->parent->parent->color = RED;
								n = n->parent->parent;
							}
							else
							{
								if (n == n->parent->left)
								{
									n = n->parent;
									rotateRight(n);
								}
								n->parent->color = BLACK;
								n->parent->parent->color = RED;
								rotateLeft(n->parent->parent);
							}
						}
						else
						{
							temp = n->parent->parent->right;
							if (temp->color == RED)
							{
								temp->color = BLACK;
								n->parent->color = BLACK;
								n->parent->parent->color = RED;
								n = n->parent->parent;
							}
							else
							{
								if (n == n->parent->right)
								{
									n = n->parent;
									rotateLeft(n);
								}
								n->parent->color = BLACK;
								n->parent->parent->color = RED;
								rotateRight(n->parent->parent);
							}
						}
						if (n == _root)
							break;
					}
					_root->color = BLACK;
				}

    //         ft::pair<iterator, bool>	__insert_node(const value_type &data) {
	// 	pointer look = search(data);
	// 	if (look)
	// 		return ft::make_pair(iterator(look, _root, _nil), false);

	// 	pointer node = __alloc_node(data);
    //     // std::cout << "Yu\n";
	// 	if (!node)
	// 		throw std::bad_alloc();

	// 	pointer y = _nil;
	// 	pointer x = _root;

	// 	while (x != _nil) {
	// 		y = x;
	// 		if (comp(data, x->data) > 0)
	// 			x = x->left;
	// 		else
	// 			x = x->right;
	// 	}

	// 	node->parent = y;
	// 	if (y == _nil)
	// 		_root = node;
	// 	else if (comp(node->data, y->data))
	// 		y->left = node;
	// 	else
	// 		y->right = node;

	// 	if (node->parent == _nil) {
	// 		node->color = BLACK;
	// 		return ft::make_pair(iterator(node, _root, _nil), true);
	// 	}

	// 	if (node->parent->parent == _nil)
	// 		return ft::make_pair(iterator(node, _root, _nil), true);

	// 	__insert_fixup(node);
	// 	return ft::make_pair(iterator(node, _root, _nil), true);
	// }
    // pointer __alloc_node(const value_type &data) {
	// 	pointer node = _allocator.allocate(1);

	// 	node->data = data;
    //     // std::cout << "Ui\n";
	// 	node->color = _nil;
	// 	node->left = _nil;
	// 	node->right = _nil;
	// 	node->parent = _nil;
	// 	++len;
	// 	return node;
	// }

    //             void	__insert_fixup(pointer node) {
	// 	pointer u;

	// 	while (node->parent->color == RED) {
	// 		if (node->parent == node->parent->parent->right) {
	// 			u = node->parent->parent->left;
	// 			if (u->color == RED) {
	// 				u->color = BLACK;
	// 				node->parent->color = BLACK;
	// 				node->parent->parent->color = RED;
	// 				node = node->parent->parent;
	// 			} else {
	// 				if (node == node->parent->left) {
	// 					node = node->parent;
	// 					rotateRight(node);
	// 				}
	// 				node->parent->color = BLACK;
	// 				node->parent->parent->color = RED;
	// 				rotateLeft(node->parent->parent);
	// 			}
	// 		} else {
	// 			u = node->parent->parent->right;
	// 			if (u->color == RED) {
	// 				u->color = BLACK;
	// 				node->parent->color = BLACK;
	// 				node->parent->parent->color = RED;
	// 				node = node->parent->parent;
	// 			} else {
	// 				if (node == node->parent->right) {
	// 					node = node->parent;
	// 					rotateLeft(node);
	// 				}
	// 				node->parent->color = BLACK;
	// 				node->parent->parent->color = RED;
	// 				rotateRight(node->parent->parent);
	// 			}
	// 		}

	// 		if (node == _root)
	// 			break;
	// 	}
	// 	_root->color = _nil;
	// }



                
                // pointer new_node( value_type value )
                // {
                //     pointer n = _allocator.allocate(1);
                
                //     n->data = value;
                //     n->left = NULL;
                //     n->right = NULL;
                //     return n;
                // }
                pointer new_node( const value_type &value )
                {
                    pointer n = _allocator.allocate(1);
                    // if (!_root)
                    n->parent = _nil;
                    // else
                    //     n->parent = _root;
                    n->left = _nil;
                    n->right = _nil;
                    n->color = RED;
                    n->data = value;
                    // std::cout << "LMACHAKIL!\n";
                    len++;
                    // rt = nl;
                    return n;
                }

                void new_empty_node()
                {
                    // _nil = _allocator.allocate(1);
                    // // if (!_root)
                    // _nil->parent = _nil;
                    // // else
                    // //     n->parent = _root;
                    // _nil->left = _nil;
                    // _nil->right = _nil;
                    // _nil->color = BLACK;
                    // _root = _nil;
                    // // rt = nl;
                    // // return n;
                    _nil = _allocator.allocate(1);

                    _nil->color = BLACK;
                    _nil->parent = _nil;
                    _nil->left = _nil;
                    _nil->right = _nil;
                    _root = _nil;
                }
            
            // deletion
                void erase( iterator pos )
                {
                    if (pos == end())
                        return;
                    delete_node(pos._node);
                }
                size_type erase( const value_type &value )
                {
                    pointer n = search(value);
                    
                    if (n)
                    {
						delete_node(n);
						return 1;
                    }
                    std::cout << "404 Not found\n";
                    return 0;
                }
                void erase( iterator first, iterator last )
                {
                    while (first != last)
                    {
                        erase(first++);
                        // ++first;
                    }
                }
                
                void	delete_node( pointer n )
                {
                    pointer x, y, z;
					bool original_color;
					pointer _temp_root = _root;
					
					while (_temp_root != _nil) // searching for the node of value
                    {
						// if (!comp(n->data, _temp_root->data))
						if (n->data == _temp_root->data)
							z = n;
						// if (comp(n->data, _temp_root->data) < 0)
						if (n->data > _temp_root->data)
							_temp_root = _temp_root->right;
						else
							_temp_root = _temp_root->left;
                    }
					
					if (!z) // value not found
						return;
					
					y = z;
					original_color = y->color;
					if (!z->right)
					{
						x = z->left;
						ft_transplant(z, z->left);
					}
					else if (!z->left)
					{
						x = z->right;
						ft_transplant(z, z->right);
					}
					else
					{
						y = min_element(z->right);
						original_color = y->color;
						x = y->right;
						if (y->parent == z)
							x->parent = y;
						else
						{
							ft_transplant(y, y->right);
							y->right = z->right;
							y->right->parent = y;
						}
						ft_transplant(z, y);
						y->left = z->left;
						y->left->parent = y;
						y->color = z->color;
					}
					_allocator.destroy(z);
					_allocator.deallocate(z, 1);
					len--;
					if (original_color == BLACK)// {}
						__fixshiUp(x);
                }
                
                void    __fixshiUp( pointer n )
                {
                    pointer temp;
                    
                    while (n != _root && n->color == BLACK)
                    {
						if (n == n->parent->left)
                        {
							temp = n->parent->right;
							if (temp->color == RED)
							{
								temp->color = BLACK;
								n->parent->color = RED;
								rotateLeft(n->parent);
								temp = n->parent->right;
							}

							if (temp->left->color == BLACK && temp->right->color == BLACK)
							{
								temp->color = RED;
								n = n->parent;
							}
							else
							{
								if (temp->right->color == BLACK)
								{
									temp->left->color = BLACK;
									temp->color = RED;
									rotateRight(temp);
									temp = n->parent->right;
								}
								
								temp->color = n->parent->color;
								n->parent->color = BLACK;
								temp->right->color = BLACK;
								rotateLeft(n->parent);
								n = _root;
							}
                        }
                        else
                        {
							temp = n->parent->left;
							if (temp->color == RED)
							{
								temp->color = BLACK;
								n->parent->color = RED;
								rotateRight(n->parent);
								temp = n->parent->left;
							}

							if (temp->right->color == BLACK && temp->right->color == BLACK)
							{
								temp->color = RED;
								n = n->parent;
							}
							else
							{
								if (temp->left->color == BLACK)
								{
									temp->right->color = BLACK;
									temp->color = RED;
									rotateLeft(temp);
									temp = n->parent->left;
								}
								
								temp->color = n->parent->color;
								n->parent->color = BLACK;
								temp->left->color = BLACK;
								rotateRight(n->parent);
								n = _root;
							}
                        }
                    }
					n->color = BLACK;
                }
                
            /*    pointer    delete_node( pointer root, value_type n )
                {
                    if (!root)
                        return root;
                    if (n->data > root->data)
                        root->right = delete_node(root->right, n);
                    else if (n->data > root->data)
                        root->left = delete_node(root->left, n);
                    else
                    {
                        if (!root->left)
                            return root->right;
                        else if (!root->right)
                            return root->left;
                        root->data = inOrderSuccessor(root->right);
                        root->right = delete_node(root->right, n);
                    }
                    return root;
                }
                void delete_node(*//*pointer root,*/ /*pointer n )
                {
                    if (n->color == BLACK)
                    {
                        if (n->right || n->left)
                        {   
                            if (n->right->color == RED)
                                n->right->color = BLACK;
                            else if (n->left->color == RED)
                                n->left->color = BLACK;
                            else
                            {
                                
                            }
                        }
                        else
                        {
                            //its leaf taht we wanna delete
                        }
                    }

                    
                    iterator it = find(value);
                    if (it == end())
                        return;
                    bool original_color = it->color;
                    pointer n = it->_node;
                    pointer x = NULL, y = NULL;
                    if (!n->left)
                    {
                        x = n->left;
                        transplate(n, n->left);
                    }
                    else if (!n->left)
                    {
                        x = n->right;
                        transplate(n, n->right);
                    }
                    else
                    {
                        y = min_element(n->right);
                        original_color = y->color;
                        x = y->right;
                        if (y->parent == n)
                            x->parent = y;
                        else
                        {
                            transplate(y, y->right);
                            y->right = n->right;
                            y->right->parent = y;
                        }
                    }
                }*/












    //             pointer	__min_node(pointer node) const {
	// 	while (node->left != _nil)
	// 		node = node->left;
	// 	return node;
	// }

    //         void	__rotate_left(pointer node) {
	// 	pointer tmp = node->right;

	// 	node->right = tmp->left;
	// 	if (tmp->left != _nil)
	// 		tmp->left->parent = node;

	// 	tmp->parent = node->parent;
	// 	if (node->parent == _nil)
	// 		_root = tmp;
	// 	else if (node == node->parent->left)
	// 		node->parent->left = tmp;
	// 	else
	// 		node->parent->right = tmp;
	// 	tmp->left = node;
	// 	node->parent = tmp;
	// }

	// void	__rotate_right(pointer node) {
	// 	pointer tmp = node->left;

	// 	node->left = tmp->right;
	// 	if (tmp->right != _nil)
	// 		tmp->right->parent = node;

	// 	tmp->parent = node->parent;
	// 	if (node->parent == _nil)
	// 		_root = tmp;
	// 	else if (node == node->parent->right)
	// 		node->parent->right = tmp;
	// 	else
	// 		node->parent->left = tmp;
	// 	tmp->right = node;
	// 	node->parent = tmp;
	// }

    //             void	__delete_fixup(pointer node) {
	// 	pointer s;

	// 	while (node != _root && node->color == BLACK) {
	// 		if (node == node->parent->left) {
	// 			s = node->parent->right;
	// 			if (s->color == RED) {
	// 				s->color = BLACK;
	// 				node->parent->color = RED;
	// 				__rotate_left(node->parent);
	// 				s = node->parent->right;
	// 			}
	// 			if (s->left->color == BLACK && s->right->color == BLACK) {
	// 				s->color = RED;
	// 				node = node->parent;
	// 			} else {
	// 				if (s->right->color == BLACK) {
	// 					s->left->color = BLACK;
	// 					s->color = RED;
	// 					__rotate_right(s);
	// 					s = node->parent->right;
	// 				}
	// 				s->color = node->parent->color;
	// 				node->parent->color = BLACK;
	// 				s->right->color = BLACK;
	// 				__rotate_left(node->parent);
	// 				node = _root;
	// 			}
	// 		} else {
	// 			s = node->parent->left;
	// 			if (s->color == RED) {
	// 				s->color = BLACK;
	// 				node->parent->color = RED;
	// 				__rotate_right(node->parent);
	// 				s = node->parent->left;
	// 			}
	// 			if (s->right->color == BLACK && s->left->color == BLACK) {
	// 				s->color = RED;
	// 				node = node->parent;
	// 			} else {
	// 				if (s->left->color == BLACK) {
	// 					s->right->color = BLACK;
	// 					s->color = RED;
	// 					__rotate_left(s);
	// 					s = node->parent->left;
	// 				}
	// 				s->color = node->parent->color;
	// 				node->parent->color = BLACK;
	// 				s->left->color = BLACK;
	// 				__rotate_right(node->parent);
	// 				node = _root;
	// 			}
	// 		}
	// 	}
	// 	node->color = BLACK;
	// }

	// void	delete_node(pointer node) {
	// 	if (node == NULL)
	// 		return;

	// 	pointer root = _root;
	// 	pointer z = _nil;

	// 	while (root != _nil) {
	// 		if (comp(node->data, root->data) == 0)
	// 			z = root;

	// 		if (comp(node->data, root->data) > 0)
	// 			root = root->left;
	// 		else
	// 			root = root->right;
	// 	}

	// 	if (z == _nil)
	// 		return;

	// 	pointer x;
	// 	pointer y = z;
	// 	bool y_original_color = y->color;
	// 	if (z->left == _nil) {
	// 		x = z->right;
	// 		__transplant(z, z->right);
	// 	} else if (z->right == _nil) {
	// 		x = z->left;
	// 		__transplant(z, z->left);
	// 	} else {
	// 		y = __min_node(z->right);
	// 		y_original_color = y->color;
	// 		x = y->right;
	// 		if (y->parent == z) {
	// 			x->parent = y;
	// 		} else {
	// 			__transplant(y, y->right);
	// 			y->right = z->right;
	// 			y->right->parent = y;
	// 		}
	// 		__transplant(z, y);
	// 		y->left = z->left;
	// 		y->left->parent = y;
	// 		y->color = z->color;
	// 	}
	// 	__destroy_node(z);
	// 	if (y_original_color == BLACK)
	// 		__delete_fixup(x);
	// }

	// void	__destroy_node(pointer n) {
	// 	_allocator.destroy(n);
	// 	_allocator.deallocate(n, 1);
	// 	--len;
	// }

    // void	__transplant(pointer u, pointer v) {
	// 	if (u->parent == _nil)
	// 		_root = v;
	// 	else if (u == u->parent->left)
	// 		u->parent->left = v;
	// 	else
	// 		u->parent->right = v;
	// 	if (v)
	// 		v->parent = u->parent;
	// }














				void	ft_transplant( pointer x, pointer y )
				{
					if (x->parent == _nil)
						_root = y;
					else if (x == x->parent->left)
						x->parent->left = y;
					else
						x->parent->right = y;
					if (y->parent != _nil) //       <<<<<<<<<<<<< HADI 3LAAAACH
						y->parent = x->parent;
				}
                
				void    rotateLeft( pointer n )
				{
					pointer temp = n->right;

					n->right = temp->left;
					if (temp->left != _nil)
						temp->left->parent = n;
					temp->parent = n->parent;
					if (n->parent == _nil)
						_root = temp;
					else if (n == n->parent->left)
						n->parent->left = temp;
					else
						n->parent->right = temp;
					temp->left = n;
					n->parent = temp;
				};

				void    rotateRight( pointer n )
				{
					pointer temp = n->left;

					n->left = temp->right;
					if (temp->right != _nil)
						temp->right->parent = n;
					temp->parent = n->parent;
					if (n->parent == _nil)
						_root = temp;
					else if (n == n->parent->right)
						n->parent->right = temp;
					else
						n->parent->left = temp;
					temp->right = n;
					n->parent = temp;
				};

                
                value_type successor( pointer n )
                {
                    value_type temp_data = n->data;

                    while (n->left != NULL)
                    {
                        n = n->left;
                        temp_data = n->left->data;
                    }
                    return temp_data;
                };

                
                // pointer insert_node()
                // {

                // }
            /*    void delete_node( pointer n )
                {
                    pointer temp_rt = rt, temp_nl = nl;

                    while (temp__root != nl)
                    {
                        if (n->data == temp_rt->data)
                            temp_nl = temp_rt;
                        else if (n->data > temp_rt->data)
                        {
                            temp_nl = temp_rt;
                            temp_rt = temp_rt->left;
                        }
                        else
                        {
                            temp_nl = temp_rt;
                            temp_rt = temp_rt->right;
                        }
                    }
                    if (temp_nl == nl)
                        return;
                    
                    // n->parent = temp_nl;
                    // if (nl == temp_nl)
                    //     rt = n;
                    // else if (n->data > temp_nl->data)
                    //     temp_nl->right = n;
                    // else
                    //     temp_nl->left = n;
                    // fixViolation(temp_rt, n);
                    // return ft::make_pair(iterator(rt, n, nl), true);
                }*/

            iterator find( const value_type &value )
            {
                pointer n = search(value);

                if (n)
                    return iterator(n, _root, _nil);
                std::cout << "not in here\n";
                return end();
            }
            const_iterator find( const value_type &value ) const
            {
                pointer n = search(value);

                if (n)
                    return const_iterator(n, _root, _nil);
                return end();
            }

            bool empty() const
            {
                if (!len)
                    return true;
                return false;
            }

            size_type size() const
            {
                return len;
            }

            size_type max_size() const
            {
                return _allocator.max_size();
            }

            void clear()
            {
            //    destroy_nodes(_root);
                _root = _nil;
                len = 0;
            }

            void    swap( RBtree &rbt )
            {
                std::swap(_allocator, rbt._allocator);
                std::swap(comp, rbt.comp);
                std::swap(_root, rbt._root);
                std::swap(_nil, rbt._nil);
                std::swap(len, rbt.len);
            }

            iterator lower_bound( const value_type &value )
		    {
                for (iterator it = begin(); it != end(); ++it) {
                    if (comp(it._node->data, value) == false)
                        return it;
                }
                return end();
		    };
		    const_iterator lower_bound( const value_type &value ) const
		    {
                for (const_iterator it = begin(); it != end(); ++it) {
                    if (comp(it._node->data, value) == false)
                        return it;
                }
                return end();
		    };

            iterator upper_bound( const value_type &value )
		    {
                for (iterator it = begin(); it != end(); ++it) {
                    if (comp(value, it._node->data))
                        return it;
                }
                return end();
		    };
		    const_iterator upper_bound( const value_type &value ) const
		    {
                for (const_iterator it = begin(); it != end(); ++it) {
                    if (comp(value, it._node->data))
                        return it;
                }
                return end();
		    };

            ft::pair<iterator,iterator> equal_range( const value_type &value )
		    {
                return ft::make_pair(lower_bound(value), upper_bound(value));
		    };
		    ft::pair<const_iterator,const_iterator> equal_range( const value_type& value ) const
		    {
                return ft::make_pair(lower_bound(value), upper_bound(value));
		    };

            //----  Utils
            pointer search(const value_type &value) const {
                pointer node = _root;

                int i=0;
                // while (i<len)
                while (node != _nil)
                {
                    // if (comp(value, node->data))
                    if (value == node->data)
                        return node;
                    else if (value < node->data)
                        node = node->left;
                    else
                        node = node->right;
                    i++;
                    // else if (comp(node->data, value))
                }
                std::cout << "o " << i << std::endl;
                return NULL;
            }

            pointer min_element( pointer n ) const
            {
                if (n->left == _nil)
                    return n;
                return min_element(n->left);
            };
    };
}

#endif