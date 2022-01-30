#ifndef __HEURISTIC_H__
#define __HEURISTIC_H__
#include "GraphNode.hpp"

class Heuristic{
private:
    /* data */
public:
    Heuristic(/* args */);
    virtual ~Heuristic();

    virtual float calculate(GraphNode* firstNode, GraphNode* secondNode) = 0;
};
#endif