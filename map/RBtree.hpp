#ifndef RBTREE_HPP
#define RBTREE_HPP

template<typename T, typename Compare, typename Alloc=std::allocator<T> > class RBtree
{
	// public:
		// typedef node<T>	root;
		// typedef	typename Allocator::template rebind<node<T> >::other				allocator;
		// typedef	typename allocator::size_type	size_type;
		// allocator	_allocator;

    public:
			typedef	Key							key_type;
			typedef	T							value_type;
			// typedef	std::pair<const Key, T>		value_type;
            typedef node<T>                     nvalue_type;
            typedef const node<T>               const_nvalue_type;
			typedef	size_t						size_type;
			typedef	ptrdiff_t					difference_type;
			typedef	Compare						key_compare;
			typedef	Allocator					allocator_type;
			typedef	node<T>&							reference;
			typedef	const node<T>&					const_reference;
			typedef	node<T>*							pointer;
			typedef	const node<T>*					const_pointer;
			// typedef RDtree_Iterator<T>			iterator;
			// typedef RDtree_Iterator<const T >   const_iterator;
			// typedef RDtree_reverse_iterator<T>			reverse_iterator;
			// typedef RDtree_reverse_iterator<const T>	const_reverse_iterator;
	
	private:
		allocator_type	_allocator;
		Compare			comp;
		pointer			rt;
		pointer			nl;
		size_type		len;

	// protected:
	// 	void	rotateRight( node<T> *&, node<T> *& );
	// 	void	rotateLeft( node<T> *&, node<T> *& );
	// 	void	fixViolation( node<T> *&, node<T> *& );
	public:
		explicit RBtree( allocator_type alloc=allocator_type() )
		{
            _allocator = alloc;
            comp = key_compare();
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
            comp = key_compare();
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
        void new_rbt( pointer n, pointer _nl )
        {
            if (!node || !_nl)
                return;
            new_rbt(n->left, _nl);
            new_node(n->data);
            new_rbt(n->right, _nl);
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

        destroy_node( pointer n )
        {
            if (!n || n == nl)
                return;
            destroy_node(n->left);
            destroy_node(n->right);
            destroy_node(n);
        }







		void	insert( const T &n );
		node<T>	*search( T n );
		void	inorder();
		node<T>* const *root() const
		{
			return &rt;
		};
		node<T>* const nil() const
		{
			return nl;
		};
		// void	levelOrder();

		node<T> new_node( node<T> n )
		{
			node<T> temp = _allocator.allocate(1);
			_allocator.construct(temp, node(n));
			return temp;
		}
};

#endif