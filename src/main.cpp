#include "GraphNode.hpp"
#include "SearchGraphNode.hpp"
#include "GraphSearcher.hpp"
#include "FileToGraph.hpp"
#include <iostream>
#include <stdlib.h>
#include <stack>
#include <chrono>

void printUsage(){
    std::cout<<"./pastar edgesFile nodePositionsFile originDestinyFile <numThreads>"<<std::endl;
}

int main(int argc, char const *argv[])
{
    if(argc != 4 && argc != 5){
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
    std::cout<<"First node: "<<myGraph.getInitialPos()<<" End node: "<<myGraph.getFinalPos()<<std::endl;

    GraphSearcher graphSearcher;
    graphSearcher.setGraph(&myGraph);
    std::stack<unsigned int> path;
    
    if(argc == 4){
        path = graphSearcher.searchInGraph();
    }else{
        path = graphSearcher.parallelSearchInGraph(atoi(argv[4]));
    }
    
    if(!path.empty()){
        std::cout<<"Nodes explored count: "<<graphSearcher.getNodesExploredCount()<<std::endl;
        std::cout<<"Solution Size: "<<path.size()<<std::endl;

        std::cout<<"[";
        while(!path.empty()){
            unsigned int nodeId = path.top();
            path.pop();
            std::cout<<nodeId<<", ";
        }

        std::cout<<"]\n";

        std::cout<<"Total cost: "<<graphSearcher.getTotalCost()<<std::endl;
        std::cout<<"Path cost: "<<graphSearcher.getPathCost()<<std::endl;
    }else{
        std::cout<<"Could not find a path!\n";
    }

    return 0;
}