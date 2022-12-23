/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:11:37 by ael-asri          #+#    #+#             */
/*   Updated: 2022/12/23 16:20:37 by ael-asri         ###   ########.fr       */
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

#include "../utils/map_utils.hpp"
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

// #include "RBtree.hpp"
#include "RBnode.hpp"
#include "map.hpp"
int main()
{
    // ft::RBtree<int, char> tree;
    // ft::node<int> *n=NULL;
    // n = tree.new_node(7);
    // n9 = tree.new_node(9);
    // n3 = tree.new_node(3);

    // n.data = 7;
    // tree.insert_node(n, 17);
    // std::cout << "sewiiizz" << n->data << std::endl;
    // ft::RBtree<int, char>::iterator it = tree.begin();
    // while (it != end())
    // {
    //     std::cout << it->data << std::endl;
    //     it++;
    // }
    // std::cout << n9->data << std::endl;
    // std::cout << n3->data << std::endl;
    // tree.insert(6);
    // tree.insert(5);
    // tree.insert(4);
    // tree.insert(3);
    // tree.insert(2);
    // tree.insert(1);
 
    // std::cout << "Inorder Traversal of Created Tree\n";
    // tree.inorder();
 
    // std::cout << "\n\nLevel Order Traversal of Created Tree\n";
    // tree.levelOrder();


    // ft::map<int, char> intcharmap;
	// ft::map<char, int> charintmap;

	// ft::map<bool, bool> boolboolmap;

	// ft::map<char, int, classcomp> fourth;  // class as Compare

	// bool(*fn_pt)(int, int) = fncomp;
	// ft::map<char, int, bool(*)(int, int)>
		// fifth(fn_pt);  // function pointer as Compare
	// return true;
 
    // ft::map<std::string, int> map;
    // ft::node<int> *n=NULL;
    // ft::pair<int, bool> gg;
    // int *v;
    // *v=7;
    // n = map1.insert(v);
    // map["stronk"] = 69;
    // map["stronkest"] = 199;
    // map["redGiant"] = 50;
    // std::cout << "stronk = " << map["stronk"] << std::endl;
    // std::cout << "stronkest = " << map["stronkest"] << std::endl;
    // std::cout << "redGiant = " << map["redGiant"] << std::endl;





    // ft::map<char, int> mp;
    // // ft::pair <ft::map<char, int>::iterator, bool> ptr1, ptr2;
       
    // // using insert() to insert single pair
    // // inserting 'a' with 20
    // mp['a'] = 20;
    // // ptr2 = mp.insert( ft::pair<char, int>('b', 22) );
    // mp['c'] = 26;
    // // ptr = mp.insert( ft::pair<char, int>('a', 20) );
       
    // // checking if the key was already present or newly inserted
    // // if(ptr2.second)
    //     // std::cout << "The key was newly inserted" ;
    // std::cout << "a = " << mp['a'] << std::endl;
    // // std::cout << "b = " << mp['b'] << std::endl;
    // std::cout << "c = " << mp['c'] << std::endl;
    // else
        // std::cout << "The key was already present" ;
    
    ft::map<char, int> map;
    std::cout << "len before " << map.size() << std::endl;
    map['a'] = 13;
    // map['b'] = 24;
    // map['c'] = 9;
    // map.insert(ft::make_pair(-1, 99));
    // calls a_map.begin() and a_map.end()
    // int i=1;
    // for (ft::map<int, int>::iterator it = map.begin(); it != map.end(); it++)
    //     std::cout << map[i++] << '\n';
    map.erase('a');
    std::cout << map['a'] << std::endl;
    std::cout << "len after " << map.size() << std::endl;
    return 0;
}