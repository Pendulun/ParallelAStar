#ifndef __SEARCHGRAPHNODE_H__
#define __SEARCHGRAPHNODE_H__

class SearchGraphNode{
private:
    SearchGraphNode* parentNode;
    unsigned int pathCostToNode;
    //Last Action
public:
    SearchGraphNode(/* args */);
    ~SearchGraphNode();
    void setParentNode(SearchGraphNode* newParentNode);
    void setPathCost(const unsigned int pathCost);
    SearchGraphNode* getParentNode();
    const unsigned int getPathCost();
};

#endif