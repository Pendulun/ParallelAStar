#ifndef __GRAPHNODE_H__
#define __GRAPHNODE_H__
#include <list>

class GraphNode
{
private:
    std::list<GraphNode> childNodes;    
public:
    GraphNode(/* args */);
    ~GraphNode();
    void addChildNode(GraphNode newChildNode);

};
#endif