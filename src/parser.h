#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <utility>

class Graph;

struct InputData {
    std::string mode;

    int source = -1;
    int destination = -1;
    int includeNode = -1;

    std::vector<int> avoidNodes;

    std::vector<std::pair<int, int>> avoidSegments;

    bool restricted = false;
};

class Parser {

public:
    static void readLocations(const std::string& filename, Graph& graph);
    static void readDistances(const std::string& filename, Graph& graph);
    static InputData readInput(const std::string& filename);
};

#endif