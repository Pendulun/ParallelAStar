#ifndef __GRAPHSEARCHER_H__
#define __GRAPHSEARCHER_H__
#include "Graph.hpp"
#include "Heuristic.hpp"
#include "ManhattanHeuristic.hpp"
#include "EuclidianHeuristic.hpp"

#include <list>

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

    void setGraph(Graph newGraph);
    void setInitialNode(unsigned int initialNodeId);
    std::list<unsigned int> getPathTo(const unsigned int finalNodeId);

private:
    GraphSearcher::searchType mySearchType;
    GraphSearcher::heuristicType myHeuristicType;
    Graph myGraph;

    unsigned int myInitialNodeId;
    std::list<unsigned int> astarSearch(Heuristic* myHeuristic, const unsigned int finalNodeId);
};
#endif