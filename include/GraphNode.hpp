#ifndef __GRAPHNODE_H__
#define __GRAPHNODE_H__
#include <unordered_map>
#include <iterator>
#include <iostream>

class GraphNode
{
private:
    std::unordered_map<unsigned int, double> costToOtherNodes;
    float xPos;
    float yPos;
    unsigned int id;

public:
    GraphNode(/* args */);
    ~GraphNode();
    void addReachableNode(unsigned int nodeId, double cost);
    void setXPos(float newXPos);
    void setYPos(float newYPos);
    float getXPos();
    float getYPos();
    void setId(unsigned int newId);
    void printMyInfo();
    unsigned int getId();
    std::unordered_map<unsigned int, double>* getCostToOtherNodes();
    
};
#endif