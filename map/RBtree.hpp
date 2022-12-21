/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBtree.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:32 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/21 16:19:46 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include "RBnode.hpp"
#include "RBiterators.hpp"
// #include "../utils/vector_Iterators.hpp"
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
                typedef typename ft::Reverse_iterator<iterator>			reverse_iterator;
                typedef typename ft::Reverse_iterator<const_iterator>   const_reverse_iterator;
        
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
                    // _allocator = alloc;
                    // comp = compare_type();
                    // rt = NULL;
                    // nl = NULL;
                    // len = 0;
                    
                    // nl = _allocator.allocate(1);
                    // nl->parent = nl->right = nl->left = nl;
                    // nl->color = BLACK;
                    // rt = nl;
                    new_empty_node();
                    


                    // pointer n = _allocator.allocate(1);
                    // n->parent = n;
                    // n->right = n;
                    // n->left = n;
                    // n->color = RED;
                    // _root = n;
                };
                RBtree( const RBtree &other ) : _allocator(other._allocator), comp(compare_type()), _root(NULL), _nil(NULL), len(0)
                {
                    // _allocator = other.alloc;
                    // comp = compare_type();
                    // rt = NULL;
                    // nl = NULL;
                    // len = 0;
                    // pointer n = _allocator.allocate(1);
                    // n->parent = n;
                    // n->right = n;
                    // n->left = n;
                    // n->color = BLACK;
                    // nl = _allocator.allocate(1);
                    // nl->parent = nl->right = nl->left = nl;
                    // nl->color = BLACK;
                    // rt = nl;
                    // rt = nl;
                    new_empty_node();
                    // len++;
                    rbt(other.rbt);
                //    new_rbt(other.rt, other.nl);
                }
                RBtree &operator=( const RBtree &other )
                {
                    if (*this != other)
                    {
                        clear();
                        _allocator.destroy(*this);
                        _allocator.deallocate(*this, 1);
                        _allocator = other._allocator;
                        // nl = _allocator.allocate(1);
                        // nl->parent = other->parent;
                        // nl->right = other->right;
                        // nl->left = other->left;
                        // nl->color = BLACK;
                        _root = new_node(_root->data);
                        // _root = nl;
                        rbt(other.rbt);
                     //   new_rbt(other.rt, other.nl);
                    }
                    return *this;
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
                    return iterator(_root, min_element(_root), _nil);
                }
                const_iterator begin() const
                {
                    return const_iterator(_root, min_element(_root), _nil);
                }

                iterator end()
                {
                    return iterator(_root, _nil, _nil);
                }
                const_iterator end() const
                {
                    return const_iterator(_root, _nil, _nil);
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
                    // pointer temp_n = new_node(value), temp_rt = rt, temp_nl = nl;

                    // while (temp_rt != nl)
                    // {
                    //     if (value > temp_rt->data)
                    //     {
                    //         temp_nl = temp_rt;
                    //         temp_rt = temp_rt->left;
                    //     }
                    //     else
                    //     {
                    //         temp_nl = temp_rt;
                    //         temp_rt = temp_rt->right;
                    //     }
                    // }
                    // n->parent = temp_nl;
                    // if (nl == temp_nl)
                    //     rt = n;
                    // else if (n->data > temp_nl->data)
                    //     temp_nl->right = n;
                    // else
                    //     temp_nl->left = n;
                    // fixViolation(temp_rt, n);
                    // return ft::make_pair(iterator(rt, n, nl), true);
                    // pointer n = new_node(value);
                    _root = insert_node(value);
                    // fixViolation(_root, n);
                    // std::cout << n->data << std::endl;
                    iterator it = find(value);
                    return ft::make_pair(it, true);
                    // return insert_node(rt, value);
                }
                iterator insert( iterator pos, const value_type& value )
                {
                    (void)pos;
                    // return insert_node(value).first;
                    return iterator(insert_node(value));
                }
                template<class InputIt> void insert( InputIt first, InputIt last/*, typename ft::enable_if<!ft::is_integral<InputIt>::value>::type *= NULL*/ )
                {
                    while (first != last)
                    {
                        insert_node(*first);
                        *first++;
                    }
                }
            /*    pointer insert_node( node &*n, const value_type value )
                {
                    node<value_type> *n;
                    n->data = value;
                    if (!rt)
                        return n->right;
                    if (n->data > rt->data)
                    {
                        rt->right = insert_node(rt->right, n->data);
                        rt->right->parent = rt;
                    }
                    else if (n->data < rt->data)
                    {
                        rt->left = insert_node(rt->left, n);
                        rt->left->parent = rt;
                    }
                    fixViolation(rt, n);
                    return rt;
                };*/

            /*    pointer insert_node( pointer root, pointer n )
                {
                    // if the root is null, create a new node and return it
                    if (!root)
                        return n;
                
                    // if the given key is less than the root node, recur for the left subtree
                    if (n->data < root->data)
                    {
                        // std::cout << "sew< " << std::endl;
                        root->left = insert_node(root->left, n);
                        root->left->parent = root;
                    }
                    // if the given key is more than the root node, recur for the right subtree
                    else
                    {
                        // std::cout << "sew> " << std::endl;
                        root->right = insert_node(root->right, n);
                        root->right->parent = root;
                    }
                    // return ft::make_pair(iterator(root), true);
                    return root;
                }*/

                pointer insert_node(/*pointer root,*/ value_type value)
                {
                    pointer n = new_node(value);
                    
                    pointer _temp_root=_root, _temp_nil=_nil;
                    while (_temp_root != _nil)
                    {
                        _temp_nil = _temp_root;
                        if (value < _temp_root->data)
                            _temp_root = _temp_root->left;
                        else
                            _temp_root = _temp_root->right;
                    }
                    n->parent = _temp_nil;
                    if (_temp_nil == _nil)
                        _root = n;
                    else if (value < _temp_nil->data)
                        _temp_nil->left = n;
                    else
                        _temp_nil->right = n;
                    return n;



                    
              /*      // std::cout << n->data << std::endl;
                    if (!_root)
                    // if (!len)
                    {
                        _root = n;
                        len++;
                        return n;
                    }
                    // root = NULL;
                    pointer prev = NULL;
                    pointer temp = _root;
                    // std::cout << "yy\n";
                    while (temp)
                    {
                        if (temp->data > value) {
                            prev = temp;
                            temp = temp->left;
                        }
                        else if (temp->data < value) {
                            prev = temp;
                            temp = temp->right;
                        }
                        // std::cout << "sewiii<" << std::endl;
                    }
                    if (prev->data > value)
                        prev->left = n;
                    else
                        prev->right = n;
                    // if (!prev->parent->right || !prev->parent->left)
                    //     len++;
                    fixViolation(_root, n);
                    return _root;*/
                }


                
                // pointer new_node( value_type value )
                // {
                //     pointer n = _allocator.allocate(1);
                
                //     n->data = value;
                //     n->left = NULL;
                //     n->right = NULL;
                //     return n;
                // }
                pointer new_node( value_type value )
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
                    len++;
                    // rt = nl;
                    return n;
                }

                void new_empty_node()
                {
                    _nil = _allocator.allocate(1);
                    // if (!_root)
                    _nil->parent = _nil;
                    // else
                    //     n->parent = _root;
                    _nil->left = _nil;
                    _nil->right = _nil;
                    _nil->color = BLACK;
                    _root = _nil;
                    // rt = nl;
                    // return n;
                }
            
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
                        erase(n);
                        return 1;
                    }
                    return 0;
                }
                void erase( iterator first, iterator last )
                {
                    while (first != last)
                    {
                        delete_node(*first);
                        *first++;
                    }
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
                }*/
                void delete_node(/*pointer root,*/ value_type value)
                {
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
                }
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
                    return iterator(_root, n, _nil);
                return end();
            }
            const_iterator find( const value_type &value ) const
            {
                pointer n = search(value);

                if (n)
                    return const_iterator(_root, n, _nil);
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
		    	// return rbt.lower_bound();
                iterator it = find(value);
                if (it == begin())
                    return begin();
                // else if (++it == end())
                //     return --it;
                return --it;
		    };
		    const_iterator lower_bound( const value_type &value ) const
		    {
		    	// return rbt.lower_bound();
                const_iterator it = find(value);
                if (it == begin())
                    return begin();
                // else if (++it == end())
                //     return --it;
                return --it;
		    };

            iterator upper_bound( const value_type &value )
		    {
		    	// return rbt.lower_bound();
                iterator it = find(value);
                if (it == end())
                    return end();
                // else if (--it == end())
                //     return ++it;
                return ++it;
		    };
		    const_iterator upper_bound( const value_type &value ) const
		    {
		    	// return rbt.lower_bound();
                const_iterator it = find(value);
                if (it == end())
                    return end();
                // else if (--it == end())
                //     return ++it;
                return ++it;
		    };

            ft::pair<iterator,iterator> equal_range( const value_type &value )
		    {
		    	// return rbt.equal_range();
                iterator it = lower_bound(value);
                // while (it != upper_bound(value))
                // {
                //     ft::make_pair(value);
                //     i++;
                // }
                return make_pair(it, upper_bound(value));
		    };
		    ft::pair<const_iterator,const_iterator> equal_range( const value_type& value ) const
		    {
		    	// return rbt.equal_range();
                const_iterator it = lower_bound(value);
                return make_pair(it, upper_bound(value));
		    };

            //----  Utils
        /*    void new_rbt( pointer n, pointer _nl )
            {
                if (!n || !_nl)
                    return;
                new_rbt(n->left, _nl);
                new_node(n->data);
                new_rbt(n->right, _nl);
            }*/

        /*    void destroy_node( pointer n )
            {
                if (!n || n == _nil)
                    return;
                destroy_node(n->left);
                destroy_node(n->right);
                destroy_node(n);
            }*/

            pointer search( const value_type &value ) const
            {
                pointer n = _root;

                while (n != _nil)
                {
                    if (comp(value, n->data))
                        n = n->left;
                    if (!comp(value, n->data))
                        n = n->right;
                    else
                        return n;
                }
                return NULL;
            }

            pointer min_element( pointer n )
            {
                if (n->left != _nil)
                    return n;
                return min_element(n->left);
            };

            // Fix Violation function
            void    rotateLeft( pointer &root, pointer &n )
            {
                pointer temp = n->right;

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

            void    rotateRight( pointer &root, pointer &n )
            {
                pointer temp = n->left;

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

            void	fixViolation( pointer &root, pointer &n )
            {
                pointer temp_parent = NULL, temp_gparent = NULL, temp_uncle;

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





            // void	insert( const T &n );
            // node<T>	*search( T n );
            // void	inorder();
            // node<T>* const *root() const
            // {
            // 	return &rt;
            // };
            // node<T>* const nil() const
            // {
            // 	return nl;
            // };
            // void	levelOrder();

            // node<T> new_node( node<T> n )
            // {
            // 	node<T> temp = _allocator.allocate(1);
            // 	_allocator.construct(temp, node(n));
            // 	return temp;
            // }
    };
}

#endif