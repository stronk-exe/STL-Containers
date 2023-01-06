/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:00:55 by ael-asri          #+#    #+#             */
/*   Updated: 2023/01/06 10:41:34 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set.hpp"

int main()
{
    ft::set<std::string> s;
    s.insert("stronk");
    // s.insert("dog");
    // s.insert("horse");
    std::cout << s.size() << '\n';

    // for(auto& str: a) std::cout << str << ' ';
}