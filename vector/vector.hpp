/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 18:50:08 by ael-asri          #+#    #+#             */
/*   Updated: 2022/09/03 10:49:35 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

template <class T, class Allocator = std::allocator<T>> class vector
{
	public:
		vector() {};
	//	vector( const vector &v ) { *this = v };
		vector & operator=( const vector &v ) { *this = v; return *this; };
		~vector() {};
		
		typedef typename vector<T>::vecor
		end();
};

#endif