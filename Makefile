EXEC=pastar
CXX = g++ 
CXXFLAGS = -Wall -g
BUILD=./build/
SRC=./src/
INCLUDE=./include/

GRAPHSEARCHERDEPENDENCIES= $(BUILD)Graph.o $(BUILD)SearchGraphNode.o $(BUILD)SearchGraphNodeComparator.o $(BUILD)Heuristic.o $(BUILD)ManhattanHeuristic.o $(BUILD)EuclidianHeuristic.o

all: ${EXEC}

${EXEC}: $(BUILD)main.o $(BUILD)FileToGraph.o $(BUILD)GraphNode.o $(BUILD)GraphSearcher.o $(GRAPHSEARCHERDEPENDENCIES)
	${CXX} ${CXXFLAGS} -o ${EXEC} $(BUILD)main.o $(BUILD)GraphNode.o $(BUILD)GraphSearcher.o $(BUILD)FileToGraph.o $(GRAPHSEARCHERDEPENDENCIES)

$(BUILD)main.o: $(SRC)main.cpp $(BUILD)FileToGraph.o $(BUILD)GraphNode.o $(BUILD)SearchGraphNode.o $(BUILD)GraphSearcher.o
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)main.cpp -o $(BUILD)main.o

$(BUILD)GraphNode.o: $(SRC)GraphNode.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)GraphNode.cpp -o $(BUILD)GraphNode.o

$(BUILD)SearchGraphNode.o: $(SRC)SearchGraphNode.cpp
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

$(BUILD)SearchGraphNodeComparator.o: $(BUILD)SearchGraphNode.o $(SRC)SearchGraphNodeComparator.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)SearchGraphNodeComparator.cpp -o $(BUILD)SearchGraphNodeComparator.o

$(BUILD)FileToGraph.o: $(BUILD)Graph.o  $(BUILD)GraphNode.o $(SRC)FileToGraph.cpp 
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)FileToGraph.cpp -o $(BUILD)FileToGraph.o


run: ${EXEC}
	./${EXEC}

clean:
	rm ${EXEC} -f $(BUILD)*/*.o $(BUILD)*.o