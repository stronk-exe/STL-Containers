/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 17:12:15 by ael-asri          #+#    #+#             */
/*   Updated: 2022/11/02 17:12:18 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include "../vector/vector.hpp"

namespace ft
{
    template<class T, class Container = ft::vector<T> > class stack
    {
        // private:

        
        public:
            typedef T           value_type;
            typedef size_t      size_type;
            typedef Container   container_type;
            // typedef &value_type          reference;
            // typedef const &value_type          const_reference;
            // const_reference	Container::const_reference;
            // >> Member functions
				//----	Constructors
                    explicit stack( const Container& cont = Container() ) : c(cont) {};
                    // stack( const stack& other ) : c(other.c) {};

                //----  Destructor
                    ~stack(){};

                //----  operator=
                    // stack& operator=( const stack& other )
                    // {

                    // };

                //----  Element access
                    // top
                        value_type& top()
                        {
                            return c.back();
                        };
                        const value_type& top() const
                        {
                            return c.back();
                        };
                
                //----  capacity
                    // empty
                        bool empty() const
                        {
                            return c.empty();
                        };
                    
                    // size
                        size_type size() const
                        {
                            return c.size();
                        };
                
                //----  modifiers
                    // push
                        void push( const value_type& value )
                        {
                            c.push_back(value);
                        };
                        // void push( value_type&& value )
                        // {
                        //     c.pop_back(value);
                        // };

                    // pop
                        void pop()
                        {
                            c.pop_back();
                        };
        protected:
            container_type	c;
    };
            //>> Non member functions
                template< class T, class Container > bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
                {
                    return lhs.c == rhs.c;
                };
                template< class T, class Container > bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
                {
                    return lhs.c != rhs.c;
                };
                template< class T, class Container > bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
                {
                    return lhs.c < rhs.c;
                };
                template< class T, class Container > bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
                {
                    return lhs.c <= rhs.c;
                };
                template< class T, class Container > bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
                {
                    return lhs.c > rhs.c;
                };
                template< class T, class Container > bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
                {
                    return lhs.c <= rhs.c;
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