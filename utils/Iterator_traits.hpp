/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:33:44 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/09 19:44:58 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
#define ITERATOR_TRAITS_HPP

#include <iterator>
#include <iostream>
#include <cstddef>

namespace ft
{

	struct input_iterator_tag { };

	struct output_iterator_tag { };

	struct forward_iterator_tag : public input_iterator_tag { };

	struct bidirectional_iterator_tag : public forward_iterator_tag { };

	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <class iterator> class iterator_traits
	{
		public:
			typedef typename	iterator::difference_type		difference_type;
			typedef typename	iterator::value_type			value_type;
			typedef typename	iterator::iterator_category		iterator_category;
			typedef typename	iterator::pointer				pointer;
			typedef typename	iterator::reference				reference;
	};

	template <class T> class iterator_traits<T*>
	{
		public:
			typedef	T								value_type;
			typedef	ptrdiff_t						difference_type;
			typedef	ft::random_access_iterator_tag	iterator_category;
			typedef	T*								pointer;
			typedef	T&								reference;
	};

	template <class T> class iterator_traits<const T*>
	{
		public:
			typedef	T									value_type;
			typedef	ptrdiff_t							difference_type;
			typedef	ft::random_access_iterator_tag		iterator_category;
			typedef	const	T*							pointer;
			typedef	const	T&							reference;
	};
}

#endif