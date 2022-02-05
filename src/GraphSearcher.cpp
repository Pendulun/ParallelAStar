#include "GraphSearcher.hpp"

GraphSearcher::GraphSearcher(){
    this->mySearchType = ASTAR;
    this->myHeuristicType = MANHATTAN;
    this->myInitialNodeId = 0;
    this->totalCost = 0.0;
    this->nodesExploredCount = 0;
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

void GraphSearcher::setGraph(Graph* newGraph){
    this->myGraph = newGraph;
}

void GraphSearcher::setInitialNode(unsigned int initialNodeId){
    this->myInitialNodeId = initialNodeId;
}

float GraphSearcher::getTotalCost(){
    return this->totalCost;
}

float GraphSearcher::getPathCost(){
    return this->pathCost;
}

unsigned int GraphSearcher::getNodesExploredCount(){
    return this->nodesExploredCount;
}

std::stack<unsigned int> GraphSearcher::searchInGraph(){
    std::stack<unsigned int> pathToFinalNode;

    Heuristic* myHeuristic;

    switch (this->myHeuristicType){
        case GraphSearcher::heuristicType::MANHATTAN:
            myHeuristic = new ManhattanHeuristic();
            break;
        case GraphSearcher::heuristicType::EUCLIDIAN:
            myHeuristic = new EuclidianHeuristic();
            break;

        case GraphSearcher::heuristicType::ZERO:
            myHeuristic = new ZeroHeuristic();
            break;
            
        default:
            myHeuristic = new ManhattanHeuristic();
            break;
    }

    switch (this->mySearchType){
        case GraphSearcher::searchType::ASTAR:
            pathToFinalNode = this->astarSearch(myHeuristic);
            break;
        
        default:
            pathToFinalNode = this->astarSearch(myHeuristic);
    }

    delete myHeuristic;
    return pathToFinalNode;
}

std::stack<unsigned int> GraphSearcher::astarSearch(Heuristic* myHeuristic){
    GraphNode* initialNode = &this->myGraph->findNode(this->myGraph->getInitialPos());
    GraphNode* finalNode = &this->myGraph->findNode(this->myGraph->getFinalPos());

    //Priority Queue of the open nodes yet to be explored
    BST* openList = new BST();

    //Stack of Node Ids to get to the final node
    std::stack<unsigned int> pathToFinalNode;

    //Set of Ids in which its Nodes have been explored
    std::set<unsigned int> closedList;

    //Used to delete all SearchGraphNode created
    std::list<SearchGraphNode*> searchGraphNodescreated;

    SearchGraphNode* initialSearchGraphNode = new SearchGraphNode();
    initialSearchGraphNode->setGraphNode(initialNode);
    initialSearchGraphNode->setLastActionCost(0.0);
    initialSearchGraphNode->setPathCost(0.0);
    initialSearchGraphNode->setTotalCost(0 + myHeuristic->calculate(initialNode, finalNode));
    openList->addAndCreateNodeFor(initialSearchGraphNode);
    //openList->printBST();

    searchGraphNodescreated.push_back(initialSearchGraphNode);

    unsigned int exploredCount = 0;
    std::cout<<"Its gonna start exploring!\n";
    while(!openList->empty()){
        exploredCount++;
        
        SearchGraphNode* currNode = openList->popMaxPriorityNode();

        //If it is the goal
        if(currNode->getGraphNode()->getId() == finalNode->getId()){
            this->totalCost = currNode->getTotalCost();
            this->pathCost = currNode->getPathCost();
            this->nodesExploredCount = exploredCount;

            pathToFinalNode = this->getPathTo(currNode);
            
            //Delete all SearchGraphNodes created
            while(!searchGraphNodescreated.empty()){
                delete searchGraphNodescreated.front();
                searchGraphNodescreated.pop_front();
            }            
            delete openList;

            return pathToFinalNode;
        }

        closedList.insert(currNode->getNodeId());

        std::unordered_map<unsigned int, double>* nodeNeighboors = currNode->getGraphNode()->getCostToOtherNodes();

        for(std::pair<unsigned int, double> neighboorsIt: *nodeNeighboors){

            //If neighboor is not in the closedList
            if(closedList.count(neighboorsIt.first) == 0){
                double pathCostToNeighboor = currNode->getPathCost() + neighboorsIt.second;

                //If neighboor is not in the openList
                if(!openList->hasNode(neighboorsIt.first)){

                    SearchGraphNode* newSearchGraphNode = new SearchGraphNode();
                    newSearchGraphNode->setGraphNode(&(this->myGraph->findNode(neighboorsIt.first)));
                    newSearchGraphNode->setLastActionCost(neighboorsIt.second);
                    newSearchGraphNode->setPathCost(pathCostToNeighboor);
                    float heuristic = myHeuristic->calculate(newSearchGraphNode->getGraphNode(), finalNode);
                    newSearchGraphNode->setTotalCost(pathCostToNeighboor + heuristic);
                    newSearchGraphNode->setParentNode(currNode);

                    searchGraphNodescreated.push_back(newSearchGraphNode);
                    openList->addAndCreateNodeFor(newSearchGraphNode);
                
                }else if(pathCostToNeighboor < openList->findNode(neighboorsIt.first)->getPathCost()){
                    //If neighboor is in the openList
                    //and its saved path cost is greater than current path cost to it

                    BSTNode* bstNode = openList->findNode(neighboorsIt.first);
                    SearchGraphNode* searchNode = bstNode->getNode();

                    searchNode->setPathCost(pathCostToNeighboor);
                    float heuristic = myHeuristic->calculate(searchNode->getGraphNode(), finalNode);
                    searchNode->setTotalCost(pathCostToNeighboor + heuristic);
                    searchNode->setLastActionCost(neighboorsIt.second);
                    searchNode->setParentNode(currNode);

                    openList->updateNode(bstNode);
                }
            }
        }
    }
    
    //Delete all SearchGraphNodes
    while(!searchGraphNodescreated.empty()){
        delete searchGraphNodescreated.front();
        searchGraphNodescreated.pop_front();
    }
    delete openList;

    return pathToFinalNode;
}

std::stack<unsigned int> GraphSearcher::getPathTo(SearchGraphNode* finalNode){
    std::stack<unsigned int> pathIds;
    SearchGraphNode* currNode = finalNode;
    while(currNode != nullptr){
        pathIds.push(currNode->getGraphNode()->getId());
        currNode = currNode->getParentNode();
    }

    return pathIds;
}