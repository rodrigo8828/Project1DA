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
        if (line.empty()) {
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
    void Parser::readDistances(const std::string& filename, Graph& graph){
        std::ifstream file(filename);
        std::string line;
        int lineNumber = 0;
        while (std::getline(file, line)) {
            lineNumber++;
            if (lineNumber == 1) {
                continue;
            }
            if (line.empty()) {
                continue;
            }
        
        std::stringstream ss(line);
        std::string location1;
        std::string location2;
        std::string driving;
        std::string walking;
        getline(ss, location1, ',');
        getline(ss, location2, ',');
        getline(ss, driving, ',');
        getline(ss, walking, ',');

        int driving_;

        if (driving == "X") {
            driving_ = -1;
        }
        else {
            driving_ = std::stoi(driving);
        }

        int walking_ = std::stoi(walking);

        graph.addEdge(location1, location2, driving_, walking_);
        }
    }


