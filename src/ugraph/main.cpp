////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Main module for smoke-test-project for undirected graphs.
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       18.09.2020
/// \copyright  © Sergey Shershakov 2020.
///             This code is for educational purposes of the course "Algorithms
///             and Data Structures" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///
////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <set>
#include "lbl_ugraph.hpp"
#include "ugraph_algos.hpp"


typedef UGraph<int> IntGraph;
typedef EdgeLblUGraph<int,int> IntLBGraph;
typedef EdgeLblUGraph<char, int> CharIntLBGraph;

void test1()
{
//     IntLBGraph g;
    CharIntLBGraph g;
//    g.addLblEdge(1, 2, 4);
//    g.addLblEdge(2, 3, 8);
//    g.addLblEdge(3, 1, 8);
//    g.addLblEdge(4, 3, 3);
//    g.addLblEdge('a', 'b', 4);
//     g.addLblEdge('b', 'c', 8);
//     g.addLblEdge('c', 'a', 8);
//     g.addLblEdge('d', 'c', 3);
//     g.addLblEdge('d', 'a', 16);
//     g.addLblEdge('d', 'e', 1);


    g.addLblEdge('a', 'c', 1);
    g.addLblEdge('a', 'b', 6);
    g.addLblEdge('b', 'c', 5);
    g.addLblEdge('d', 'c', 5);
    g.addLblEdge('b', 'd', 3);

    std::set<std::pair<int,int>> res;
//    res = findMSTKruskal(g);
    findMSTPrim(g);
    std::set<std::pair<int,int>>::iterator it = res.begin();
    for(it; it != res.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }
}




void test2()
{
    IntLBGraph g;
    g.addLblEdge(0, 1, 4);
    g.addLblEdge(0, 7, 8);
    g.addLblEdge(1, 2, 8);
    g.addLblEdge(1, 7, 11);
    g.addLblEdge(2, 3, 7);
    g.addLblEdge(2, 8, 2);
    g.addLblEdge(2, 5, 4);
    g.addLblEdge(3, 4, 9);
    g.addLblEdge(3, 5, 14);
    g.addLblEdge(4, 5, 10);
    g.addLblEdge(5, 6, 2);
    g.addLblEdge(6, 7, 1);
    g.addLblEdge(6, 8, 6);
    g.addLblEdge(7, 8, 7);
    std::set<std::pair<int,int>> res;
    std::set<std::pair<int,int>> res2;
    res = findMSTPrim(g);
    std::set<std::pair<int,int>>::iterator it = res.begin();
    for(it; it != res.end(); ++it)
    {
        std::cout << it->first << " " << it->second << std::endl;
    }

}


int main()
{
    std::cout << "Let's do some undirected graphs!\n";

    test2();

    std::cout << "\n\nBye-bye!\n\n";
    return 0;
}

