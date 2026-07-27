#include <iostream>
using namespace std;

#include "graph.h"
#include "edge.h"
#include "vertex.h"

int main() {
Graph graph;

Vertex* porto = new Vertex("Porto", 1, "POR", true);
Vertex* gaia = new Vertex("Gaia", 2, "GAI", false);

graph.addVertex(porto);
graph.addVertex(gaia);

graph.addEdge("Porto", "Gaia", 20, 60);

for (Edge* e : porto->getCon()) {
    std::cout << e->getDestination()->getLocation() << std::endl;
    std::cout << e->getDriving() << std::endl;
    std::cout << e->getWalking() << std::endl;
}
}