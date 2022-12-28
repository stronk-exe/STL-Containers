/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:12:15 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/28 13:22:44 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "../vector/vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> > class	stack
	{
        public:
            typedef T								value_type;
            typedef Container						container_type;
            typedef typename Container::size_type	size_type;

		protected:
            container_type	s;
        
		public:
			// >> Member functions
				//----	Constructors
					explicit stack( const Container& cont = Container() ) : s(cont) {};
					stack( const stack& other ) : s(other.s) {};

				//----  Destructor
					~stack(){};

                //----  operator=
					stack& operator=( const stack& other )
                    {
						if (*this != other)
							s = other.s;
						return *this;
					};

				//----  Element access
					// top
						value_type& top()
						{
							return s.back();
						};
						const value_type& top() const
						{
							return s.back();
						};

				//----  capacity
					// empty
						bool empty() const
						{
							return s.empty();
						};

					// size
						size_type size() const
						{
							return s.size();
						};

				//----  modifiers
					// push
						void push( const value_type& value )
						{
							s.push_back(value);
						};

					// pop
						void pop()
						{
							s.pop_back();
						};

                // Relational operators
                    friend bool operator==( const stack<T,Container>&, const stack<T,Container>& );
                    // {
                    //     return lhs.s == rhs.s;
                    // };
                    friend bool operator!=( const stack<T,Container>&, const stack<T,Container>& );
                    // {
                    //     return lhs.s != rhs.s;
                    // };
                    friend bool operator<( const stack<T,Container>&, const stack<T,Container>& );
                    // {
                    //     return lhs.s < rhs.s;
                    // };
                    friend bool operator<=( const stack<T,Container>&, const stack<T,Container>& );
                    // {
                    //     return lhs.s <= rhs.s;
                    // };
                    friend bool operator>( const stack<T,Container>&, const stack<T,Container>& );
                    // {
                    //     return lhs.s > rhs.s;
                    // };
                    friend bool operator>=( const stack<T,Container>&, const stack<T,Container>& );
                    // {
                    //     return lhs.s >= rhs.s;
                    // };
    };
            //>> Non member functions
                template< class T, class Container > bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
                {
                    return lhs.s == rhs.s;
                };
                template< class T, class Container > bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
                {
                    return lhs.s != rhs.s;
                };
                template< class T, class Container > bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
                {
                    return lhs.s < rhs.s;
                };
                template< class T, class Container > bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
                {
                    return lhs.s <= rhs.s;
                };
                template< class T, class Container > bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
                {
                    return lhs.s > rhs.s;
                };
                template< class T, class Container > bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
                {
                    return lhs.s <= rhs.s;
                };
                // template< class T, class Container > bool operator!=( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs )
                // {

                // };
                // template< class T, class Container > bool operator<( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs )
                // {

                // };
                // template< class T, class Container > bool operator<=( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs )
                // {

                // };
                // template< class T, class Container > bool operator>( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs )
                // {

                // };
                // template< class T, class Container > bool operator>=( const std::stack<T,Container>& lhs, const std::stack<T,Container>& rhs )
                // {

                // };
}

#endif