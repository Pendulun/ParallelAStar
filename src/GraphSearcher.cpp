#include "GraphSearcher.hpp"

GraphSearcher::GraphSearcher(){
    this->mySearchType = ASTAR;
    this->myHeuristicType = MANHATTAN;
    this->myInitialNodeId = 0;
}

GraphSearcher::~GraphSearcher(){
}

void GraphSearcher::setSearchType(searchType newSearchType){
    this->mySearchType = newSearchType;
}

GraphSearcher::searchType GraphSearcher::getSearchType(){
    return this->mySearchType;
}

void GraphSearcher::setHeuristicType(heuristicType newHeuristic){
    this->myHeuristicType = newHeuristic;
}

GraphSearcher::heuristicType GraphSearcher::getHeuristicType(){
    return this->myHeuristicType;
}

void GraphSearcher::setGraph(Graph newGraph){
    this->myGraph = newGraph;
}

void GraphSearcher::setInitialNode(unsigned int initialNodeId){
    this->myInitialNodeId = initialNodeId;
}

std::list<unsigned int> GraphSearcher::getPathTo(const unsigned int finalNodeId){
    std::list<unsigned int> pathToFinalNode;
    pathToFinalNode.clear();

    Heuristic* myHeuristic;

    switch (this->myHeuristicType){
    case GraphSearcher::heuristicType::MANHATTAN:
        myHeuristic = new ManhattanHeuristic();
        break;
    case GraphSearcher::heuristicType::EUCLIDIAN:
        myHeuristic = new EuclidianHeuristic();
        break;
        
    default:
        myHeuristic = new ManhattanHeuristic();
        break;
    }

    switch (this->mySearchType){
    case GraphSearcher::searchType::ASTAR:
        pathToFinalNode = this->astarSearch(myHeuristic, finalNodeId);
        break;
    
    default:
        pathToFinalNode = this->astarSearch(myHeuristic, finalNodeId);
    }

    delete myHeuristic;
    return pathToFinalNode;
}

std::list<unsigned int> astarSearch(Heuristic* myHeuristic, const unsigned int finalNodeId){
    //Pesquisar via astar
    std::list<unsigned int> pathToFinalNode;
    return pathToFinalNode;
}