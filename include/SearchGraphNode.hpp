#ifndef __SEARCHGRAPHNODE_H__
#define __SEARCHGRAPHNODE_H__
#include "GraphNode.hpp"

class SearchGraphNode{
private:
    SearchGraphNode* parentNode;
    unsigned int pathCostToNode;
    float totalCost;
    GraphNode* myGraphNode;
public:
    SearchGraphNode();
    ~SearchGraphNode();
    void setParentNode(SearchGraphNode* newParentNode);
    void setPathCost(const unsigned int pathCost);
    void setTotalCost(float totalCost);
    void setGraphNode(GraphNode* myGraphNode);
    SearchGraphNode* getParentNode();
    const unsigned int getPathCost();
    const float getTotalCost();
    GraphNode* getGraphNode();
    unsigned int getNodeId();
};

#endif