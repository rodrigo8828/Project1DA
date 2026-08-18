#include <iostream>

#include "graph.h"
#include "parser.h"

int main() {

    InputData data = Parser::readInput(
        "/home/roger/universidade/Project1DA/input.txt"
    );

std::cout << "Mode: " << data.mode << "\n";
std::cout << "Source: " << data.source << "\n";
std::cout << "Destination: " << data.destination << "\n";
std::cout << "IncludeNode: " << data.includeNode << "\n";
std::cout << "AvoidNodes: ";

for (int node : data.avoidNodes) {
    std::cout << node << " ";
}

std::cout << "\n";

std::cout << "AvoidSegments: ";

for (auto segment : data.avoidSegments) {
    std::cout << "("
              << segment.first
              << ","
              << segment.second
              << ") ";
}

std::cout << "\n";
    return 0;
}