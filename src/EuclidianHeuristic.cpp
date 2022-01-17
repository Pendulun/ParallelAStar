#include "EuclidianHeuristic.hpp"

float EuclidianHeuristic::calculate(GraphNode firstNode, GraphNode secondNode){
    return sqrt(pow(firstNode.getXPos() - secondNode.getXPos(), 2) + 
                            pow(firstNode.getYPos() - secondNode.getYPos(), 2));
}

EuclidianHeuristic::EuclidianHeuristic(/* args */){}
EuclidianHeuristic::~EuclidianHeuristic(){}