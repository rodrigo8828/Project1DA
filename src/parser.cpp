#include "parser.h"
#include "graph.h"
#include "vertex.h"

#include <fstream>
#include <sstream>
#include <iostream>

void Parser::readLocations(const std::string& filename, Graph& graph) {

    std::ifstream file(filename);
    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) {
        lineNumber++;
        if (lineNumber == 1) {
            continue;
        }
    
    std::stringstream ss(line);
    std::string location;
    std::string id;
    std::string code;
    std::string parking;
    getline(ss, location, ',');
    getline(ss, id, ',');
    getline(ss, code, ',');
    getline(ss, parking, ',');

    int id_ = std::stoi(id);
    bool parking_ = std::stoi(parking);

    Vertex* v = new Vertex(location, id_, code, parking_);
    graph.addVertex(v);
    
    }
}


