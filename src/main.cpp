#include <iostream>
using namespace std;

#include "graph.h"
#include "edge.h"
#include "vertex.h"
#include "graph.h"
#include "parser.h"

int main() {

    Graph graph;

    Parser::readLocations("../For Students-20250213T135713Z-001/For Students/Locations.csv", graph);

    return 0;
}