/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:23:00 by ael-asri          #+#    #+#             */
/*   Updated: 2022/10/11 16:20:07 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> > class ft_vector
	{
		private:
			int	n;
			T	*v;
		public:
			// Member functions
				// -- Constructors
					explicit ft_vector ( const T& alloc = T() )	
					{
						n = 0;
						(void)alloc;
						v = new T[n];
						// v = alloc.allocate(n);
						std::cout << "vector default constractor called!" << std::endl;
					};	// default constactor
					explicit ft_vector (
						int n, const T& val = T(), 
						const T& alloc = T())
					{
						this->n = n;
						(void)alloc;
						//  v = alloc.allocate(n);
						v = new T[n];
						for (int i=0; i<n; i++)
						{
							v[i] = val;
							std::cout << v[i] << std::endl;
						}
						std::cout << "vector fill constractor called!" << std::endl;
					};	// fill constractor
			/*		template <class InputIterator> ft_vector (
						InputIterator first, InputIterator last,
						const T& alloc = T())
					{
						int i=0;
						while (first != last)
						{
							v[i] = *first;
							std::cout << v[i] << std::endl;
							i++;
						}
						std::cout << "vector range constractor called!" << std::endl;
					};	// range constractor
			*/		ft_vector (const ft_vector& v)
					{
						*this = v;
						for (int i=0; i<this->n; i++)
						{
							std::cout << this->v[i] << std::endl;
						}
						std::cout << "vector copy constractor called!" << std::endl;
					};					// copy constractor

				// -- Deconstructors
					~ft_vector()
					{
						std::cout << "vector Deconstractor called!" << std::endl;
					};		/*										// deconstractor

				// -- Operator=
					vector& operator= (const vector& x);	*/				// copy assignement operator

	/*		// Iterators
			begin
			end
			rbegin
			rend
			cbegin
			cend
			crbegin
			crend

			// Capacity
			size
			max_size
			resize
			capacity
			empty
			reserve
			shrink_to_fit

			// Element access
			operator[]
			at
			front
			back
			data

			// Modifiers
			assign
			push_back
			pop_back
			insert
			erase
			swap
			clear
			emplace
			emplace_back

			// Allocator
			get_allocator*/
	};
}

#endif