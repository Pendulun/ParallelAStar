#ifndef __ZEROHEURISTIC_H__
#define __ZEROHEURISTIC_H__
#include "Heuristic.hpp"
#include <cmath>

class ZeroHeuristic: public Heuristic
{
private:
    /* data */
public:
    ZeroHeuristic(/* args */);
    ~ZeroHeuristic();

    float calculate(GraphNode* firstNode, GraphNode* secondNode);
};
#endif