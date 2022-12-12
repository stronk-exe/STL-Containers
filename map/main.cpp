/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:11:37 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/12 19:14:32 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
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
*/
#include "../utils/map_utils.hpp"
/*
int main()
{
    bst<int> b;
	bst<int> *root;
    root = b.insert(root, 50);
    b.insert(root, 30);
    b.insert(root, 20);
    b.insert(root, 40);
    b.insert(root, 70);
    b.insert(root, 60);
    b.insert(root, 80);
 
    b.inorder(root);
    return 0;
}
int main()
{
 */   /* Let us create following BST
              50
            /    \
          30     70
         /  \   /  \
       20   40 60  80 */
 /*   node<int>	n;
	node<int>	*root;
    root = n.insert_node(root, 50);
    n.insert_node(root, 30);
    n.insert_node(root, 20);
    n.insert_node(root, 40);
    n.insert_node(root, 70);
    n.insert_node(root, 60);
    n.insert_node(root, 80);
 
    printf("Inorder traversal of the given tree \n");
    n.inorder(root);
 
    printf("\n\nDelete 20\n");
    root = n.delete_node(root, 20);
    printf("Inorder traversal of the modified tree \n");
    n.inorder(root);
 
    printf("\n\nDelete 30\n");
    root = n.delete_node(root, 30);
    printf("Inorder traversal of the modified tree \n");
    n.inorder(root);
 
    printf("\n\nDelete 50\n");
    root = n.delete_node(root, 50);
    printf("Inorder traversal of the modified tree \n");
    n.inorder(root);
 
    return 0;
}
*/

int main()
{
    RBtree<int> tree;
 
    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
 
    std::cout << "Inorder Traversal of Created Tree\n";
    tree.inorder();
 
    // std::cout << "\n\nLevel Order Traversal of Created Tree\n";
    // tree.levelOrder();
 
    return 0;
}