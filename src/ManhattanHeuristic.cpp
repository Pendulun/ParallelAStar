#include "ManhattanHeuristic.hpp"

float ManhattanHeuristic::calculate(GraphNode* firstNode, GraphNode* secondNode){
    return abs(firstNode->getXPos() - secondNode->getXPos()) + abs(firstNode->getYPos() - secondNode->getYPos());
}

ManhattanHeuristic::ManhattanHeuristic(/* args */){}
ManhattanHeuristic::~ManhattanHeuristic(){}