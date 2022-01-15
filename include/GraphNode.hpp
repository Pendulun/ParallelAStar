#ifndef __GRAPHNODE_H__
#define __GRAPHNODE_H__
#include <list>

class GraphNode
{
private:
    std::list<GraphNode> childNodes;
    unsigned int xPos;
    unsigned int yPos;    
public:
    GraphNode(/* args */);
    ~GraphNode();
    void addChildNode(GraphNode newChildNode);
    void setXPos(unsigned int newXPos);
    void setYPos(unsigned int newYPos);
    unsigned int getXPos();
    unsigned int getYPos();
    
};
#endif