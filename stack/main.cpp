/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 11:45:37 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/07 23:52:55 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.hpp"
#include <vector>
#include <stack>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mOK\033[0m\n") : (std::cout << "\033[1;31mKO\033[0m\n"))

void	stackConstructors(void)
{
    std::cout <<"	default constructor ---	";
	{
		std::vector<int> myvector (2,200);
		ft::stack<int,std::vector<int> > s(myvector);
		EQUAL(s.size() == 2);
	}
}

void	stackMemberFunctions(void)
{
    std::cout << "	empty method ----	";
	{
		ft::stack<int> mystack;
		int sum (0);

		for (int i=1;i<=10;i++) mystack.push(i);

		while (!mystack.empty())
		{
			sum += mystack.top();
			mystack.pop();
		}
		EQUAL(sum == 55);
	}
    std::cout << "	size method ----	";
	{
		bool cond(false);
		ft::stack<int> myints;
		cond = myints.size() == 0;

		for (int i=0; i<5; i++) myints.push(i);
		cond = cond && (myints.size() == 5);

		myints.pop();
		cond = cond && (myints.size() == 4);
		EQUAL(cond);
	}
    std::cout << "	top method ----		";
	{
		ft::stack<int> mystack;

		mystack.push(10);
		mystack.push(20);

		mystack.top() -= 5;
		std::vector<int> vec(10, 50);
		vec.push_back(300);
		ft::stack<int, std::vector<int> > const c_mystack(vec);

		EQUAL(mystack.top() == 15 && c_mystack.top() == 300);
	}
    std::cout << "	push & pop methods ----	";
	{
		int sum(0);
		ft::stack<int> mystack;

		for (int i=0; i<5; ++i) mystack.push(i);

		while (!mystack.empty())
		{
			sum += mystack.top();
			mystack.pop();
		}
		EQUAL(sum == 10);
	}
}

void stackRelationalOperators(void)
{
    std::cout << "	operator== ----		";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack ==  mystack1) == (stack == stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack ==  mystack1) == (stack == stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack ==  mystack1) == (stack == stack1);
		}
		EQUAL(cond);
	}
	std::cout << "	operator!= ----		";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack !=  mystack1) == (stack != stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack !=  mystack1) == (stack != stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack !=  mystack1) == (stack != stack1);
		}
		EQUAL(cond);
	}
	std::cout << "	operator< ----		";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack < mystack1) == (stack < stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack < mystack1) == (stack < stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack < mystack1) == (stack < stack1);
		}
		EQUAL(cond);
	}
    std::cout << "	operator<= ----		";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack <= mystack1) == (stack <= stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack <= mystack1) == (stack <= stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack <= mystack1) == (stack <= stack1);
		}
		EQUAL(cond);
	}
	std::cout << "	operator> ----		";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack > mystack1) == (stack > stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack > mystack1) == (stack > stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack > mystack1) == (stack > stack1);
		}
		EQUAL(cond);
	}
	std::cout << "	operator>= ----		";
	{
		bool cond(false);
		std::vector<int>	vec(100, 2);
		std::vector<int>	vec1(100, 2);
		{
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = (mystack >= mystack1) == (stack >= stack1);
		}
		{
			vec.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack >= mystack1) == (stack >= stack1);
		}
		{
			vec.pop_back();
			vec1.push_back(300);
			ft::stack<int, std::vector<int> > mystack1(vec);
			ft::stack<int, std::vector<int> > mystack(vec1);
			std::stack<int, std::vector<int> > stack1(vec);
			std::stack<int, std::vector<int> > stack(vec1);
			cond = cond && (mystack >= mystack1) == (stack >= stack1);
		}
		EQUAL(cond);
	}
}

int main()
{
    std::cout << "* Stack Constructors;" << std::endl;
    stackConstructors();
	std::cout << std::endl;

    std::cout << "* Stack Member Functions" <<  std::endl;
    stackMemberFunctions();
	std::cout << std::endl;

    std::cout << "* Stack Relational Operators" << std::endl;
    stackRelationalOperators();
	
	return 0;
}