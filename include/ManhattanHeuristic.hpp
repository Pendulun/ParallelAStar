#ifndef __MANHATTANHEURISTIC_H__
#define __MANHATTANHEURISTIC_H__
#include "Heuristic.hpp"
#include <cstdlib>

class ManhattanHeuristic: public Heuristic
{
private:
    /* data */
public:
    ManhattanHeuristic(/* args */);
    ~ManhattanHeuristic();

    float calculate(GraphNode* firstNode, GraphNode* secondNode);
};
#endif