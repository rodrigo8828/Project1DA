#ifndef PARSER_H
#define PARSER_H

#include <string>

class Graph;

class Parser {

public:
    static void readLocations(const std::string& filename, Graph& graph);
    static void readDistances(const std::string& filename, Graph& graph);
};

#endif