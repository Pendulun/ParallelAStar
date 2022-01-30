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

void GraphSearcher::setGraph(Graph* newGraph){
    this->myGraph = newGraph;
}

void GraphSearcher::setInitialNode(unsigned int initialNodeId){
    this->myInitialNodeId = initialNodeId;
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

    //Stack of Node Ids to get to the final node
    std::stack<unsigned int> pathToFinalNode;

    //Priority Queue of the open nodes yet to be explored
    BST openList;

    //Set of Ids in which its Nodes have been explored
    std::set<unsigned int> closedList;

    //Used to delete all SearchGraphNode created
    std::list<SearchGraphNode*> searchGraphNodescreated;

    SearchGraphNode* initialSearchGraphNode = new SearchGraphNode();
    initialSearchGraphNode->setGraphNode(initialNode);
    initialSearchGraphNode->setPathCost(0.0 + myHeuristic->calculate(initialNode, finalNode));
    openList.addAndCreateNodeFor(initialSearchGraphNode);

    searchGraphNodescreated.push_back(initialSearchGraphNode);

    unsigned int exploredCount = 0;
    std::cout<<"Its gonna start exploring!\n";
    while(!openList.empty()){
        exploredCount++;
        
        SearchGraphNode* currNode = openList.popMaxPriorityNode();
        std::cout<<"----Exploring node id: "<<currNode->getNodeId()<<"----"<<std::endl;

        //If it is the goal
        if(currNode->getGraphNode()->getId() == finalNode->getId()){
            std::cout<<"Found the final node!\n";
            while(currNode != nullptr){
                pathToFinalNode.push(currNode->getGraphNode()->getId());
                currNode = currNode->getParentNode();
            }

            //Delete all SearchGraphNodes created
            searchGraphNodescreated.erase(searchGraphNodescreated.begin(), searchGraphNodescreated.end());

            std::cout<<"Nodes explored count:"<<exploredCount<<". It found a path!\n";
            return pathToFinalNode;
        }

        closedList.insert(currNode->getNodeId());

        std::unordered_map<unsigned int, unsigned int>::iterator neighboorsIt;
        std::unordered_map<unsigned int, unsigned int>* nodeNeighboors = currNode->getGraphNode()->getCostToOtherNodes();
        for(neighboorsIt = nodeNeighboors->begin(); neighboorsIt != nodeNeighboors->end(); neighboorsIt++){
            std::cout<<"Found neigh: "<<neighboorsIt->first;

            //If neighboor is not in the closedList
            if(closedList.count(neighboorsIt->first) == 0){
                float calculatedPathCost = currNode->getPathCost() + neighboorsIt->second;

                //If neighboor is not in the openList
                if(!openList.hasNode(neighboorsIt->first)){

                    SearchGraphNode* newSearchGraphNode = new SearchGraphNode();
                    newSearchGraphNode->setGraphNode(&(this->myGraph->findNode(neighboorsIt->first)));
                    newSearchGraphNode->setPathCost(calculatedPathCost);
                    float heuristic = myHeuristic->calculate(newSearchGraphNode->getGraphNode(), finalNode);
                    newSearchGraphNode->setTotalCost(newSearchGraphNode->getPathCost() + heuristic);
                    newSearchGraphNode->setParentNode(currNode);

                    searchGraphNodescreated.push_back(newSearchGraphNode);
                    openList.addAndCreateNodeFor(newSearchGraphNode);
                //If neighboor is in the openList
                }else if(calculatedPathCost < openList.findNode(neighboorsIt->first)->getNode()->getPathCost()){
                    std::cout<<". It's got a better cost!";
                    BSTNode* bstNode = openList.findNode(neighboorsIt->first);

                    bstNode->getNode()->setPathCost(calculatedPathCost);
                    float heuristic = myHeuristic->calculate(bstNode->getNode()->getGraphNode(), finalNode);
                    bstNode->getNode()->setTotalCost(bstNode->getNode()->getPathCost() + heuristic);
                    bstNode->getNode()->setParentNode(currNode);
                    openList.updateNode(bstNode);
                }
            }else{
                std::cout<<". It was already explored!";
            }
            std::cout<<std::endl;
        }
    }
    
    //Delete all SearchGraphNodes
    searchGraphNodescreated.erase(searchGraphNodescreated.begin(), searchGraphNodescreated.end());
    std::cout<<"Nodes explored count:"<<exploredCount<<". It didn't found a path!\n";
    return pathToFinalNode;
}