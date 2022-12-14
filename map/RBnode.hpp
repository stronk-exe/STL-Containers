#ifndef RBNODE_HPP
#define RBNODE_HPP

enum Color { RED, BLACK };

template<typename T> struct node
{
	T		data;
	bool	color;
	node	*parent, *right, *left;

	node( const T &value ) : data(value)
	{
		// data = value;
		// parent = right = left = NULL;
		// color = RED;
	};
};

#endif