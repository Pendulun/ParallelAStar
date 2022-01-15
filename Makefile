EXEC=pastar
CXX = g++ 
CXXFLAGS = -Wall -g
BUILD=./build/
SRC=./src/
INCLUDE=./include/

all: ${EXEC}

${EXEC}: $(BUILD)main.o
	${CXX} ${CXXFLAGS} -o ${EXEC} $(BUILD)main.o

$(BUILD)main.o: $(SRC)main.cpp $(BUILD)GraphNode.o $(BUILD)SearchGraphNode.o 
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)main.cpp -o $(BUILD)main.o

$(BUILD)GraphNode.o: $(SRC)GraphNode.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)GraphNode.cpp -o $(BUILD)GraphNode.o

$(BUILD)SearchGraphNode.o: $(SRC)SearchGraphNode.cpp
	${CXX} ${CXXFLAGS} -I${INCLUDE} -c $(SRC)SearchGraphNode.cpp -o $(BUILD)SearchGraphNode.o

run: ${EXEC}
	./${EXEC}

clean:
	rm ${EXEC} -f $(BUILD)*/*.o $(BUILD)*.o