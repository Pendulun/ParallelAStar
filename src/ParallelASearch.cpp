#include "ParallelASearch.hpp"


ParallelASearch::ParallelASearch(){

}

ParallelASearch::~ParallelASearch(){

}


void ParallelASearch::setMyOpenListMutex(pthread_rwlock_t& mutex){
    this->myOpenListMutex = &mutex;
}

void ParallelASearch::setOtherSearchOpenListMutex(pthread_rwlock_t& mutex){
    this->otherSearchOpenListMutex = &mutex;
}

void ParallelASearch::setMyClosedListMutex(pthread_rwlock_t& mutex){
    this->myClosedListMutex = &mutex;
}

void ParallelASearch::setOtherSearchClosedListMutex(pthread_rwlock_t& mutex){
    this->otherSearchClosedListMutex = &mutex;
}

void ParallelASearch::setBestPathMutex(pthread_rwlock_t& mutex){
    this->bestPathMutex = &mutex;
}

void ParallelASearch::setTerminateMutex(pthread_rwlock_t& mutex){
    this->terminateMutex = &mutex;
}

void ParallelASearch::setSearchNodesMutex(pthread_rwlock_t& mutex){
    this->searchNodesMutex = &mutex;
}

void ParallelASearch::setHasNodesOpenListCondVar(pthread_cond_t& condVar){
    this->hasNodesOpenListCondVar = &condVar;
}

void ParallelASearch::setHasNodesOpenListMutex(pthread_mutex_t& mutex){
    this->hasNodesOpenListMutex = &mutex;
}

void ParallelASearch::setCurrTakenNodesCondVar(pthread_cond_t& condVar){
    this->currTakenNodesCondVar = &condVar;
}

void ParallelASearch::setCurrTakenNodesMutex(pthread_mutex_t& mutex){
    this->currTakenNodesMutex = &mutex;
}

void ParallelASearch::setInitNodeId(unsigned int nodeId){
    this->initNodeId = nodeId;
}

void ParallelASearch::setFinalNodeId(unsigned int nodeId){
    this->finalNodeId = nodeId;
}

void ParallelASearch::setHeuristic(Heuristic* heuristic){
    this->myHeuristic = heuristic;
}

void ParallelASearch::setThreadId(unsigned int threadId){
    this->threadId = threadId;
}

void ParallelASearch::setNumThreadsMySearch(unsigned int numThreads){
    this->numThreadsMySearch = numThreads;
}

void ParallelASearch::setShouldStopCounter(unsigned int* shouldStop){
    this->shouldStopCounter = shouldStop;
}

void ParallelASearch::setBestPathCost(double* bestPathCost){
    this->bestPathCost = bestPathCost;
}

void ParallelASearch::setFoundPath(bool* foundPath){
    this->foundAPath = foundPath;
}

void ParallelASearch::setGraph(Graph* graph){
    this->myGraph = graph;
}

void ParallelASearch::setPathToFinalNode(std::stack<unsigned int>* path){
    this->pathToFinalNode = path;
}

void ParallelASearch::setMyClosedList(std::map<unsigned int, double>* closedList){
    this->myClosedList = closedList;
}

void ParallelASearch::setOtherSearchClosedList(std::map<unsigned int, double>* closedList){
    this->otherSearchClosedList = closedList;
}

void ParallelASearch::setCurrTakenNodes(std::set<unsigned int>* currTaken){
    this->currTakenNodes = currTaken;
}

void ParallelASearch::setMyOpenList(BST* openList){
    this->myOpenList = openList;
}

void ParallelASearch::setOtherSearchOpenList(BST* openList){
    this->otherSearchOpenList = openList;
}

std::stack<unsigned int> ParallelASearch::getPathToFinalNode(){
    return (*this->pathToFinalNode);
}

void ParallelASearch::setFinalNode(GraphNode* finalNode){
    this->finalNode = finalNode;
}

void ParallelASearch::setMyOriginNode(GraphNode* originNode){
    this->originNode = originNode;
}

void ParallelASearch::setSearchPathNodesCreated(std::list<SearchGraphNode*>* searchNodesCreated){
    this->searchNodesCreated = searchNodesCreated;
}

void ParallelASearch::setTerminate(bool* terminate){
    this->terminate = terminate;
}

unsigned int ParallelASearch::getExploredCount(){
    return this->exploredCount;
}

void ParallelASearch::setMiddleNode(SearchGraphNode* middleNode){
    this->middleNode = middleNode;
}

SearchGraphNode* ParallelASearch::getMiddleNode(){
    return this->middleNode;
}

bool ParallelASearch::shouldTerminate(){
    bool shouldTerminate = false;
    pthread_rwlock_rdlock(this->terminateMutex);
    shouldTerminate = *this->terminate;
    pthread_rwlock_unlock(this->terminateMutex);
    return shouldTerminate;
}

bool ParallelASearch::shouldExplore(SearchGraphNode* currNode){
    if(!(*this->foundAPath)){
        return true;
    }

    float otherSearchHeuristic = myHeuristic->calculate(currNode->getGraphNode(), this->originNode);
    bool betterTotalCost = currNode->getTotalCost() < *this->bestPathCost;
    bool lowEnoughTotalCost = currNode->getPathCost() + this->otherSearchOpenList->peekMaxPriority() - otherSearchHeuristic < *this->bestPathCost;
    return (betterTotalCost && lowEnoughTotalCost);
}

void ParallelASearch::updateBestPathCostIfCan(double pathCostToCurrNeigh, const unsigned int neighId, SearchGraphNode* neighSearchNode){
    double g1 = pathCostToCurrNeigh;
    double g2 = 0.0;
    
    bool g2IsInOtherClosedList = false;
    bool g2IsInOtherOpenList = false;

    pthread_rwlock_rdlock(this->otherSearchClosedListMutex);
    if(this->otherSearchClosedList->count(neighId) != 0){
        g2 = this->otherSearchClosedList->at(neighId);
        g2IsInOtherClosedList = true;
    }

    pthread_rwlock_unlock(this->otherSearchClosedListMutex);
    
    if(!g2IsInOtherClosedList){
        pthread_rwlock_rdlock(this->otherSearchOpenListMutex);
        if(this->otherSearchOpenList->hasNode(neighId)){
            g2 = this->otherSearchOpenList->findNode(neighId)->getPathCost();
            g2IsInOtherOpenList = true;
        }
        pthread_rwlock_unlock(this->otherSearchOpenListMutex);
    }

    if(g2IsInOtherClosedList || g2IsInOtherOpenList){
        
        if(!(*this->foundAPath) || g1 + g2 < *this->bestPathCost){
            pthread_rwlock_wrlock(this->bestPathMutex);
            *this->bestPathCost = g1 + g2;
            *this->foundAPath = true;
            this->middleNode = neighSearchNode;
            pthread_rwlock_unlock(this->bestPathMutex);
        }
    }
}

void ParallelASearch::barrierUntilMayContinue(){
    pthread_mutex_lock(this->hasNodesOpenListMutex);
    (*this->shouldStopCounter) += 1;

    if((*this->shouldStopCounter) == this->numThreadsMySearch){
        (*this->shouldStopCounter) = 0;

        //Se ainda estiver vazio, terminate!
        pthread_rwlock_rdlock(this->myOpenListMutex);
        if(this->myOpenList->empty()){
            *this->terminate = true;
        }

        pthread_rwlock_unlock(this->myOpenListMutex);

        //libera todos
        pthread_cond_broadcast(this->hasNodesOpenListCondVar);
    }else{
        while(pthread_cond_wait(this->hasNodesOpenListCondVar, this->hasNodesOpenListMutex)!=0);
    }

    pthread_mutex_unlock(this->hasNodesOpenListMutex);
}

void ParallelASearch::exploreNode(SearchGraphNode* currNode){
    pthread_rwlock_rdlock(this->bestPathMutex);
    pthread_rwlock_rdlock(this->otherSearchOpenListMutex);
    
    if(this->shouldExplore(currNode)){
        pthread_rwlock_unlock(this->bestPathMutex);
        pthread_rwlock_unlock(this->otherSearchOpenListMutex);

        std::unordered_map<unsigned int, double>* nodeNeighboors = currNode->getGraphNode()->getCostToOtherNodes();
        for(std::pair<unsigned int, double> neighboorsIt: *nodeNeighboors){

            //If this node isn't taken by another thread
            pthread_mutex_lock(this->currTakenNodesMutex);
            while(this->currTakenNodes->count(neighboorsIt.first) != 0){
                pthread_cond_wait(this->currTakenNodesCondVar, this->currTakenNodesMutex);
            }

            this->currTakenNodes->insert(neighboorsIt.first);
            pthread_mutex_unlock(this->currTakenNodesMutex);

            double pathCostToNeighboor = currNode->getPathCost() + neighboorsIt.second;
            
            bool shouldTryUpdateBestCost = true;
            SearchGraphNode* neighSearchNode = nullptr;
            //If neighboor is not in the closedList

            pthread_rwlock_rdlock(this->myClosedListMutex);
            if(this->myClosedList->count(neighboorsIt.first) == 0){
                pthread_rwlock_unlock(this->myClosedListMutex);

                pthread_rwlock_rdlock(this->myOpenListMutex);
                
                //If neighboor is not in the openList
                if(!this->myOpenList->hasNode(neighboorsIt.first)){
                    //First time beeing reached
                    pthread_rwlock_unlock(this->myOpenListMutex);

                    SearchGraphNode* neighSearchNode = new SearchGraphNode();
                    neighSearchNode->setGraphNode(&(this->myGraph->findNode(neighboorsIt.first)));
                    neighSearchNode->setLastActionCost(neighboorsIt.second);
                    neighSearchNode->setPathCost(pathCostToNeighboor);
                    float heuristic = myHeuristic->calculate(neighSearchNode->getGraphNode(), finalNode);
                    neighSearchNode->setTotalCost(pathCostToNeighboor + heuristic);
                    neighSearchNode->setParentNode(currNode);

                    pthread_rwlock_wrlock(this->searchNodesMutex);
                    this->searchNodesCreated->push_back(neighSearchNode);
                    pthread_rwlock_unlock(this->searchNodesMutex);

                    pthread_rwlock_wrlock(this->myOpenListMutex);
                    this->myOpenList->addAndCreateNodeFor(neighSearchNode);
                    pthread_rwlock_unlock(this->myOpenListMutex);

                    pthread_cond_signal(this->hasNodesOpenListCondVar);
                
                }else if(pathCostToNeighboor < this->myOpenList->findNode(neighboorsIt.first)->getPathCost()){
                    //If neighboor is in the openList
                    //and we just found a better path cost to it

                    BSTNode* bstNode = this->myOpenList->findNode(neighboorsIt.first);
                    pthread_rwlock_unlock(this->myOpenListMutex);

                    neighSearchNode = bstNode->getNode();

                    neighSearchNode->setPathCost(pathCostToNeighboor);
                    float heuristic = myHeuristic->calculate(neighSearchNode->getGraphNode(), finalNode);
                    neighSearchNode->setTotalCost(pathCostToNeighboor + heuristic);
                    neighSearchNode->setLastActionCost(neighboorsIt.second);
                    neighSearchNode->setParentNode(currNode);

                    pthread_rwlock_wrlock(this->myOpenListMutex);
                    this->myOpenList->updateNode(bstNode);
                    pthread_rwlock_unlock(this->myOpenListMutex);

                }else{
                    pthread_rwlock_unlock(this->myOpenListMutex);
                }
            }else{
                pthread_rwlock_unlock(this->myClosedListMutex);
                shouldTryUpdateBestCost = false;
            }

            if(shouldTryUpdateBestCost && neighSearchNode != nullptr){
                this->updateBestPathCostIfCan(pathCostToNeighboor, neighboorsIt.first, neighSearchNode);
            }

            //TALVEZ MUDAR PARA DAR O BROADCAST SÓ SE ESTIVER ALGUÉM ESPERANDO
            pthread_mutex_lock(this->currTakenNodesMutex);
            this->currTakenNodes->erase(neighboorsIt.first);
            pthread_mutex_unlock(this->currTakenNodesMutex);
            pthread_cond_broadcast(this->currTakenNodesCondVar);

        }
    }else{
        pthread_rwlock_unlock(this->bestPathMutex);
        pthread_rwlock_unlock(this->otherSearchOpenListMutex);
    }

    pthread_rwlock_wrlock(this->myClosedListMutex);
    this->myClosedList->insert(std::pair<unsigned int, double>(currNode->getNodeId(),currNode->getPathCost()));
    pthread_rwlock_unlock(this->myClosedListMutex);
}

void ParallelASearch::search(){

    this->exploredCount = 0;
    while(true){

        pthread_rwlock_wrlock(this->myOpenListMutex);
        pthread_rwlock_rdlock(this->terminateMutex);


        if(!this->myOpenList->empty() && !(*this->terminate)){

            SearchGraphNode* currNode = this->myOpenList->popMaxPriorityNode();

            pthread_rwlock_unlock(this->terminateMutex);
            pthread_rwlock_unlock(this->myOpenListMutex);
            pthread_mutex_lock(this->currTakenNodesMutex);
            this->currTakenNodes->insert(currNode->getNodeId());
            pthread_mutex_unlock(this->currTakenNodesMutex);
            
            this->exploreNode(currNode);

            pthread_mutex_lock(this->currTakenNodesMutex);
            this->currTakenNodes->erase(currNode->getNodeId());
            pthread_mutex_unlock(this->currTakenNodesMutex);
            pthread_cond_broadcast(this->currTakenNodesCondVar);

            this->exploredCount++;

        }else{
            pthread_rwlock_unlock(this->myOpenListMutex);

            if(*this->terminate){
                pthread_rwlock_unlock(this->terminateMutex);
                break;
            }
            pthread_rwlock_unlock(this->terminateMutex);

            this->barrierUntilMayContinue();

            pthread_rwlock_rdlock(this->terminateMutex);
            if(*this->terminate){
                pthread_rwlock_unlock(this->terminateMutex);
                break;
            }
            pthread_rwlock_unlock(this->terminateMutex);
        }

    }

    if(this->middleNode == nullptr){
        std::cout<<"Thread: "<<this->threadId<<" MIDDLE NODE NULLPTR!\n";
    }

}