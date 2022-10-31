/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:23:00 by ael-asri          #+#    #+#             */
/*   Updated: 2022/10/31 18:47:26 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <iostream>
#include "Iterator_traits.hpp"
#include "reverse_iterator.hpp"

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
					vector& operator=(const vector& x)
					{
						v = x;
					};

				//----	Iterators
					// begin
					iterator begin()
					{
						return iterator(*this, 0);
					};
					const_iterator begin() const
					{
						return iterator(*this, 0);
					};

					// end
					iterator end()
					{
						return iterator(*this, v.size());
					};
					const_iterator	end() const
					{
						return const_iterator(*this, v.size());
					};

					// rbegin
					reverse_iterator	rbegin()
					{
						return reverse_iterator(*this, 0);
					};
					const_reverse_iterator	rbegin() const
					{
						return const_reverse_iterator(*this, 0);
					};

					// rend
					reverse_iterator	rend()
					{
						return reverse_iterator(*this, v.size());
					};
					reverse_iterator	rend() const
					{
						return reverse_iterator(*this, v.size());
					};

					// cbegin
					const_iterator	cbegin() const
					{
						return const_iterator(*this, 0);
					};

					// cend
					const_iterator	cend() const
					{
						return const_iterator(*this, v.size());
					};

					// crbegin
					const_reverse_iterator	crbegin() const
					{
						return const_reverse_iterator(*this, 0);
					};

					// crend
					const_reverse_iterator	crend() const
					{
						return const_reverse_iterator(*this, v.size());
					};

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
								delete v[i];
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
					reference	operator[](sizt_type n)
					{
						if (n<0 || n>this->n)
							throw invalidIndex();
						return v[n];
					};
					const_reference	operator[](size_type n) const
					{
						if (n<0 || n>this->n)
							throw invalidIndex();
						return v[n];
					};

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
					reference	front()
					{
						return *v;
					};
					const_reference	front() const
					{
						return *v;
					};

					// back
					reference	back()
					{
						while (v->next != NULL)
							v = v->next;
						return *v;
					};
					const_reference	back() const
					{
						while (v->next != NULL)
							v = v->next;
						return *v;
					};

					// data
					value_type*	data() {};
					value_type*	data() const {};

				//----	Modifiers
					// assigne
					template <class InputIterator>void	assigne(InputIterator first, InputIterator last) {};
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
					void	swap(vector& x) 
					{
						while (x != NULL)
						{
							v[i] = x[i];
							x = x->next;
						}
					};
					// clear
					void	clear()
					{
						while (v != NULL)
						{
							delete v[i];
							v = v->next;
						}
						this->n = 0;
					};
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