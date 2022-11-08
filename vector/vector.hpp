/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 13:23:00 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/08 15:53:08 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include "../exceptions.hpp"
#include "Iterator_traits.hpp"
// #include "reverse_iterator.hpp"

namespace ft
{
	template <class T, class Allocator = std::allocator<T> > class vector
	{
		public:
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
			// using iterator = Vectoriterator<vector<T> >;
			typedef Vectoriterator<T>		iterator;
			// typedef InputIterator<vector<T> >	InputIterator;
			typedef const_iterator<vector<T> >	const_iterator;
			// typedef reverse_iterator<vector<T> >	reverse_iterator;
			// typedef const_reverse_iterator<vector<T> >	const_reverse_iterator;

		private:
			size_type		capcity;
			size_type		len;
			T				*v;
			Allocator		_allocator;
			// InputIterator	first;
			// InputIterator	last;
		public:
			// Member functions
				//----	Constractors
					// default constactor
					explicit vector (const allocator_type& alloc = allocator_type()) : capcity(0), len(0), v(nullptr), _allocator(alloc)
					{
						// len = 0;
						// (void)alloc;
					//	v = new T[n];
						// _allocator = alloc;
						v = _allocator.allocate(capcity);
						// v = alloc;
						// len = 0;
						// v = new T[len];
						std::cout << "vector default constractor called!" << std::endl;
					};

					// fill constractor
					explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : capcity(n), len(n), _allocator(alloc)
					{
						// this->n = n;
						// (void)alloc;
						v = _allocator.allocate(capcity);
						// v = new T[n];
						for (size_type i=0; i<capcity; i++)
						{
							v[i] = val;
							// std::cout << v[i] << std::endl;
						}
						std::cout << "vector fill constractor called!" << std::endl;
					};

				/*	// range constractor
					template <class InputIterator> vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _allocator(alloc)
					{
						int i=0;
						// v = _allocator.allocate();
						// while (first != last)
						for (InputIterator it=first; it != last; ++it)
						{
							// v[i] = val;
							// std::cout << v[i] << std::endl;
							i++;
						}
						capcity = i;
						len = i;
						std::cout << "vector range constractor called!" << std::endl;
					};*/

					// copy constractor
					vector (const vector& x) : capcity(x.capcity), len(x.len), v(x.v)
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
						// std::cout << "vector Deconstractor called!" << std::endl;
					};

					// operator=
					vector& operator=(const vector& x)
					{
						capcity = x.capcity;
						len = x.len;
						v = x.v;
						return *this;
					};

				//----	Iterators
					// begin
					iterator begin()
					{
						return v;
						// return {iterator::*this, 0};
						// return *v;
					};
					const_iterator begin() const
					{
						return v;
						// return {const_iterator::*this, 0};
					};

					// end
					iterator end()
					{
						return v+len;
						// return {iterator::*this, len};
					};
					const_iterator	end() const
					{
						return v+len;
						// return {const_iterator::*this, len};
					};

				/*	// rbegin
					reverse_iterator	rbegin()
					{
						return reverse_iterator(v);
						// return {reverse_iterator:*this, 0};
					};
					const_reverse_iterator	rbegin() const
					{
						return const_reverse_iterator(v);
						// return {const_reverse_iterator::*this, len};
					};

					// rend
					reverse_iterator	rend()
					{
						return reverse_iterator(v+len);
						// return {reverse_iterator::*this, len};
					};
					reverse_iterator	rend() const
					{
						return reverse_iterator(v+len);
						// return {reverse_iterator::*this, len};
					};

				*/	// cbegin
					const_iterator	cbegin() const
					{
						return v;
						// return {const_iterator:*this, 0};
					};

					// cend
					const_iterator	cend() const
					{
						return v+len;
						// return {const_iterator::*this, len};
					};

				/*	// crbegin
					const_reverse_iterator	crbegin() const
					{
						return const_reverse_iterator(v);
						// return {const_reverse_iterator:*this, 0};
					};

					// crend
					const_reverse_iterator	crend() const
					{
						return const_reverse_iterator(v+len);
						// return {const_reverse_iterator::*this, len};
					};*/

				//----	Capacity
					// size
					size_type	size() const
					{
						// for(size_t i=0; v[i] != NULL; i++)
						// 	;
						// return i;
						return len;
					};

					// max_size
					size_type	max_size() const
					{
						// return std::distance(begin(), end());
						return capcity;
					};

					// resize
					void	resize(size_type n, value_type val = value_type())
					{
						if (n<len)
							for (size_type i=n; i<len; i++)
								_allocator.destroy(v+i);
						else
							for (size_type i=len; i<n; i++)
								push_back(val);
						len = n;
						// capcity = n;
					};

					// capacity
					size_type	capacity() const
					{
						// return 2<<(len-2);
						return capcity;
					};

					// empty
					bool	empty() const
					{
						if (!len)
							return true;
						return false;
					};

					// reserve
					void	reserve(size_type n)
					{
						if (n > capcity)
						{
							capcity = n;
							this->_allocator(capcity);
						}
						// else
						// {
							
						// }
					};

					// shrink_to_fit
					void	shrink_to_fit()
					{
						capcity = len;
					};

				//----	Element access
					// operator[]
					reference	operator[](size_type n)
					{
						if (n < 0 || n > len)
							throw invalidIndex();
						return v[n];
					};
					const_reference	operator[](size_type n) const
					{
						if (n < 0 || n > len)
							throw invalidIndex();
						return v[n];
					};

					// at
					reference	at(size_type n)
					{
						return *(v+n);
					};
					const_reference	at(size_type n) const
					{
						// return &v[n];
						return *(v+n);
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
						// while (v->next != NULL)
						// 	v = v->next;
						return *(v+(len-1));
					};
					const_reference	back() const
					{
						// while (v->next != NULL)
						// 	v = v->next;
						return *(v+(len-1));
					};

					// data
					value_type*	data()
					{
						return v;
					};
					value_type*	data() const
					{
						return v;
					};

			/*	//----	Modifiers
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
						capcity = 0;
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