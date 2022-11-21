/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:33:44 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/21 11:07:04 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include "vector.hpp"

namespace ft
{
	template <class T> struct iterator_traits
	{
		typedef typename	T::vlaue_type			value_type;
		typedef typename	T::difference_type		difference_type;
		typedef typename	T::iterator_category	iterator_category;
		typedef typename	T::pointer				pointer;
		typedef typename	T::reference			reference;
	};

	template <class T> struct iterator_traits<T*>
	{
		typedef	T							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	random_access_iterator_tag	iterator_category;
		typedef	T*							pointer;
		typedef	T&							reference;
	};

	template <class T> struct iterator_traits<const T*>
	{
		typedef	T									value_type;
		typedef	ptrdiff_t							difference_type;
		typedef	random_access_iterator_tag			iterator_category;
		typedef	const	T*							pointer;
		typedef	const	T&							reference;
	};
}

#endif