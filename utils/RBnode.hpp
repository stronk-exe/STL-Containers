/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBnode.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:00:40 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/09 19:44:45 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBNODE_HPP
#define RBNODE_HPP

#include <iostream>

namespace ft
{
    #define M_BLACK   0
    #define M_RED     1

    template<typename T> struct node
    {
        typedef T value_type;
        T		data;
        bool    color;
        node	*parent, *right, *left;

        node( const T &value ) : data(value), color(M_BLACK), parent(NULL), right(NULL), left(NULL) {};
    };
}

#endif