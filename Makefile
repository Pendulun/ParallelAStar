EXEC=main
CXX = g++ 
CXXFLAGS = -Wall -g
BUILD=./build/
SRC=./src/
INCLUDE=./include/
GRAPHS=./testGraphs/

GRAPHSEARCHERDEPENDENCIES= $(BUILD)Graph.o $(BUILD)SearchGraphNode.o $(BUILD)Heuristic.o $(BUILD)ManhattanHeuristic.o $(BUILD)EuclidianHeuristic.o $(BUILD)ZeroHeuristic.o $(BUILD)BST.o $(BUILD)BSTNode.o

all: ${EXEC}

${EXEC}: $(BUILD)main.o $(BUILD)FileToGraph.o $(BUILD)GraphNode.o $(BUILD)GraphSearcher.o $(GRAPHSEARCHERDEPENDENCIES)
	${CXX} ${CXXFLAGS} -o ${EXEC} $(BUILD)main.o $(BUILD)GraphNode.o $(BUILD)GraphSearcher.o $(BUILD)FileToGraph.o $(GRAPHSEARCHERDEPENDENCIES)

$(BUILD)main.o: $(SRC)main.cpp $(BUILD)FileToGraph.o $(BUILD)GraphNode.o $(BUILD)SearchGraphNode.o $(BUILD)GraphSearcher.o
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)main.cpp -o $(BUILD)main.o

$(BUILD)GraphNode.o: $(SRC)GraphNode.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)GraphNode.cpp -o $(BUILD)GraphNode.o

$(BUILD)SearchGraphNode.o: $(SRC)SearchGraphNode.cpp $(BUILD)GraphNode.o
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)SearchGraphNode.cpp -o $(BUILD)SearchGraphNode.o

$(BUILD)GraphSearcher.o: $(SRC)GraphSearcher.cpp $(GRAPHSEARCHERDEPENDENCIES)
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)GraphSearcher.cpp -o $(BUILD)GraphSearcher.o

$(BUILD)Graph.o: $(SRC)Graph.cpp $(BUILD)GraphNode.o $(BUILD)Heuristic.o
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)Graph.cpp -o $(BUILD)Graph.o

$(BUILD)Heuristic.o: $(BUILD)GraphNode.o $(SRC)Heuristic.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)Heuristic.cpp -o $(BUILD)Heuristic.o

$(BUILD)ManhattanHeuristic.o: $(BUILD)Heuristic.o $(SRC)ManhattanHeuristic.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)ManhattanHeuristic.cpp -o $(BUILD)ManhattanHeuristic.o

$(BUILD)EuclidianHeuristic.o: $(BUILD)Heuristic.o $(SRC)EuclidianHeuristic.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)EuclidianHeuristic.cpp -o $(BUILD)EuclidianHeuristic.o

$(BUILD)ZeroHeuristic.o: $(BUILD)Heuristic.o $(SRC)ZeroHeuristic.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)ZeroHeuristic.cpp -o $(BUILD)ZeroHeuristic.o

$(BUILD)FileToGraph.o: $(BUILD)Graph.o  $(BUILD)GraphNode.o $(SRC)FileToGraph.cpp 
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)FileToGraph.cpp -o $(BUILD)FileToGraph.o

$(BUILD)BST.o: $(BUILD)BSTNode.o $(BUILD)SearchGraphNode.o $(SRC)BST.cpp 
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)BST.cpp -o $(BUILD)BST.o

$(BUILD)BSTNode.o: $(SRC)BSTNode.cpp $(BUILD)SearchGraphNode.o
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)BSTNode.cpp -o $(BUILD)BSTNode.o


test: ${EXEC}
	./${EXEC} ${GRAPHS}teste${ARG}.txt ${GRAPHS}nodePosGraph${ARG}.txt ${GRAPHS}nodesToGetPathGraph${ARG}.txt 

memCheck: ${EXEC}
	valgrind --leak-check=full --show-leak-kinds=all ./${EXEC} ${GRAPHS}teste${ARG}.txt ${GRAPHS}nodePosGraph${ARG}.txt ${GRAPHS}nodesToGetPathGraph${ARG}.txt

clean:
	rm ${EXEC} -f $(BUILD)*/*.o $(BUILD)*.o