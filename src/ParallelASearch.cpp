#include "ParallelASearch.hpp"


ParallelASearch::ParallelASearch(){

}

ParallelASearch::~ParallelASearch(){

}


void ParallelASearch::setMyOpenListMutex(pthread_rwlock_t* mutex){
    this->myOpenListMutex = mutex;
}

void ParallelASearch::setOtherSearchOpenListMutex(pthread_rwlock_t* mutex){
    this->otherSearchOpenListMutex = mutex;
}

void ParallelASearch::setMyClosedListMutex(pthread_rwlock_t* mutex){
    this->myClosedListMutex = mutex;
}

void ParallelASearch::setOtherSearchClosedListMutex(pthread_rwlock_t* mutex){
    this->otherSearchClosedListMutex = mutex;
}

void ParallelASearch::setBestPathMutex(pthread_rwlock_t* mutex){
    this->bestPathMutex = mutex;
}

void ParallelASearch::setTerminateMutex(pthread_rwlock_t* mutex){
    this->terminateMutex = mutex;
}

void ParallelASearch::setSearchNodesMutex(pthread_rwlock_t* mutex){
    this->searchNodesMutex = mutex;
}

void ParallelASearch::setHasNodesOpenListCondVar(pthread_cond_t* condVar){
    this->hasNodesOpenList = condVar;
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

void ParallelASearch::setMyOpenList(BST* openList){
    this->myOpenList = openList;
}

void ParallelASearch::setOtherSearchOpenList(BST* openList){
    this->otherSearchOpenList = openList;
}

std::stack<unsigned int> ParallelASearch::getPathToFinalNode(){
    return (*this->pathToFinalNode);
}

void ParallelASearch::sayHi(){
    std::cout<<"Hello from thread "<<this->threadId<<std::endl;
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

bool ParallelASearch::shouldTerminate(){
    bool shouldTerminate = false;
    pthread_rwlock_rdlock(this->terminateMutex);
    shouldTerminate = *this->terminate;
    pthread_rwlock_unlock(this->terminateMutex);
    return shouldTerminate;
}

bool ParallelASearch::shouldExplore(SearchGraphNode* currNode){
    if(!this->foundAPath){
        return true;
    }

    float otherSearchHeuristic = myHeuristic->calculate(currNode->getGraphNode(), this->originNode);
    bool betterTotalCost = currNode->getTotalCost() < *this->bestPathCost;
    bool lowEnoughTotalCost = currNode->getPathCost() + this->otherSearchOpenList->peekMaxPriority() - otherSearchHeuristic < *this->bestPathCost;
    return (betterTotalCost && lowEnoughTotalCost);
}

void ParallelASearch::attBetterPathCostIfCan(double g1, double g2, const unsigned int nodeId){
    pthread_rwlock_rdlock(this->otherSearchClosedListMutex);

    if(this->otherSearchClosedList->count(nodeId) > 0 && g1 + g2 > *this->bestPathCost){
        
    }

    pthread_rwlock_unlock(this->otherSearchClosedListMutex);
}

void ParallelASearch::search(){
    //Used to delete all SearchGraphNode created
    std::list<SearchGraphNode*> searchGraphNodescreated;

    unsigned int exploredCount = 0;
    while(!this->shouldTerminate()){
        
        //CRIAR MAIS UM MUTEX NORMAL PARA SER USADO NA COND_WAIT
        pthread_rwlock_wrlock(this->myOpenListMutex);

        while(this->myOpenList->empty() && !this->shouldTerminate()){
            pthread_cond_wait(this->hasNodesOpenList, this->myOpenListMutex);
        }

        if(this->shouldTerminate()){
            pthread_rwlock_unlock(this->myOpenListMutex);
            break;
        }

        SearchGraphNode* currNode = this->myOpenList->popMaxPriorityNode();

        pthread_rwlock_unlock(this->myOpenListMutex);

        //A ideia agora, não é encontrar o nó final, mas sim, o nó no meio do caminho

        // //If it is the goal
        // if(currNode->getGraphNode()->getId() == finalNode->getId()){
        //     this->totalCost = currNode->getTotalCost();
        //     this->pathCost = currNode->getPathCost();
        //     this->nodesExploredCount = exploredCount;

        //     pathToFinalNode = this->getPathTo(currNode);
            
        //     //Delete all SearchGraphNodes created
        //     while(!searchGraphNodescreated.empty()){
        //         delete searchGraphNodescreated.front();
        //         searchGraphNodescreated.pop_front();
        //     }            
        //     delete openList;

        //     return pathToFinalNode;
        // }

        
        pthread_rwlock_rdlock(this->bestPathMutex);
        pthread_rwlock_rdlock(this->otherSearchOpenListMutex);
        
        if(this->shouldExplore(currNode)){
            pthread_rwlock_unlock(this->bestPathMutex);

            std::unordered_map<unsigned int, double>* nodeNeighboors = currNode->getGraphNode()->getCostToOtherNodes();
            for(std::pair<unsigned int, double> neighboorsIt: *nodeNeighboors){
                
                double pathCostToNeighboor = currNode->getPathCost() + neighboorsIt.second;
                
                bool shouldTryUpdateBestCost = true;
                //If neighboor is not in the closedList
                pthread_rwlock_rdlock(this->myClosedListMutex);
                if(this->myClosedList->count(neighboorsIt.first) == 0){
                    pthread_rwlock_unlock(this->myClosedListMutex);

                    pthread_rwlock_rdlock(this->myOpenListMutex);

                    //If neighboor is not in the openList
                    if(!this->myOpenList->hasNode(neighboorsIt.first)){
                        pthread_rwlock_unlock(this->myOpenListMutex);

                        SearchGraphNode* newSearchGraphNode = new SearchGraphNode();
                        newSearchGraphNode->setGraphNode(&(this->myGraph->findNode(neighboorsIt.first)));
                        newSearchGraphNode->setLastActionCost(neighboorsIt.second);
                        newSearchGraphNode->setPathCost(pathCostToNeighboor);
                        float heuristic = myHeuristic->calculate(newSearchGraphNode->getGraphNode(), finalNode);
                        newSearchGraphNode->setTotalCost(pathCostToNeighboor + heuristic);
                        newSearchGraphNode->setParentNode(currNode);

                        pthread_rwlock_wrlock(this->searchNodesMutex);
                        searchGraphNodescreated.push_back(newSearchGraphNode);
                        pthread_rwlock_unlock(this->searchNodesMutex);

                        pthread_rwlock_wrlock(this->myOpenListMutex);
                        this->myOpenList->addAndCreateNodeFor(newSearchGraphNode);
                        pthread_rwlock_unlock(this->myOpenListMutex);
                    
                    }else if(pathCostToNeighboor < this->myOpenList->findNode(neighboorsIt.first)->getPathCost()){
                        //If neighboor is in the openList
                        //and its saved path cost is greater than current path cost to it

                        BSTNode* bstNode = this->myOpenList->findNode(neighboorsIt.first);
                        pthread_rwlock_unlock(this->myOpenListMutex);

                        SearchGraphNode* searchNode = bstNode->getNode();

                        searchNode->setPathCost(pathCostToNeighboor);
                        float heuristic = myHeuristic->calculate(searchNode->getGraphNode(), finalNode);
                        searchNode->setTotalCost(pathCostToNeighboor + heuristic);
                        searchNode->setLastActionCost(neighboorsIt.second);
                        searchNode->setParentNode(currNode);

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

                if(shouldTryUpdateBestCost){
                    double g1 = pathCostToNeighboor;
                    double g2 = 0.0;
                    
                    bool g2IsInOtherClosedList = false;
                    bool g2IsInOtherOpenList = false;

                    pthread_rwlock_rdlock(this->otherSearchClosedListMutex);
                    if(this->otherSearchClosedList->count(neighboorsIt.first)){
                        g2 = this->otherSearchClosedList->at(neighboorsIt.first);
                        g2IsInOtherClosedList = true;
                    }

                    pthread_rwlock_unlock(this->otherSearchClosedListMutex);
                    
                    if(!g2IsInOtherClosedList){
                        pthread_rwlock_rdlock(this->otherSearchOpenListMutex);
                        if(this->otherSearchOpenList->hasNode(neighboorsIt.first)){
                            g2 = this->otherSearchOpenList->findNode(neighboorsIt.first)->getPathCost();
                            g2IsInOtherOpenList = true;
                        }
                        pthread_rwlock_unlock(this->otherSearchOpenListMutex);
                    }

                    if(g2IsInOtherClosedList || g2IsInOtherOpenList){
                        
                        if(g1 + g2 > *this->bestPathCost){
                            pthread_rwlock_wrlock(this->bestPathMutex);
                            *this->bestPathCost = g1 + g2;
                            *this->foundAPath = true;
                            pthread_rwlock_unlock(this->bestPathMutex);
                        }
                    }
                }

            }
        }else{
            pthread_rwlock_unlock(this->bestPathMutex);
            pthread_rwlock_unlock(this->otherSearchOpenListMutex);
        }

        pthread_rwlock_wrlock(this->myClosedListMutex);
        this->myClosedList->insert(std::pair<unsigned int, double>(currNode->getNodeId(),currNode->getPathCost()));
        pthread_rwlock_unlock(this->myClosedListMutex);
        
        //DEFINIR COMO IDENTIFCAR QUE A PESQUISA DEVE ACABAR
        pthread_rwlock_rdlock(this->myOpenListMutex);
        if(this->myOpenList->empty()){
            //this->terminateMutex
        }
        pthread_rwlock_unlock(this->myOpenListMutex);
    }
    
    //Delete all SearchGraphNodes
    while(!searchGraphNodescreated.empty()){
        delete searchGraphNodescreated.front();
        searchGraphNodescreated.pop_front();
    }

    //DELETAR OPEN LIST DAS PESQUISAS

    //Espera as threads parceiras chegarem

}