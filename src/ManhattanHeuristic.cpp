#include "ManhattanHeuristic.hpp"

float ManhattanHeuristic::calculate(GraphNode* firstNode, GraphNode* secondNode){
    float result = std::abs(firstNode->getXPos() - secondNode->getXPos()) + std::abs(firstNode->getYPos() - secondNode->getYPos());
    return result;
}

ManhattanHeuristic::ManhattanHeuristic(/* args */){}
ManhattanHeuristic::~ManhattanHeuristic(){}