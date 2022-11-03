/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:23:00 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/03 17:12:57 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
// #include "Iterator_traits.hpp"
// #include "reverse_iterator.hpp"

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
			size_type		n;
			size_type		len;
			T				*v;
			Allocator		_allocator;
			// InputIterator	first;
			// InputIterator	last;
		public:
			// Member functions
				//----	Constractors
					// default constactor
					explicit vector (const allocator_type& alloc = allocator_type()) : len(0), _allocator(alloc)
					{
						// len = 0;
						// (void)alloc;
					//	v = new T[n];
						// _allocator = alloc;
						v = _allocator.allocate(len);
						// v = alloc;
						// len = 0;
						// v = new T[len];
						std::cout << "vector default constractor called!" << std::endl;
					};

					// fill constractor
					explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : len(n), _allocator(alloc)
					{
						// this->n = n;
						// (void)alloc;
						 v = _allocator.allocate(len);
						// v = new T[n];
						for (size_type i=0; i<len; i++)
						{
							v[i] = val;
							// std::cout << v[i] << std::endl;
						}
						std::cout << "vector fill constractor called!" << std::endl;
					};

			/*		// range constractor
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

			*/		// copy constractor
					vector (const vector& x) : len(x.len), v(x.v)
					{
						// len = x.len;
						// v = x.v;
						// for (size_type i=0; i<len; i++)
						// {
						// 	std::cout << v[i] << std::endl;
						// }
						std::cout << "vector copy constractor called!" << std::endl;
					};

					// deconstractor
					~vector()
					{
						// _allocator.dealocate();
						std::cout << "vector Deconstractor called!" << std::endl;
					};

					// operator=
					vector& operator=(const vector& x)
					{
						len = x.len;
						v = x.v;
						return *this;
					};

		/*		//----	Iterators
					// begin
					iterator begin()
					{
						// return iterator(*this, 0);
						return {iterator::*this, 0};
					};
					const_iterator begin() const
					{
						// return iterator(*this, 0);
						return {const_iterator::*this, 0};
					};

					// end
					iterator end()
					{
						// return iterator(*this, v.size());
						return {iterator::*this, len};
					};
					const_iterator	end() const
					{
						// return const_iterator(*this, v.size());
						return {const_iterator::*this, len};
					};

					// rbegin
					reverse_iterator	rbegin()
					{
						// return reverse_iterator(*this, 0);
						return {reverse_iterator:*this, 0};
					};
					const_reverse_iterator	rbegin() const
					{
						// return const_reverse_iterator(*this, 0);
						return {const_reverse_iterator::*this, len};
					};

					// rend
					reverse_iterator	rend()
					{
						// return reverse_iterator(*this, v.size());
						return {reverse_iterator::*this, len};
					};
					reverse_iterator	rend() const
					{
						// return reverse_iterator(*this, v.size());
						return {reverse_iterator::*this, len};
					};

					// cbegin
					const_iterator	cbegin() const
					{
						// return const_iterator(*this, 0);
						return {const_iterator:*this, 0};
					};

					// cend
					const_iterator	cend() const
					{
						// return const_iterator(*this, v.size());
						return {const_iterator::*this, len};
					};

					// crbegin
					const_reverse_iterator	crbegin() const
					{
						// return const_reverse_iterator(*this, 0);
						return {const_reverse_iterator:*this, 0};
					};

					// crend
					const_reverse_iterator	crend() const
					{
						// return const_reverse_iterator(*this, v.size());
						return {const_reverse_iterator::*this, len};
					};

		*/		//----	Capacity
					// size
					size_type	size() const
					{
						// for(size_t i=0; v[i] != NULL; i++)
						// 	;
						// return i;
						return len;
					};

		/*			// max_size
					size_type	max_size() const
					{
						return std::distance(begin(), end());
					};

					// resize
					void	resize(size_type n, value_type val = value_type())
					{
						if (n<len)
						{
							// size_type i;
							for (size_type i=n; i<len; i++)
							{
								delete v[i];
							}
							len = n;
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

			*/		// capacity
					size_type	capacity() const
					{
						return 2<<(len-2);
					};

					// empty
					bool	empty() const
					{
						if (!len)
							return true;
						return false;
					};

			/*		// reserve
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
			*/		// operator[]
					reference	operator[](size_type n)
					{
						// if (n < 0 || n > len)
						// 	throw invalidIndex();
						return v[n];
					};
			/*		const_reference	operator[](size_type n) const
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
				*/	// push_back
					void	push_back(const value_type& val)
					{
						// this->insert(val, data.end());
						len+=1;
						T *temp = v;
						v = _allocator.allocate(len); // resize() here!
						v = temp;
						v[len-1] = val;
						// for (size_type i=0; i<len; i++)
						// 	std::cout << "hlwa's data " << v[i] << std::endl;
					};
					// pop_back
					void	pop_back()
					{
						// for (size_type i=0; i<len; i++)
						// 	std::cout << "hlwa before popin " << this->v[i] << std::endl;
						_allocator.destroy(v+(len-1));
						len-=1;
						// for (size_type i=0; i<len; i++)
						// 	std::cout << "hlwa after popin " << v[i] << std::endl;
					};
			/*		// insert
					iterator	insert(iterator position, const value_type& val) {};
					void	insert(iterator position, size_type n, const_value_type& val) {};
					template <class InputIterator>void	insert(iterator position, InputIterator first, InputIterator last) {};
					// erase
					iterator	erase(iterator position) {};
					iterator	erease(iterator first, iterator last) {};
			*/		// swap
					void	swap(vector& x)
					{
						// while (x != NULL)
						// {
						// 	v[i] = x[i];
						// 	// x = x->next;
						// 	i++;
						// }
						int temp_len = len;
						T *temp_v = v;
						len = x.len;
						v = x.v;
						x.len = temp_len;
						x.v = temp_v;
					};
					// clear
					void	clear()
					{
						// while (v != NULL)
						// for (size_type i; i<len; i++)
						// {
						// 	// delete (v[i]);
						// 	// v = v->next;
						// }
						_allocator.destroy(v);
						len = 0;
					};
			/*		// emplace
					template <class... Args>iterator emplace(const_iterator position, Args&&... args) {};
					
					// emplace_back
					template <class... Args>void	emplace_back(Args&&... args) {};
					

			*/	//----	Allocator
					// get_allocator
					allocator_type	get_allocator() const
					{
						// return this->allocate;
						return _allocator;
					};
	};
}

#endif