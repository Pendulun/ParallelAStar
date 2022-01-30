#ifndef __GRAPHSEARCHER_H__
#define __GRAPHSEARCHER_H__

#include <queue>
#include <utility>
#include <vector>
#include <set>
#include <stack>
#include <list>
#include <unordered_map>
#include <iterator>

#include <iostream>

#include "Graph.hpp"
#include "Heuristic.hpp"
#include "ManhattanHeuristic.hpp"
#include "EuclidianHeuristic.hpp"
#include "SearchGraphNode.hpp"
#include "SearchGraphNodeComparator.hpp"
#include "BST.hpp"
#include "BSTNode.hpp"



class GraphSearcher{
public:
    enum searchType{ASTAR};
    enum heuristicType{MANHATTAN, EUCLIDIAN};

    GraphSearcher();
    ~GraphSearcher();

    void setSearchType(searchType newSearchType);
    searchType getSearchType();

    void setHeuristicType(heuristicType newHeuristic);
    heuristicType getHeuristicType();

    void setGraph(Graph* newGraph);
    void setInitialNode(unsigned int initialNodeId);
    std::stack<unsigned int> searchInGraph();

private:
    GraphSearcher::searchType mySearchType;
    GraphSearcher::heuristicType myHeuristicType;
    Graph* myGraph;

    unsigned int myInitialNodeId;
    std::stack<unsigned int> astarSearch(Heuristic* myHeuristic);
};
#endif