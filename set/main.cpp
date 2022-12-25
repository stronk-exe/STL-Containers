#include "set.hpp"

int main()
{
    ft::set<std::string> a;
    a.insert("cat");
    a.insert("dog");
    a.insert("horse");
    std::cout << a.size() << '\n';

    // for(auto& str: a) std::cout << str << ' ';
}