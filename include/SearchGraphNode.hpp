#ifndef __SEARCHGRAPHNODE_H__
#define __SEARCHGRAPHNODE_H__
#include "GraphNode.hpp"

class SearchGraphNode{
private:
    SearchGraphNode* parentNode;
    double pathCostToNode;
    double totalCost;
    double lastActionCost;
    GraphNode* myGraphNode;
public:
    SearchGraphNode();
    ~SearchGraphNode();
    void setParentNode(SearchGraphNode* newParentNode);
    void setPathCost(double pathCost);
    void setTotalCost(double totalCost);
    void setLastActionCost(double lastActionCost);
    void setGraphNode(GraphNode* myGraphNode);
    SearchGraphNode* getParentNode();
    double getPathCost();
    double getTotalCost();
    double getLastActionCost();
    GraphNode* getGraphNode();
    unsigned int getNodeId();
};

#endif