#include "GraphSearcher.hpp"

GraphSearcher::GraphSearcher(){
    this->mySearchType = ASTAR;
    this->myHeuristicType = MANHATTAN;
    this->myInitialNodeId = 0;
    this->totalCost = 0.0;
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

    //Stack of Node Ids to get to the final node
    std::stack<unsigned int> pathToFinalNode;

    //Priority Queue of the open nodes yet to be explored
    BST* openList = new BST();

    //Set of Ids in which its Nodes have been explored
    std::set<unsigned int> closedList;

    //Used to delete all SearchGraphNode created
    std::list<SearchGraphNode*> searchGraphNodescreated;

    SearchGraphNode* initialSearchGraphNode = new SearchGraphNode();
    initialSearchGraphNode->setGraphNode(initialNode);
    initialSearchGraphNode->setPathCost(0.0 + myHeuristic->calculate(initialNode, finalNode));
    initialSearchGraphNode->setTotalCost(0);
    openList->addAndCreateNodeFor(initialSearchGraphNode);
    openList->printBST();

    searchGraphNodescreated.push_back(initialSearchGraphNode);

    unsigned int exploredCount = 0;
    std::cout<<"Its gonna start exploring!\n";
    while(!openList->empty()){
        exploredCount++;
        
        SearchGraphNode* currNode = openList->popMaxPriorityNode();
        //std::cout<<"----Exploring node id: "<<currNode->getNodeId()<<"----"<<std::endl;

        //If it is the goal
        if(currNode->getGraphNode()->getId() == finalNode->getId()){
            std::cout<<"Found the final node!\n";
            //Conseguir o custo total
            this->totalCost = currNode->getTotalCost();
            this->pathCost = currNode->getPathCost();

            while(currNode != nullptr){
                pathToFinalNode.push(currNode->getGraphNode()->getId());
                currNode = currNode->getParentNode();
            }

            std::cout<<"Nodes explored count:"<<exploredCount<<". It found a path!\n";
            
            //Delete all SearchGraphNodes created
            //searchGraphNodescreated.erase(searchGraphNodescreated.begin(), searchGraphNodescreated.end());
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
            //std::cout<<"Found neigh: "<<neighboorsIt.first;

            //If neighboor is not in the closedList
            if(closedList.count(neighboorsIt.first) == 0){
                double calculatedPathCost = currNode->getPathCost() + neighboorsIt.second;
                //std::cout<<" PathCost: "<<calculatedPathCost<<" ";

                //If neighboor is not in the openList
                if(!openList->hasNode(neighboorsIt.first)){
                    //std::cout<<" First time reached!";

                    SearchGraphNode* newSearchGraphNode = new SearchGraphNode();
                    newSearchGraphNode->setGraphNode(&(this->myGraph->findNode(neighboorsIt.first)));
                    newSearchGraphNode->setPathCost(calculatedPathCost);
                    float heuristic = myHeuristic->calculate(newSearchGraphNode->getGraphNode(), finalNode);
                    //std::cout<<" Heuristic: "<<heuristic<<" ";
                    newSearchGraphNode->setTotalCost(newSearchGraphNode->getPathCost() + heuristic);
                    //std::cout<<" TotalCost: "<<newSearchGraphNode->getTotalCost()<<" ";
                    newSearchGraphNode->setParentNode(currNode);
                    //std::cout<<" Parent: "<<newSearchGraphNode->getParentNode()->getNodeId()<<" ";

                    searchGraphNodescreated.push_back(newSearchGraphNode);
                    openList->addAndCreateNodeFor(newSearchGraphNode);
                //If neighboor is in the openList
                //and its saved path cost is greater than current path cost to it
                }else if(calculatedPathCost < openList->findNode(neighboorsIt.first)->getNode()->getPathCost()){
                    //std::cout<<". Found a better path cost!";
                    BSTNode* bstNode = openList->findNode(neighboorsIt.first);

                    bstNode->getNode()->setPathCost(calculatedPathCost);
                    float heuristic = myHeuristic->calculate(bstNode->getNode()->getGraphNode(), finalNode);
                    bstNode->getNode()->setTotalCost(bstNode->getNode()->getPathCost() + heuristic);
                    //std::cout<<" TotalCost: "<<bstNode->getTotalCost()<<" ";
                    bstNode->getNode()->setParentNode(currNode);
                    openList->updateNode(bstNode);
                }
            }else{
                //std::cout<<". It was already explored!";
            }
            //std::cout<<" FIM!"<<std::endl;
            //openList->printBST();
        }
    }
    
    //Delete all SearchGraphNodes
    searchGraphNodescreated.erase(searchGraphNodescreated.begin(), searchGraphNodescreated.end());
    std::cout<<"Nodes explored count:"<<exploredCount<<". It didn't found a path!\n";
    return pathToFinalNode;
}