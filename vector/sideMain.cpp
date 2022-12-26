#include <iostream>
#include "vector.hpp"
#include <vector>
#include <iomanip>

#define EQUAL(x) ((x) ? (std::cout << "\033[1;32mAC\033[0m\n") : (std::cout << "\033[1;31mWA\033[0m\n"))

int main()
{
	// std::cout << "\033[1;37m[-------------------- [" << std::setw(40) << std::left << " = operator (lhs.size = 0) "
    //           << "] --------------------]\t\t\033[0m";
    {
        /*-----------------------------------------------------*/
        /*------------------ ft::vectors ---------------------*/
        ft::vector<std::string> ft_v1;
        ft::vector<std::string> ft_v2(10, "string2");
        ft_v1 = ft_v2;
        /*----------------------------------------------------*/
        /*------------------ strings to store the results ----*/
        // std::string res, ft_res;
        // /*----------------------------------------------------*/

		
        // for (ft::vector<std::string>::iterator it = ft_v1.begin(); it != ft_v1.end(); ++it) // fill ft_res from ft_v1
        //     ft_res += *it;

        // EQUAL(res == ft_res);
    }
}