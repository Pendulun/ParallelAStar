#ifndef __EUCLIDIANHEURISTIC_H__
#define __EUCLIDIANHEURISTIC_H__
#include "Heuristic.hpp"
#include <cmath>

class EuclidianHeuristic: public Heuristic
{
private:
    /* data */
public:
    EuclidianHeuristic(/* args */);
    ~EuclidianHeuristic();

    float calculate(GraphNode* firstNode, GraphNode* secondNode);
};
#endif