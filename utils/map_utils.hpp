/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:20:30 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/09 11:48:31 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_UTILS_HPP
#define MAP_UTILS_HPP

template <typename T> class node
{
	T		value;
	node	*parent;
	node	*right;
	node	*left;
	int		color;

	// node() : parent(0), left(0), right(0) {};
	// node( T &n ) : value(p), parent(0), left(0), right(0) {};
};

template <typename T> RB_Tree()
{

};
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

#endif