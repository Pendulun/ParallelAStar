#ifndef __PARALLELASEARCH_H__
#define __PARALLELASEARCH_H__

#include <pthread.h>
#include <stack>
#include <map>
#include <list>
#include <set>

#include "Heuristic.hpp"
#include "Graph.hpp"
#include "GraphNode.hpp"
#include "SearchGraphNode.hpp"
#include "BST.hpp"

class ParallelASearch{

private:

    //Shared
    pthread_rwlock_t* myOpenListMutex;
    pthread_rwlock_t* otherSearchOpenListMutex;

    pthread_rwlock_t* myClosedListMutex;
    pthread_rwlock_t* otherSearchClosedListMutex;

    pthread_rwlock_t* bestPathMutex;
    pthread_rwlock_t* terminateMutex;
    pthread_rwlock_t* searchNodesMutex;
    pthread_cond_t* hasNodesOpenListCondVar;
    pthread_mutex_t* hasNodesOpenListMutex;
    pthread_cond_t* currTakenNodesCondVar;
    pthread_mutex_t* currTakenNodesMutex;

    unsigned int threadId;
    unsigned int initNodeId;
    unsigned int finalNodeId;
    unsigned int* shouldStopCounter;
    double* bestPathCost;
    bool* foundAPath;
    bool* terminate;

    Graph* myGraph;
    BST* myOpenList;
    BST* otherSearchOpenList;
    GraphNode* originNode;
    GraphNode* finalNode;
    SearchGraphNode* middleNode;
    std::stack<unsigned int>* pathToFinalNode;
    std::map<unsigned int, double>* myClosedList;
    std::map<unsigned int, double>* otherSearchClosedList;
    std::set<unsigned int>* currTakenNodes;
    std::list<SearchGraphNode*>* searchNodesCreated;
    Heuristic* myHeuristic;

    //NOT SHARED
    unsigned int numThreadsMySearch;
    unsigned int exploredCount;

    bool shouldTerminate();
    void barrierUntilMayContinue();
    void exploreNode(SearchGraphNode* currNode);
    bool shouldExplore(SearchGraphNode* currNode);
    void updateBestPathCostIfCan(double pathCostToCurrNeigh, const unsigned int neighId, SearchGraphNode* neighSearchNode);

public:
    ParallelASearch();
    ~ParallelASearch();
    
    void setMyOpenListMutex(pthread_rwlock_t& mutex);
    void setOtherSearchOpenListMutex(pthread_rwlock_t& mutex);
    void setMyClosedListMutex(pthread_rwlock_t& mutex);
    void setOtherSearchClosedListMutex(pthread_rwlock_t& mutex);
    void setBestPathMutex(pthread_rwlock_t& mutex);
    void setTerminateMutex(pthread_rwlock_t& mutex);
    void setSearchNodesMutex(pthread_rwlock_t& mutex);
    void setHasNodesOpenListCondVar(pthread_cond_t& condVar);
    void setHasNodesOpenListMutex(pthread_mutex_t& mutex);
    void setCurrTakenNodesCondVar(pthread_cond_t& condVar);
    void setCurrTakenNodesMutex(pthread_mutex_t& mutex);

    void setThreadId(unsigned int threadId);
    void setInitNodeId(unsigned int nodeId);
    void setFinalNodeId(unsigned int nodeId);
    void setNumThreadsMySearch(unsigned int numThreads);
    void setShouldStopCounter(unsigned int* shouldStop);
    void setHeuristic(Heuristic* heuristic);
    void setBestPathCost(double* bestPathCost);
    void setFoundPath(bool* foundPath);
    void setTerminate(bool* terminate);
    void setGraph(Graph* graph);
    void setPathToFinalNode(std::stack<unsigned int>* path);
    void setMyClosedList(std::map<unsigned int, double>* closedList);
    void setOtherSearchClosedList(std::map<unsigned int, double>* closedList);
    void setCurrTakenNodes(std::set<unsigned int>* currTaken);
    void setMyOpenList(BST* openList);
    void setOtherSearchOpenList(BST* openList);
    void setFinalNode(GraphNode* finalNode);
    void setMyOriginNode(GraphNode* originNode);
    void setSearchPathNodesCreated(std::list<SearchGraphNode*>*);
    void setMiddleNode(SearchGraphNode* middleNode);

    unsigned int getExploredCount();
    SearchGraphNode* getMiddleNode();

    std::stack<unsigned int> getPathToFinalNode();

    void search();
};

#endif