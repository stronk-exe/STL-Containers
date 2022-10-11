/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:44:51 by ael-asri          #+#    #+#             */
/*   Updated: 2022/10/10 13:44:53 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

template <typename T> class stack : public std::stack<T>
{
	public:
		stack() {};
		stack( const ft::stack &m ) { *this = m; };
		stack & operator=( const ft::stack &m ) { *this = m; return *this; };
		~stack() {};

		typedef typename ft::stack<T>::stack::container_type::iterator iterator;
		iterator begin() { return this->c.begin(); };
		iterator end() { return this->c.end(); };
};

#endif