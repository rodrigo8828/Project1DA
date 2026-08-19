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

        std::getline(ss, location, ',');
        std::getline(ss, id, ',');
        std::getline(ss, code, ',');
        std::getline(ss, parking, ',');

        int id_ = std::stoi(id);
        bool parking_ = std::stoi(parking);

        Vertex* v = new Vertex(location, id_, code, parking_);

        graph.addVertex(v);
    }

    file.close();
}

void Parser::readDistances(const std::string& filename, Graph& graph) {

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

        std::getline(ss, location1, ',');
        std::getline(ss, location2, ',');
        std::getline(ss, driving, ',');
        std::getline(ss, walking, ',');

        int driving_;

        if (driving == "X") {
            driving_ = -1;
        }
        else {
            driving_ = std::stoi(driving);
        }

        int walking_ = std::stoi(walking);

        graph.addEdge(
            location1,
            location2,
            driving_,
            walking_
        );
    }

    file.close();
}

InputData Parser::readInput(const std::string& filename) {

    InputData data;

    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Erro ao abrir o ficheiro de input.\n";
        return data;
    }

    std::string line;

    while (std::getline(file, line)) {

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            continue;
        }

        std::size_t separator = line.find(':');

        if (separator == std::string::npos) {
            continue;
        }

        std::string key = line.substr(0, separator);
        std::string value = line.substr(separator + 1);

        if (key == "Mode") {
            data.mode = value;
        }

        else if (key == "Source") {
            if (!value.empty()) {
                data.source = std::stoi(value);
            }
        }

        else if (key == "Destination") {
            if (!value.empty()) {
                data.destination = std::stoi(value);
            }
        }

        else if (key == "IncludeNode") {

            data.restricted = true;
            
            if (!value.empty()) {
                data.includeNode = std::stoi(value);
            }
        }

        else if (key == "AvoidNodes") {

            data.restricted = true;

            if (!value.empty()) {

                std::stringstream ss(value);
                std::string node;

                while (std::getline(ss, node, ',')) {

                    if (!node.empty()) {
                        data.avoidNodes.push_back(
                            std::stoi(node)
                        );
                    }
                }
            }
        }

        else if (key == "AvoidSegments") {

            data.restricted = true;

            if (!value.empty()) {

                std::stringstream ss(value);

                char ch;
                int a;
                int b;

                while (
                    ss >> ch
                       >> a
                       >> ch
                       >> b
                       >> ch
                ) {

                    data.avoidSegments.push_back({a, b});

                    if (ss.peek() == ',') {
                        ss.ignore();
                    }
                }
            }
        }
    }

    file.close();

    return data;
}