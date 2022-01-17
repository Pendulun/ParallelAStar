#include "GraphNode.hpp"
#include "SearchGraphNode.hpp"
#include "GraphSearcher.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    GraphSearcher graphSearcher;
    graphSearcher.getPathTo(2);
    return 0;
}
