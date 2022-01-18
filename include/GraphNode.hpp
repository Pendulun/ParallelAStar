#ifndef __GRAPHNODE_H__
#define __GRAPHNODE_H__
#include <unordered_map>

class GraphNode
{
private:
    std::unordered_map<unsigned int, unsigned int> costToOtherNodes;
    float xPos;
    float yPos;
    unsigned int id;

public:
    GraphNode(/* args */);
    ~GraphNode();
    void addReachableNode(unsigned int nodeId, unsigned int cost);
    void setXPos(float newXPos);
    void setYPos(float newYPos);
    float getXPos();
    float getYPos();
    void setId(unsigned int newId);
    unsigned int getId();
    
};
#endif