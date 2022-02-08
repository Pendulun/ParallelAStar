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
    pthread_rwlock_t* myOpenListMutex;
    pthread_rwlock_t* otherSearchOpenListMutex;

    pthread_rwlock_t* myClosedListMutex;
    pthread_rwlock_t* otherSearchClosedListMutex;

    pthread_rwlock_t* bestPathMutex;
    pthread_rwlock_t* terminateMutex;
    pthread_rwlock_t* searchNodesMutex;
    pthread_cond_t* hasNodesOpenList;

    unsigned int threadId;
    unsigned int initNodeId;
    unsigned int finalNodeId;
    double* bestPathCost;
    bool* foundAPath;
    bool* terminate;

    Graph* myGraph;
    BST* myOpenList;
    BST* otherSearchOpenList;
    GraphNode* originNode;
    GraphNode* finalNode;
    std::stack<unsigned int>* pathToFinalNode;
    std::map<unsigned int, double>* myClosedList;
    std::map<unsigned int, double>* otherSearchClosedList;
    std::list<SearchGraphNode*>* searchNodesCreated;
    Heuristic* myHeuristic;

    bool shouldTerminate();
    bool shouldExplore(SearchGraphNode* currNode);
    void attBetterPathCostIfCan(double g1, double g2, const unsigned int nodeId);

public:
    ParallelASearch();
    ~ParallelASearch();
    
    void setMyOpenListMutex(pthread_rwlock_t* mutex);
    void setOtherSearchOpenListMutex(pthread_rwlock_t* mutex);
    void setMyClosedListMutex(pthread_rwlock_t* mutex);
    void setOtherSearchClosedListMutex(pthread_rwlock_t* mutex);
    void setBestPathMutex(pthread_rwlock_t* mutex);
    void setTerminateMutex(pthread_rwlock_t* mutex);
    void setSearchNodesMutex(pthread_rwlock_t* mutex);
    void setHasNodesOpenListCondVar(pthread_cond_t* condVar);

    void setThreadId(unsigned int threadId);
    void setInitNodeId(unsigned int nodeId);
    void setFinalNodeId(unsigned int nodeId);
    void setHeuristic(Heuristic* heuristic);
    void setBestPathCost(double* bestPathCost);
    void setFoundPath(bool* foundPath);
    void setTerminate(bool* terminate);
    void setGraph(Graph* graph);
    void setPathToFinalNode(std::stack<unsigned int>* path);
    void setMyClosedList(std::map<unsigned int, double>* closedList);
    void setOtherSearchClosedList(std::map<unsigned int, double>* closedList);
    void setMyOpenList(BST* openList);
    void setOtherSearchOpenList(BST* openList);
    void setFinalNode(GraphNode* finalNode);
    void setMyOriginNode(GraphNode* originNode);
    void setSearchPathNodesCreated(std::list<SearchGraphNode*>*);

    std::stack<unsigned int> getPathToFinalNode();
    void sayHi();

    void search();
};

#endif