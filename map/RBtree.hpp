#ifndef RBTREE_HPP
#define RBTREE_HPP

namespace ft
{
    template<typename T, typename Compare, typename Alloc=std::allocator<T> > class RBtree
    {
        // public:
            // typedef node<T>	root;
            // typedef	typename Allocator::template rebind<node<T> >::other				allocator;
            // typedef	typename allocator::size_type	size_type;
            // allocator	_allocator;

        public:
                // typedef	Key							key_type;
                typedef	T							value_type;
                // typedef	std::pair<const Key, T>		value_type;
                typedef node<T>                     nvalue_type;
                typedef const node<T>               const_nvalue_type;
                typedef	size_t						size_type;
                typedef	ptrdiff_t					difference_type;
                typedef	Compare						compare_type;
                typedef	Allocator					allocator_type;
                typedef	node<T>&							    reference;
                typedef	const node<T>&					        const_reference;
                typedef	node<T>*							    pointer;
                typedef	const node<T>*					        const_pointer;
                typedef ft::RDtree_Iterator<nvalue_type>        iterator;
                typedef ft::RDtree_Iterator<const nvalue_type>  const_iterator;
                typedef ft::reverse_iterator<iterator>			reverse_iterator;
                typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;
        
        private:
            allocator_type	_allocator;
            compare_type    comp;
            pointer			rt;
            pointer			nl;
            size_type		len;

        // protected:
        // 	void	rotateRight( node<T> *&, node<T> *& );
        // 	void	rotateLeft( node<T> *&, node<T> *& );
        // 	void	fixViolation( node<T> *&, node<T> *& );
        public:
            //----  Constructors
            explicit RBtree( allocator_type alloc=allocator_type() )
            {
                _allocator = alloc;
                comp = compare_type();
                // rt = NULL;
                nl = NULL;
                len = 0;
                n = _allocator.allocate(1);

                n->parent = n;
                n->right = n;
                n->left = n;
                n->color = BLACK;
                rt = n;

            };
            RBtree( const RBtree &other )
            {
                _allocator = other.alloc;
                comp = compare_type();
                // rt = NULL;
                // nl = NULL;
                // len = 0;
                nl = _allocator.allocate(1);
                nl->parent = n;
                nl->right = n;
                nl->left = n;
                nl->color = BLACK;
                rt = nl;
                len++;
                new_rbt(other.rt, other.nl);
            }
            RBtree &operator=( const RBtree &other )
            {
                if (this != &other)
                {
                    clear();
                    _allocator.destroy(n);
                    _allocator.deallocate(n, 1);
                    _allocator = other._allocator;
                    nl = _allocator.allocate(1);
                    nl->parent = n;
                    nl->right = n;
                    nl->left = n;
                    nl->color = BLACK;
                    rt = nl;
                    new_rbt(other.rt, other.nl);
                }
                return *this;
            }
            ~RBtree()
            {
                clear();
                // destroy_node();
                if (nl)
                {
                    _allocator.destroy(nl);
                    _allocator.deallocate(nl, 1);
                    nl = NULL;
                }
            }

            //----  Iterators

                iterator begin()
                {
                    return iterator(rt, min_element(rt), nl);
                }
                const_iterator begin() const
                {
                    return const_iterator(rt, min_element(rt), nl);
                }

                iterator end()
                {
                    return iterator(rt, nl, nl);
                }
                const_iterator end() const
                {
                    return const_iterator(rt, nl, nl);
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
                pointer temp_n = new_node(value), temp_rt = rt, temp_nl = nl;

                while (temp_rt != nl)
                {
                    if (value > temp_rt->data)
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
                n->parent = temp_nl;
                if (nl == temp_nl)
                    rt = n;
                else if (n->data > temp_nl->data)
                    temp_nl->right = n;
                else
                    temp_nl->left = n;
                fixViolation(temp_rt, n);
                return ft::make_pair(iterator(rt, n, nl), true);
            }
        /*    iterator insert( iterator pos, const value_type& value )
            {

            }*/
            
            void erase( iterator pos )
            {
                if (pos == end())
                    return;
                delete_node(pos._node);
            }
            pointer insert_node()
            {

            }
            void delete_node( pointer n )
            {
                pointer temp_rt = rt, temp_nl = nl;

                while (temp_rt != nl)
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
            }

            iterator find( const value_type& value )
            {
                pointer n = search(value);

                if (n)
                    return iterator(rt, n, nl);
                return end();
            }
            const_iterator find( const value_type& value ) const
            {
                pointer n = search(value);

                if (n)
                    return const_iterator(rt, n, nl);
                return end();
            }

            bool empty() const
            {
                if (!len)
                    return true
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
                destroy_nodes(rt);
                rt = nl;
                len = 0;
            }
            void    swap( RBtree &rbt )
            {
                std::swap(_allocator, rbt._allocator);
                std::swap(comp, rbt.comp);
                std::swap(rt, rbt.rt);
                std::swap(nl, rbt.nl);
                std::swap(lwn, rbt.len);
            }

            //----  Utils
            void new_rbt( pointer n, pointer _nl )
            {
                if (!node || !_nl)
                    return;
                new_rbt(n->left, _nl);
                new_node(n->data);
                new_rbt(n->right, _nl);
            }

            destroy_node( pointer n )
            {
                if (!n || n == nl)
                    return;
                destroy_node(n->left);
                destroy_node(n->right);
                destroy_node(n);
            }

            pointer search( const value_type &value ) const
            {
                pointer n = rt;

                while (n != nl)
                {
                    if comp(value, n->data);
                        n = n->left;
                    if !comp(value, n->data);
                        n = n->right;
                    else
                        return n;
                }
                return NULL;
            }

            pointer min_element( pointer n )
            {
                if (n->left != nl)
                    return n;
                return min_element(n->left);
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