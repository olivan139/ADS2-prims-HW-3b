////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Contains implementations of some algorithms for undirected graph.
/// \author     Sergey Shershakov
/// \version    0.1.0
/// \date       21.09.2020
/// \copyright  © Sergey Shershakov 2020.
///             This code is for educational purposes of the course "Algorithms
///             and Data Structures" provided by the Faculty of Computer Science
///             at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///
////////////////////////////////////////////////////////////////////////////////


#ifndef UGRAPH_ALGOS_HPP
#define UGRAPH_ALGOS_HPP

#include <set>
#include <map>
#include <algorithm>

#include "lbl_ugraph.hpp"

template<typename Vertex, typename EdgeLbl>
class PriorityQueue
{
public:
    void insert(const Vertex& u, const EdgeLbl& v)
    {
        _getAccessByV.insert(std::make_pair(u, v));
        _getAccessByL.insert(std::make_pair(v, u));
    }

    void remove(const Vertex& u)
    {
        auto it = _getAccessByV.find(u);
        auto it2 = _getAccessByL.find(std::make_pair(it->second, u));
        if (it != _getAccessByV.end())
        {
            _getAccessByV.erase(it);
            _getAccessByL.erase(it2);
        }
    }

    void set(const Vertex&u, const EdgeLbl& newLbl)
    {
        remove(u);
        insert(u, newLbl);
    }

    Vertex getMin() const
    {
        return _getAccessByL.begin()->second;
    }

    EdgeLbl getCost(const Vertex& u) const
    {
        return _getAccessByV.find(u)->second;
    }

    bool isEmpty()
    {
        return (_getAccessByV.empty() && _getAccessByL.empty());
    }
private:

    std::multimap<Vertex, int> _getAccessByV;
    std::set<std::pair<int, Vertex>> _getAccessByL;

};

/// Finds a MST for the given graph \a g using Prim's algorithm.
template<typename Vertex, typename EdgeLbl>
std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge>
findMSTPrim(const EdgeLblUGraph<Vertex, EdgeLbl>& g)
{
    std::map<Vertex, Vertex> MST;                                                       //result MST
    typename std::map<Vertex, Vertex>::iterator MSTit;                                  //it for MST
    std::set<Vertex> VisitedNodes;                                                      //Nodes we have visited
    PriorityQueue<Vertex, EdgeLbl> UnvisitedNodes;                                      //Nodes we haven't visited yet
    typename EdgeLblUGraph<Vertex, EdgeLbl>::VertexIterPair Vertices = g.getVertices(); // the array of vertices represented by a pair of iterators
    std::set<typename EdgeLblUGraph<Vertex, EdgeLbl>::Edge> res;
    UnvisitedNodes.insert(*Vertices.first, 0);                                          // we are choosing first element from set of vertices
    
    for (auto it = ++Vertices.first; it != Vertices.second; ++it)
    {
        UnvisitedNodes.insert(*it, INT_MAX);                                            // filling up the PQ with infinities
    }

    while (VisitedNodes.size() < g.getVerticesNum())
    {
        Vertex item = UnvisitedNodes.getMin();
        EdgeLbl itemCost = UnvisitedNodes.getCost(item);
        UnvisitedNodes.remove(item);
        VisitedNodes.insert(item);

        typename EdgeLblUGraph<Vertex, EdgeLbl>::AdjListCIterPair rangeOfAdjV = g.getAdjEdges(item);

        for (auto it = rangeOfAdjV.first; it != rangeOfAdjV.second; ++it)
        {
            Vertex adjNode = it->second;
            EdgeLbl label;
            g.getLabel(item, adjNode, label);

            if (VisitedNodes.find(adjNode) == VisitedNodes.end() 
            && UnvisitedNodes.getCost(adjNode) > label)
            {
                UnvisitedNodes.set(adjNode, label);
                MSTit = MST.find(adjNode);
                if (MSTit == MST.end())
                    MST.insert(std::make_pair(adjNode, item));
                else
                    MSTit->second = item;
            }
        }
    }
    for (MSTit = MST.begin(); MSTit != MST.end(); ++MSTit)
    {
        res.insert(std::make_pair(MSTit->first, MSTit->second));
    }
    return res;
}

#endif // UGRAPH_ALGOS_HPP
