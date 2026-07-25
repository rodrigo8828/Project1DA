#include <iostream>
using namespace std;

#include "graph.h"
#include "vertex.h"

int main() {
    Graph graph;


Vertex* v1 = new Vertex("Porto", 1, "POR", true);
Vertex* v2 = new Vertex("Gaia", 2, "GAI", false);

graph.addVertex(v1);
graph.addVertex(v2);

Vertex* result = graph.findVertexByID(100);

if (result != nullptr) {
    std::cout << result->getLocation() << std::endl;
}

    return 0;
}