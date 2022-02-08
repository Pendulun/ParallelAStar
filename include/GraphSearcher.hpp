#ifndef __GRAPHSEARCHER_H__
#define __GRAPHSEARCHER_H__

#include <queue>
#include <map>
#include <utility>
#include <vector>
#include <set>
#include <stack>
#include <list>
#include <unordered_map>
#include <iterator>
#include <pthread.h>

#include <iostream>

#include "Graph.hpp"
#include "Heuristic.hpp"
#include "ManhattanHeuristic.hpp"
#include "EuclidianHeuristic.hpp"
#include "ZeroHeuristic.hpp"
#include "SearchGraphNode.hpp"
#include "BST.hpp"
#include "BSTNode.hpp"
#include "ParallelASearch.hpp"

class GraphSearcher{
public:
    enum searchType{ASTAR};
    enum heuristicType{MANHATTAN, EUCLIDIAN, ZERO};

    GraphSearcher();
    ~GraphSearcher();

    void setSearchType(searchType newSearchType);
    searchType getSearchType();

    void setHeuristicType(heuristicType newHeuristic);
    heuristicType getHeuristicType();

    void setGraph(Graph* newGraph);
    void setInitialNode(unsigned int initialNodeId);

    std::stack<unsigned int> searchInGraph();
    std::stack<unsigned int> parallelSearchInGraph(unsigned int numThreads);

    float getTotalCost();
    float getPathCost();
    unsigned int getNodesExploredCount();

private:

    GraphSearcher::searchType mySearchType;
    GraphSearcher::heuristicType myHeuristicType;
    Graph* myGraph;
    float totalCost;
    float pathCost;
    unsigned int nodesExploredCount;

    unsigned int myInitialNodeId;
    std::stack<unsigned int> astarSearch(Heuristic* myHeuristic);

    std::stack<unsigned int> parallelAstarSearch(Heuristic* myHeuristic, unsigned int numThreads);
    static void* oneWaySearch(void* args);

    std::stack<unsigned int> combineTwoWaySearchesPath(std::stack<unsigned int>, std::stack<unsigned int>);
    SearchGraphNode* populateInitialNodeOpenList(GraphNode* originNode, GraphNode* finalNode, Heuristic* myHeuristic);
    
    std::stack<unsigned int> getPathTo(SearchGraphNode* finalNode);
    Heuristic* getHeuristic();
};
#endif