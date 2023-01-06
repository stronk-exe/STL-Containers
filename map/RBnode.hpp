/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBnode.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:40 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/06 15:56:37 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBNODE_HPP
#define RBNODE_HPP

#include <iostream>

namespace ft
{
    #define BLACK   0
    #define RED     1

    template<typename T> struct node
    {
        typedef T value_type;
        T		data;
        bool    color;
        node	*parent, *right, *left;

        node( const T &value ) : data(value), color(BLACK), parent(NULL), right(NULL), left(NULL) {};
    };
}

#endif