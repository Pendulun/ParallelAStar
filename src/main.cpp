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
    std::cout<<"First node: "<<myGraph.getInitialPos()<<" End node: "<<myGraph.getFinalPos()<<std::endl;

    GraphSearcher graphSearcher;
    graphSearcher.setGraph(&myGraph);
    //graphSearcher.setHeuristicType(GraphSearcher::heuristicType::EUCLIDIAN);
    //graphSearcher.setHeuristicType(GraphSearcher::heuristicType::ZERO);
    std::stack<unsigned int> path = graphSearcher.searchInGraph();
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

    return 0;
}