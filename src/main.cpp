#include "GraphNode.hpp"
#include "SearchGraphNode.hpp"
#include "GraphSearcher.hpp"
#include "FileToGraph.hpp"
#include <iostream>
#include <stack>
#include <chrono>

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
    std::stack<unsigned int> path;
    std::chrono::milliseconds execSumTime = std::chrono::milliseconds(0);;
    int numIterations = 1;
    for(int i = 0; i < numIterations; i++){
        std::cout<<"Iteration "<<i<<"\n";
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        //path = graphSearcher.searchInGraph();
        path = graphSearcher.parallelSearchInGraph(4);
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        execSumTime += std::chrono::duration_cast<std::chrono::milliseconds> (t2 - t1);
    }  
    unsigned int meanTime = execSumTime.count()/numIterations;
    std::cout<<"Mean Time after "<<numIterations<<": "<<meanTime<<std::endl;
    
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