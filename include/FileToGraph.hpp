#ifndef __FILETOGRAPH_H__
#define __FILETOGRAPH_H__

#include "Graph.hpp"
#include "GraphNode.hpp"

#include <string>
#include <iostream>
#include <fstream>

class FileToGraph{
private:
    void getEdgeInfoFromLine(unsigned int &fromNodeIdx, unsigned int &toNodeIdx, float &edgeWeight, std::string &line);
    void getPosInfoFromLine(unsigned int &nodeIdx, float &xPos, float &yPos, std::string &line);
    void getSearchInfoFromLine(unsigned int &initialNodeIdx, unsigned int &finalNodeIdx, std::string &line);

public:
    FileToGraph(/* args */);
    ~FileToGraph();
    Graph readGraphFrom(const std::string fileName);
    void readGraphPositions(const std::string fileName, Graph& graph);
    void readPositionsForSearch(const std::string fileName, Graph& graph);
};


#endif