#ifndef __PARALLELASEARCH_H__
#define __PARALLELASEARCH_H__

#include <pthread.h>
#include <stack>

#include "Heuristic.hpp"
#include "Graph.hpp"
#include "BST.hpp"

class ParallelASearch{

private:
    pthread_mutex_t* myOpenListMutex;
    pthread_mutex_t* otherSearchOpenListMutex;
    pthread_mutex_t* myClosedListMutex;
    pthread_mutex_t* otherSearchClosedListMutex;
    pthread_mutex_t* bestPathMutex;

    unsigned int threadId;
    unsigned int initNodeId;
    unsigned int finalNodeId;
    unsigned int* bestPathCost;
    bool* foundAPath;

    Graph* myGraph;
    BST* openList;
    std::stack<unsigned int>* pathToFinalNode;
    std::set<unsigned int>* myClosedList;
    std::set<unsigned int>* otherSearchClosedList;

    Heuristic* myHeuristic;

public:
    ParallelASearch();
    ~ParallelASearch();
    
    void setMyOpenListMutex(pthread_mutex_t* mutex);
    void setOtherSearchOpenListMutex(pthread_mutex_t* mutex);
    void setMyClosedListMutex(pthread_mutex_t* mutex);
    void setOtherSearchClosedListMutex(pthread_mutex_t* mutex);
    void setBestPathMutex(pthread_mutex_t* mutex);

    void setThreadId(unsigned int threadId);
    void setInitNodeId(unsigned int nodeId);
    void setFinalNodeId(unsigned int nodeId);
    void setHeuristic(Heuristic* heuristic);
    void setBestPathCost(unsigned int* bestPathCost);
    void setFoundPath(bool* foundPath);
    void setGraph(Graph* graph);
    void setPathToFinalNode(std::stack<unsigned int>* path);
    void setMyClosedList(std::set<unsigned int>* closedList);
    void setOtherSearchClosedList(std::set<unsigned int>* closedList);
    void setOpenList(BST* openList);

    std::stack<unsigned int> getPathToFinalNode();
    void sayHi();
};

#endif