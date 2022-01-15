#ifndef __GRAPHNODE_H__
#define __GRAPHNODE_H__
#include <unordered_map>

class GraphNode
{
private:
    std::unordered_map<unsigned int, unsigned int> costToOtherNodes;
    unsigned int xPos;
    unsigned int yPos;
    unsigned int id;

public:
    GraphNode(/* args */);
    ~GraphNode();
    void addReachableNode(unsigned int nodeId, unsigned int cost);
    void setXPos(unsigned int newXPos);
    void setYPos(unsigned int newYPos);
    unsigned int getXPos();
    unsigned int getYPos();
    void setId(unsigned int newId);
    unsigned int getId();
    
};
#endif