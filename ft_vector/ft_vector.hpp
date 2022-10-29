/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:23:00 by ael-asri          #+#    #+#             */
/*   Updated: 2022/10/29 16:31:07 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>

namespace ft
{
	template <class T, class Allocator = std::allocator<T> > class vector
	{
		// definin
		typedef T				value_type;
		typedef T*				pointer;
		typedef T&				reference;
		typedef const T*		const_pointer;
		typedef const T&		const_reference;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;
		typedef Allocator		allocator_type;
		// typedef	typename vector<T>::iterator		iterator;

		private:
			size_type	n;
			T			*v;
		public:
			// Member functions
				//----	Constractors
					// default constactor
					explicit vector (const allocator_type& alloc = allocator_type())
					{
						n = 0;
						// (void)alloc;
					//	v = new T[n];
						v = alloc.allocate(n);
						std::cout << "vector default constractor called!" << std::endl;
					};

					// fill constractor
					explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
					{
						this->n = n;
						// (void)alloc;
						 v = alloc.allocate(n);
						// v = new T[n];
						for (size_type i=0; i<n; i++)
						{
							v[i] = val;
							std::cout << v[i] << std::endl;
						}
						std::cout << "vector fill constractor called!" << std::endl;
					};

					// range constractor
					template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
					{
						int i=0;
						while (first != last)
						{
							v[i] = *first;
							std::cout << v[i] << std::endl;
							i++;
						}
						std::cout << "vector range constractor called!" << std::endl;
					};

					// copy constractor
					vector (const vector& x)
					{
						*this = x;
						for (size_type i=0; i<this->n; i++)
						{
							std::cout << this->v[i] << std::endl;
						}
						std::cout << "vector copy constractor called!" << std::endl;
					};

					// deconstractor
					~vector()
					{
						std::cout << "vector Deconstractor called!" << std::endl;
					};

					// operator=
					vector& operator=(const vector& x) {};

				//----	Iterators
					// begin
					iterator begin() {};
					const_iterator begin() const {};

					// end
					iterator end() {};
					const_iterator	end() const {};

					// rbegin
					reverse_iterator	rbegin() {};
					const_reverse_iterator	rbegin() const {};

					// rend
					reverse_iterator	rend() {};
					reverse_iterator	rend() const {};

					// cbegin
					const_iterator	cbegin() const {};

					// cend
					const_iterator	cend() const {};

					// crbegin
					const_reverse_iterator	crbegin() const {};

					// crend
					const_reverse_iterator	crend() const {};

				//----	Capacity
					// size
					size_type	size() const
					{
						for(size_t i=0; v[i] != NULL; i++)
							;
						return i;
					};

					// max_size
					size_type	max_size() const {};

					// resize
					void	resize(size_type n, value_type val = value_type())
					{
						if (n<this->n)
						{
							size_type i;
							for (i=0; i<n; i++)
								;
							for (i=0; i<n; i++)
							{
								delete[v[i]];
							}
							this->n = n;
						}
						else
						{
							size_type i=v.size();
							for (i=0; i<n; i++)
							{
								v.push_back(val);
							}
							this->n = n;
						}
					};

					// capacity
					size_type	capacity() const {};

					// empty
					bool	empty() const
					{
						if (!v.size())
							return true;
						return false;
					};

					// reserve
					void	reserve(size_type n)
					{
						if (n > v.capacity())
						{
							v.capacity() = this->n;
						}
					};

					// shrink_to_fit
					void	shrink_to_fit()
					{
						v.capacity() = c.size();
					};

				//----	Element access
					// operator[]
					reference	operator[](sizt_type n) {};
					const_reference	operator[](size_type n) const {};

					// at
					reference	at(size_type n)
					{
						return &v[n];
					};
					const_reference	at(size_type n) const
					{
						return &v[n];
					};

					// front
					reference	front() {};
					const_reference	front() const;

					// back
					reference	back() {};
					const_reference	back() const {};

					// data
					value_type*	data() {};
					value_type*	data() const {};

				//----	Modifiers
					// assigne
					void	assigne(size_type n, const value_type& val) {};
					// push_back
					void	push_back(const value_type& val) {};
					// pop_back
					void	pop_back() {};
					// insert
					iterator	insert(iterator position, const value_type& val) {};
					void	insert(iterator position, size_type n, const_value_type& val) {};
					template <class InputIterator>void	insert(iterator position, InputIterator first, InputIterator last) {};
					// erase
					iterator	erase(iterator position) {};
					iterator	erease(iterator first, iterator last) {};
					// swap
					void	swap(vector& x) {};
					// clear
					void	clear() {};
					// emplace
					template <class... Args>iterator emplace(const_iterator position, Args&&... args) {};
					
					// emplace_back
					template <class... Args>void	emplace_back(Args&&... args) {};
					

				//----	Allocator
					// get_allocator
					allocator_type	get_allocator() const
					{
						return this->allocate;
					};
	};
}

#endif