#include "ParallelASearch.hpp"


ParallelASearch::ParallelASearch(){

}

ParallelASearch::~ParallelASearch(){

}


void ParallelASearch::setMyOpenListMutex(pthread_mutex_t* mutex){
    this->myOpenListMutex = mutex;
}

void ParallelASearch::setOtherSearchOpenListMutex(pthread_mutex_t* mutex){
    this->otherSearchOpenListMutex = mutex;
}

void ParallelASearch::setMyClosedListMutex(pthread_mutex_t* mutex){
    this->closedList1Mutex = mutex;
}

void ParallelASearch::setOtherSearchClosedListMutex(pthread_mutex_t* mutex){
    this->closedList2Mutex = mutex;
}

void ParallelASearch::setBestPathMutex(pthread_mutex_t* mutex){
    this->bestPathMutex = mutex;
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

void ParallelASearch::setBestPathCost(unsigned int* bestPathCost){
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

void ParallelASearch::setMyClosedList(std::set<unsigned int>* closedList){
    this->myClosedList = closedList;
}

void ParallelASearch::setOtherSearchClosedList(std::set<unsigned int>* closedList){
    this->otherSearchClosedList = closedList;
}

void ParallelASearch::setOpenList(BST* openList){
    this->openList = openList;
}

std::stack<unsigned int> ParallelASearch::getPathToFinalNode(){
    return (*this->pathToFinalNode);
}

void ParallelASearch::sayHi(){
    std::cout<<"Hello from thread "<<this->threadId<<std::endl;
}