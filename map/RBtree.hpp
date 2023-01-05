/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:32 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/05 23:47:45 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "RBnode.hpp"
#include "RBiterators.hpp"
#include "../utils/reverse_iterator.hpp"
#include "../utils/pair.hpp"
#include "../utils/equal.hpp"
#include "../utils/enable_if.hpp"
#include "../utils/lexicographical_compare.hpp"

namespace ft
{
    template<typename T, typename Compare, typename Alloc=std::allocator<node<T> > > class RBtree
    {
        public:
                typedef	T							                    value_type;
                typedef node<T>                                         nvalue_type;
                typedef const node<T>                                   const_nvalue_type;
                typedef	size_t						                    size_type;
                typedef	T											    mapped_type;
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

        public:
            //----  Constructors
                explicit RBtree( allocator_type alloc=allocator_type() ) : _allocator(alloc), comp(compare_type()), _root(NULL), _nil(NULL), len(0)
                {
                    new_empty_node();
                };
                RBtree( const RBtree &other ) : _allocator(other._allocator), _root(NULL), _nil(NULL), len(0)
                {
                    new_empty_node();
                    copy_tree(other._root, other._nil);
                }
                RBtree &operator=( const RBtree &other )
                {
                    if (this != &other)
                    {
                        clear();
                        if (_nil != NULL)
                        {
                            _allocator.destroy(_nil);
                            _allocator.deallocate(_nil, 1);
                            _nil = NULL;
                        }
                        _allocator = other._allocator;
                        new_empty_node();
                        // len=other.len;
                        copy_tree(other._root, other._nil);
                    }
                    return *this;
                }
                void copy_tree(pointer node, pointer nil) {
                    if (node == NULL || node == nil)
                        return;
                    copy_tree(node->left, nil);
                    insert_node(node->data);
                    copy_tree(node->right, nil);
                }
                ~RBtree()
                {
                    clear();
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
                    return iterator(&_root, min_element(_root), _nil);
                }
                const_iterator begin() const
                {
                    return const_iterator(&_root, min_element(_root), _nil);
                }

                iterator end()
                {
                    return iterator(&_root, _nil, _nil);
                }
                const_iterator end() const
                {
                    return const_iterator(&_root, _nil, _nil);
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
            // insertion
                ft::pair<iterator, bool> insert( const value_type& value )
                {
                    return insert_node(value);
                }
                iterator insert( iterator pos, const value_type& value )
                {
                    (void)pos;
                    return insert(value).first;
                }
                template <class InputIterator> void insert(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = NULL)
                {
                    // for (; first != last; ++first)
                    while (first != last)
                        insert_node(*first++);
                }

            // deletion
                void erase( iterator pos )
                {
                    if (pos == end())
                        return;
                    delete_node(pos.get_itnode());
                }
                size_type erase( const value_type &value )
                {
                    pointer n = search(value);
                    
                    if (n)
                    {
						delete_node(n);
						return 1;
                    }
                    return 0;
                }
                void erase( iterator first, iterator last )
                {
                    while (first != last)
                        erase(first++);
                }
                
            // private:
                ft::pair<iterator, bool> insert_node(const value_type &value)
                {
                    pointer temp = search(value);
                    if (temp)
                        return ft::make_pair(iterator(&_root, temp, _nil), false);
                    
                    pointer n = new_node(value);
                    pointer _temp_root=_root, _temp_nil=_nil;
                    while (_temp_root != _nil)
                    {
                        _temp_nil = _temp_root;
                        if (comp(value, _temp_root->data)>0)
                            _temp_root = _temp_root->left;
                        else
                            _temp_root = _temp_root->right;
                    }
                    n->parent = _temp_nil;
                    if (_temp_nil == _nil)
                        _root = n;
                    else if (comp(n->data, _temp_nil->data))
                        _temp_nil->left = n;
                    else
                        _temp_nil->right = n;
					if (n->parent == _nil)
					{
						n->color = BLACK;
						return ft::make_pair(iterator(&_root, n, _nil), true);
					}
					if (n->parent->parent == _nil)
						return ft::make_pair(iterator( &_root, n, _nil), true);
                    fix_insertion(n);
                    return ft::make_pair(iterator(&_root, n, _nil), true);
                }

                

				void    fix_insertion( pointer n )
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
                // void printHelper(pointer root, std::string indent, bool last) {
                //     if (root != _nil) {
                //     std::cout << indent;
                //     if (last) {
                //         std::cout << "R----";
                //         indent += "   ";
                //     } else {
                //         std::cout << "L----";
                //         indent += "|  ";
                //     }

                //     std::string sColor = root->color ? "RED" : "BLACK";
                //     std::cout << root->data.first << "(" << sColor << ")" << std::endl;
                //     printHelper(root->left, indent, false);
                //     printHelper(root->right, indent, true);
                //     }
                // }
                // void printRBtree() {
                //     if (_root) {
                //         printHelper(_root, "", true);
                //     }
                // }

                pointer new_node( const value_type &value )
                {
                    pointer n = _allocator.allocate(1);
                    n->parent = _nil;
                    n->left = _nil;
                    n->right = _nil;
                    n->color = RED;
                    // n->data = value;
                    _allocator.construct(n, value);
                    len++;
                    return n;
                }

                void new_empty_node()
                {
                    _nil = _allocator.allocate(1);
                    _nil->color = BLACK;
                    _nil->parent = _nil;
                    _nil->left = _nil;
                    _nil->right = _nil;
                    _root = _nil;
                }
            
                
                void	delete_node( pointer n )
                {
                    pointer x, y, z=_nil;
					bool original_color;
					pointer _temp_root = _root;
					
					while (_temp_root != _nil) // searching for the node of value
                    {
						if (!comp(n->data, _temp_root->data))
						// if (n->data == _temp_root->data)
							z = _temp_root;
						if (comp(n->data, _temp_root->data) > 0)
						// if (n->data > _temp_root->data)
							_temp_root = _temp_root->left;
						else
							_temp_root = _temp_root->right;
                    }
					
					if (z == _nil) // value not found
						return;
					y = z;
					original_color = y->color;
					if (z->left == _nil) // no children or only right
					{
						x = z->right;
                        ft_transplant(z, z->right);
					}
					else if (z->right == _nil) // only left
					{
						x = z->left;
						ft_transplant(z, z->left);
					}
					else // both children
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
                    if (original_color == BLACK)
						fix_deletion(x);
                }
                
                void    fix_deletion( pointer n )
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

				void	ft_transplant( pointer x, pointer y )
				{
					if (x->parent == _nil) // x is the root
						_root = y;
					else if (x == x->parent->left) // y is the left child
						x->parent->left = y;
					else // y is the left child
						x->parent->right = y;
					// if (y) //       <<<<<<<<<<<<< HADI 3LAAAACH
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

            iterator find( const value_type &value )
            {
                pointer n = search(value);

                if (n)
                    return iterator(&_root, n, _nil);
                return end();
            }
            const_iterator find( const value_type &value ) const
            {
                pointer n = search(value);

                if (n)
                    return const_iterator(&_root, n, _nil);
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
                ft_destroy(_root);
                _root = _nil;
                len = 0;
            }
            void ft_destroy( pointer n )
            {
                if (n == NULL || n == _nil)
                    return;
                ft_destroy(n->left);
                ft_destroy(n->right);
                _allocator.destroy(n);
                _allocator.deallocate(n,1);
                len--;
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
                    if (comp(it.get_itnode()->data, value) == false)
                        return it;
                }
                return end();
		    };
		    const_iterator lower_bound( const value_type &value ) const
		    {
                for (const_iterator it = begin(); it != end(); ++it) {
                    if (comp(it.get_itnode()->data, value) == false)
                        return it;
                }
                return end();
		    };

            iterator upper_bound( const value_type &value )
		    {
                for (iterator it = begin(); it != end(); ++it) {
                    if (comp(value, it.get_itnode()->data))
                        return it;
                }
                return end();
		    };
		    const_iterator upper_bound( const value_type &value ) const
		    {
                for (const_iterator it = begin(); it != end(); ++it) {
                    if (comp(value, it.get_itnode()->data))
                        return it;
                }
                return end();
		    };

            ft::pair<iterator,iterator> equal_range( const value_type &value )
		    {
                // return ft::make_pair(lower_bound(value), upper_bound(value));
                iterator first=lower_bound(value), last=upper_bound(value);
                return ft::make_pair(first, last);
		    };
		    ft::pair<const_iterator,const_iterator> equal_range( const value_type& value ) const
		    {
                // return ft::make_pair(lower_bound(value), upper_bound(value));
                const_iterator first=lower_bound(value), last=upper_bound(value);
                return ft::make_pair(first, last);
		    };

            //----  Utils
            pointer search(const value_type &value) const {
                pointer node = _root;

                while (node != _nil)
                {
                    if (comp(value, node->data))
                    // if (value < node->data)
                        node = node->left;
                    // if (value == node->data)
                    else if (comp(node->data, value))
                    // else if (value > node->data)
                        node = node->right;
                    else
                        return node;
                }
                // std::cout << i << " Yiip\n";
                return NULL;
            }

            // pointer min_element( pointer n ) const
            // {
            //     std::cout << "nil " << _nil->data.first << std::endl;
            //     std::cout << "n " << n->data.first << std::endl;
            //     if (n->left == _nil)
            //         return n;
            //     return min_element(n->left);
            // };

            pointer min_element(pointer node) const {
                while (node->left != _nil)
                    node = node->left;
                return node;
            }
    };
}

#endif