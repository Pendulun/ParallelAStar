#include "FileToGraph.hpp"

FileToGraph::FileToGraph(/* args */){
}

FileToGraph::~FileToGraph(){
}

Graph FileToGraph::readGraphFrom(const std::string fileName){
    Graph graph;

    std::string line;
    std::ifstream fileReader(fileName);

    unsigned int fromNodeIdx = 0;
    unsigned int toNodeIdx = 0;
    float edgeWeight = 0.0;
    while (getline (fileReader, line)) {
        this->getEdgeInfoFromLine(fromNodeIdx, toNodeIdx, edgeWeight, line);

        //MUDAR SE PARAR DE DUPLICAR AS LINHAS NO ARQUIVO DE ENTRADA
        graph.addDirectedEdge(fromNodeIdx, toNodeIdx, edgeWeight);

        fromNodeIdx = 0;
        toNodeIdx = 0;
        edgeWeight = 0.0;
    }

    fileReader.close();
    return graph;
}

void FileToGraph::getEdgeInfoFromLine(unsigned int &fromNodeIdx, unsigned int &toNodeIdx, float &edgeWeight, std::string &line){
    std::string delimiter = ",";
    //Pego as três informações
    size_t last = 0;
    size_t next = 0;

    //Popula as informações
    unsigned int infoCount = 0;
    while ((next = line.find(delimiter, last)) != std::string::npos) {
        std::string nodeId = line.substr(last, next-last);
        
        if(infoCount == 0){
            fromNodeIdx = std::stoul(nodeId, nullptr, 10);
        }else if(infoCount == 1){
            toNodeIdx = std::stoul(nodeId, nullptr, 10);
        }

        infoCount++;
        last = next + 1;
    }

    edgeWeight = std::stof(line.substr(last));
}

void FileToGraph::readGraphPositions(const std::string fileName, Graph& graph){
    std::string line;
    std::ifstream fileReader(fileName);

    unsigned int nodeIdx = 0;
    float xPos = 0;
    float yPos = 0.0;
    while (getline (fileReader, line)) {
        this->getPosInfoFromLine(nodeIdx, xPos, yPos, line);

        //MUDAR SE PARAR DE DUPLICAR AS LINHAS NO ARQUIVO DE ENTRADA
        GraphNode& node = graph.findNode(nodeIdx);

        node.setXPos(xPos);
        node.setYPos(yPos);

        nodeIdx = 0;
        yPos = 0;
        xPos = 0.0;
    }

    fileReader.close();
}

void FileToGraph::getPosInfoFromLine(unsigned int &nodeIdx, float &xPos, float &yPos, std::string &line){
    std::string delimiter = ",";
    size_t last = 0;
    size_t next = 0;

    //Popula as informações
    unsigned int infoCount = 0;
    while ((next = line.find(delimiter, last)) != std::string::npos) {
        std::string value = line.substr(last, next-last);
        
        if(infoCount == 0){
            nodeIdx = std::stoul(value, nullptr, 10);
        }else if(infoCount == 1){
            xPos = std::stof(value);
        }

        infoCount++;
        last = next + 1;
    }

    yPos = std::stof(line.substr(last));
}

void FileToGraph::readPositionsForSearch(const std::string fileName, Graph& graph){
    std::string line;
    std::ifstream fileReader(fileName);

    unsigned int initialNodeIdx = 0;
    unsigned int finalNodeIdx = 0;
    while (getline (fileReader, line)) {
        this->getSearchInfoFromLine(initialNodeIdx, finalNodeIdx, line);

       graph.setInitialPosition(initialNodeIdx);
       graph.setFinalPosition(finalNodeIdx);
    }

    fileReader.close();
}

void FileToGraph::getSearchInfoFromLine(unsigned int &initialNodeIdx, unsigned int &finalNodeIdx, std::string &line){
    std::string delimiter = ",";
    size_t last = 0;
    size_t next = 0;

    //Popula as informações
    while ((next = line.find(delimiter, last)) != std::string::npos) {
        std::string value = line.substr(last, next-last);
        initialNodeIdx = std::stoul(value, nullptr, 10);
        last = next + 1;
    }

    finalNodeIdx = std::stoul(line.substr(last), nullptr, 10);
}