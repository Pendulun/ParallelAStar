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

std::list<unsigned int> GraphSearcher::astarSearch(Heuristic* myHeuristic, const unsigned int finalNodeId){
    //List of Node Ids to get to the final node
    std::list<unsigned int> pathToFinalNode;

    //Priority Queue of the open nodes yet to be explored
    std::priority_queue<std::pair<float, SearchGraphNode>,std::vector<std::pair<float, SearchGraphNode>>, SearchGraphNodeComparator> openList;
    
    //Set of Ids in which its Nodes have been explored
    std::set<unsigned int> closedList;
    std::set<unsigned int>::iterator closedListIterator;

    for(unsigned int nodeCount = 10; nodeCount > 5; nodeCount--){
        SearchGraphNode sgn;
        sgn.setNodeId(nodeCount);
        sgn.setPathCost(nodeCount+10);
        openList.push(std::make_pair<>(nodeCount, sgn));
        closedList.insert(sgn.getNodeId());
    }
    SearchGraphNode firstNode = openList.top().second;
    openList.pop();
    std::cout<<"O primeiro elemento na OpenList eh: "<<firstNode.getNodeId()<<std::endl;

    closedListIterator = closedList.find(firstNode.getNodeId());

    std::cout<<"Ele esta na ClosedList? "<<(closedListIterator != closedList.end())<<std::endl;
    
    return pathToFinalNode;
}