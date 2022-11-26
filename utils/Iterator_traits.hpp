/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:33:44 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/21 18:15:19 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

// #include "vector.hpp"
// #include "../map/map.hpp"
// #include "Iterators.hpp"
// #include "utils.hpp"
#include <iostream>
#include <cstddef>

namespace ft
{

	struct input_iterator_tag { };

	struct output_iterator_tag { };

	struct forward_iterator_tag : public input_iterator_tag { };

	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <class Iterator> struct iterator_traits
	{
		typedef typename	Iterator::vlaue_type			value_type;
		typedef typename	Iterator::difference_type		difference_type;
		typedef typename	Iterator::iterator_category	iterator_category;
		typedef typename	Iterator::pointer				pointer;
		typedef typename	Iterator::reference			reference;
	};

	template <class T> struct iterator_traits<T*>
	{
		typedef	T							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	ft::random_access_iterator_tag	iterator_category;
		typedef	T*							pointer;
		typedef	T&							reference;
	};

	template <class T> struct iterator_traits<const T*>
	{
		typedef	T									value_type;
		typedef	ptrdiff_t							difference_type;
		typedef	ft::random_access_iterator_tag			iterator_category;
		typedef	const	T*							pointer;
		typedef	const	T&							reference;
	};
}

#endif