#include "ManhattanHeuristic.hpp"

float ManhattanHeuristic::calculate(GraphNode* firstNode, GraphNode* secondNode){
    float result = abs(firstNode->getXPos() - secondNode->getXPos()) + abs(firstNode->getYPos() - secondNode->getYPos());
    return result;
}

ManhattanHeuristic::ManhattanHeuristic(/* args */){}
ManhattanHeuristic::~ManhattanHeuristic(){}