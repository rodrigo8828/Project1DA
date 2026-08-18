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

InputData Parser::readInput(const std::string& filename) {
    InputData data;

    std::ifstream file(filename);

    std::string line;

    while (std::getline(file, line)) {
        std::size_t separator = line.find(':');

        if (separator == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, separator);
        std::string value = line.substr(separator + 1);

        if (key == "Mode") {
            data.mode = value;
        }

        if (key == "Source") {
            data.source = std::stoi(value);
        }
        if (key == "Destination") {
            data.destination = std::stoi(value);
        }

        if (key == "IncludeNode") {
            if (!value.empty()) {
            data.includeNode = std::stoi(value);
        }
        }
        if (key == "AvoidNodes") {
            std::stringstream ss(value);
            std::string node;

        while (std::getline(ss, node, ',')) {
            if (!node.empty()) {
            data.avoidNodes.push_back(std::stoi(node));
            }
        }
        }
        if (key == "AvoidSegments") {
        std::stringstream ss(value);
        char ch;
        int a, b;

        while (ss >> ch >> a >> ch >> b >> ch) {
        data.avoidSegments.push_back({a, b});

        if (ss.peek() == ',') {
            ss.ignore();
        }
        }
        }
    }
    file.close();

    return data;
}


