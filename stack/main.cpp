#include "stack.hpp"

int main()
{
    std::cout << "hello mr stack" << std::endl;
    ft::stack<int> c1;
    c1.push(5);
    c1.push(7);
    c1.push(7);
    std::cout << c1.size() << '\n';
 
    ft::stack<int> c2(c1);
    std::cout << c2.size() << '\n';
 
    // std::deque<int> deq (3,5);
    // ft::stack<int> c3(deq); // overload (2)
    // std::cout << c3.size() << '\n';
}