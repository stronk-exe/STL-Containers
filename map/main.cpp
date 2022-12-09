/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:11:37 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/09 11:14:01 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.hpp"

int main()
{
	std::cout << "hello map" << std::endl;
	ft::map<std::string, int> map1;
	// ft::map<std::string, int> map2(map1);
	map1["something"] = 69;
	// map1["anything"] = 199;
	// map1["that thing"] = 50;
	// std::cout << "map1 = " << map1;
	// map1.insert(2, 79);
	std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::map<std::string, int> iter(map1.find("anything"), map1.end());
	// std::cout << "\niter = " << iter;
	// std::cout << "map1 = " << map1;
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::map<std::string, int> map2(map1);
	// std::cout << "^^^^^^^^^^^^^^" << std::endl;
	// ft::map<std::string, int> map3;
	// map3 = map2;
}