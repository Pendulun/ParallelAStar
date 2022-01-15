EXEC=pastar
CXX = g++ 
CXXFLAGS = -Wall -g
BUILD=./build/
SRC=./src/
INCLUDE=./include/

all: ${EXEC}

${EXEC}: $(BUILD)main.o
	${CXX} ${CXXFLAGS} -o ${EXEC} $(BUILD)main.o

$(BUILD)main.o: $(SRC)main.cpp $(BUILD)GraphNode.o $(BUILD)SearchGraphNode.o $(BUILD)GraphSearcher.o
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)main.cpp -o $(BUILD)main.o

$(BUILD)GraphNode.o: $(SRC)GraphNode.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)GraphNode.cpp -o $(BUILD)GraphNode.o

$(BUILD)SearchGraphNode.o: $(SRC)SearchGraphNode.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)SearchGraphNode.cpp -o $(BUILD)SearchGraphNode.o

$(BUILD)GraphSearcher.o: $(SRC)GraphSearcher.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)GraphSearcher.cpp -o $(BUILD)GraphSearcher.o

$(BUILD)Graph.o: $(SRC)Graph.cpp $(BUILD)GraphNode.o
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)Graph.cpp -o $(BUILD)Graph.o

run: ${EXEC}
	./${EXEC}

clean:
	rm ${EXEC} -f $(BUILD)*/*.o $(BUILD)*.o