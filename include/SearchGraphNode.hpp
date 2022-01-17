#ifndef __SEARCHGRAPHNODE_H__
#define __SEARCHGRAPHNODE_H__

class SearchGraphNode{
private:
    SearchGraphNode* parentNode;
    unsigned int pathCostToNode;
    unsigned int nodeId;
    //Last Action
public:
    SearchGraphNode();
    ~SearchGraphNode();
    void setParentNode(SearchGraphNode* newParentNode);
    void setPathCost(const unsigned int pathCost);
    void setNodeId(unsigned int nodeId);
    SearchGraphNode* getParentNode();
    const unsigned int getPathCost();
    unsigned int getNodeId();
};

#endif