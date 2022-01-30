#include "GraphNode.hpp"
#include "SearchGraphNode.hpp"
#include "GraphSearcher.hpp"
#include "FileToGraph.hpp"
#include <iostream>
#include <stack>

void printUsage(){
    std::cout<<"./pastar edgesFile nodePositionsFile originDestinyFile"<<std::endl;
}

int main(int argc, char const *argv[])
{
    if(argc != 4){
        printUsage();
        exit(1);
    }

    
    Graph myGraph;

    FileToGraph graphReader;
    std::cout<<"Started reading input files!\n";
    myGraph = graphReader.readGraphFrom(argv[1]);
    graphReader.readGraphPositions(argv[2], myGraph);
    graphReader.readPositionsForSearch(argv[3], myGraph);

    std::cout<<"Finished reading input files!\n";

    GraphSearcher graphSearcher;
    graphSearcher.setGraph(&myGraph);
    std::stack<unsigned int> path = graphSearcher.searchInGraph();
    std::cout<<"Solution Size: "<<path.size()<<std::endl;
    return 0;
}