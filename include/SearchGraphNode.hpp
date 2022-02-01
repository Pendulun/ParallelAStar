#ifndef __SEARCHGRAPHNODE_H__
#define __SEARCHGRAPHNODE_H__
#include "GraphNode.hpp"

class SearchGraphNode{
private:
    SearchGraphNode* parentNode;
    double pathCostToNode;
    double totalCost;
    GraphNode* myGraphNode;
public:
    SearchGraphNode();
    ~SearchGraphNode();
    void setParentNode(SearchGraphNode* newParentNode);
    void setPathCost(const double pathCost);
    void setTotalCost(double totalCost);
    void setGraphNode(GraphNode* myGraphNode);
    SearchGraphNode* getParentNode();
    const double getPathCost();
    const double getTotalCost();
    GraphNode* getGraphNode();
    unsigned int getNodeId();
};

#endif