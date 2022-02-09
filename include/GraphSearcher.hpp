#ifndef __GRAPHSEARCHER_H__
#define __GRAPHSEARCHER_H__

#include <queue>
#include <map>
#include <utility>
#include <vector>
#include <set>
#include <stack>
#include <list>
#include <unordered_map>
#include <iterator>
#include <pthread.h>

#include <iostream>

#include "Graph.hpp"
#include "Heuristic.hpp"
#include "ManhattanHeuristic.hpp"
#include "EuclidianHeuristic.hpp"
#include "ZeroHeuristic.hpp"
#include "SearchGraphNode.hpp"
#include "BST.hpp"
#include "BSTNode.hpp"
#include "ParallelASearch.hpp"

class GraphSearcher{
public:
    enum searchType{ASTAR};
    enum heuristicType{MANHATTAN, EUCLIDIAN, ZERO};

    GraphSearcher();
    ~GraphSearcher();

    void setSearchType(searchType newSearchType);
    searchType getSearchType();

    void setHeuristicType(heuristicType newHeuristic);
    heuristicType getHeuristicType();

    void setGraph(Graph* newGraph);
    void setInitialNode(unsigned int initialNodeId);

    std::stack<unsigned int> searchInGraph();
    std::stack<unsigned int> parallelSearchInGraph(unsigned int numThreads);

    float getTotalCost();
    float getPathCost();
    unsigned int getNodesExploredCount();

private:
    void printStack(std::stack<unsigned int>);
    GraphSearcher::searchType mySearchType;
    GraphSearcher::heuristicType myHeuristicType;
    Graph* myGraph;
    float totalCost;
    float pathCost;
    unsigned int nodesExploredCount;

    unsigned int myInitialNodeId;
    std::stack<unsigned int> astarSearch(Heuristic* myHeuristic);

    std::stack<unsigned int> parallelAstarSearch(Heuristic* myHeuristic, unsigned int numThreads);
    static void* oneWaySearch(void* args);

    struct ThreadConfig{
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
        std::set<unsigned int> currTakenNodes;
        std::list<SearchGraphNode*>* searchNodesCreated;
        Heuristic* myHeuristic;
    };

    std::stack<unsigned int> combineTwoWaySearchesPath(std::stack<unsigned int>, std::stack<unsigned int>);
    SearchGraphNode* populateInitialNodeOpenList(GraphNode* originNode, GraphNode* finalNode, Heuristic* myHeuristic);
    void initializeSearchNodesCreated(std::list<SearchGraphNode*>&, BST&, GraphNode&, GraphNode&, Heuristic*);
    void defineNumThreadsPerSearch(const unsigned int numThreads, unsigned int* numThreadsPerSearch);
    
    std::stack<unsigned int> getPathTo(SearchGraphNode* finalNode);
    Heuristic* getHeuristic();
};
#endif