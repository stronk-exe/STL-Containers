/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBnode.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:40 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/21 12:27:22 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBNODE_HPP
#define RBNODE_HPP

namespace ft
{
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
}

#endif