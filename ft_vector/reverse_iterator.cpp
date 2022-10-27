/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 18:08:58 by ael-asri          #+#    #+#             */
/*   Updated: 2022/10/27 18:34:37 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

namespace ft
{
	template <class Iterator> class reverse_iterator
	{
		private:
			typedef Iterator										iterator_type;
			typedef iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef iterator_traits<Iterator>::value_type			value_type
			typedef iterator_traits<Iterator>::difference_type		difference_type;
			typedef iterator_traits<Iterator>::pointer				pointer;
			typedef iterator_traits<Iterator>::reference			reference;
		public:
			// Member functions
					//----	Constractors
						// default
						reverse_iterator() {};

						// initialization
						explicit	reverse_iterator(iterator_type it) {};

						// copy
						template <class Iter>reverse_iterator(const reverse_iterator<Iter>& rev_it) {};

						// base
						iterator_type	base() const {};

						// oprator*
						reference	operator*() const {};

						// operator+
						reverse_iterator	operator+(difference_type n) const {};

						// operator++
						reverse_iterator&	operator++() {};
						reverse_iterator	operator++(int) {};
						
						// operator+=
						reverse_iterator&	operator+=(difference_type n) {};

						// operator-
						reverse_iterator	operator-(difference_type n) const {};

						// operator--
						reverse_iterator&	operator--() {};
						reverse_iterator	operator--(int) {};

						// operator-=
						reverse_iterator&	operator-=(difference_type n) {};

						// operator->
						pointer	operator->() const {};

						// operator[]
						reference	operator[](difference_type n) const {};
		// Non-member function overloads
			//---- relational operators
			template <class Iterator> bool	operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {};
			template <class Iterator> bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {};
			template <class Iterator> bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {};
			template <class Iterator> bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {};
			template <class Iterator> bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {};
			template <class Iterator> bool	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {};
			
			// operator+
			template <class Iterator> reverse_iterator<Iterator>operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {};
			
			// operator-
			template <class Iterator> reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rev_it) {};
	};
}