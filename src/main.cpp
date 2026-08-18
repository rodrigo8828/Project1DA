#include <iostream>
#include <fstream>
#include <vector>

#include "graph.h"
#include "vertex.h"
#include "parser.h"

int main() {

    Graph graph;

    Parser::readLocations(
        "../For Students-20250213T135713Z-001/For Students/Locations_small.csv",
        graph
    );

    Parser::readDistances(
        "../For Students-20250213T135713Z-001/For Students/Distances_small.csv",
        graph
    );

    InputData data = Parser::readInput("../input.txt");

    std::ofstream output("../output.txt");

    if (!output.is_open()) {
        std::cout << "Erro ao criar output.txt\n";
        return 0;
    }

    if (data.includeNode == -1) {

        graph.algorithm(
            data.source,
            data.avoidNodes,
            data.avoidSegments
        );

        std::vector<int> route =
            graph.getPath(data.destination);

        if (route.empty()) {
            output << "Restricted Route: none\n";
        }
        else {

            Vertex* destination =
                graph.findVertexByID(data.destination);

            int totalTime =
                destination->getBestDistance();

            output << "Restricted Route: [";

            for (std::size_t i = 0; i < route.size(); i++) {

                output << route[i];

                if (i < route.size() - 1) {
                    output << ", ";
                }
            }

            output << "] Time: "
                   << totalTime
                   << "\n";
        }
    }

    else {

        int totalTime = 0;

        std::vector<int> route =
            graph.IncludeNode(
                data.source,
                data.destination,
                data.includeNode,
                totalTime,
                data.avoidNodes,
                data.avoidSegments
            );

        if (route.empty()) {
            output << "Restricted Route: none\n";
        }
        else {

            output << "Restricted Route: [";

            for (std::size_t i = 0; i < route.size(); i++) {

                output << route[i];

                if (i < route.size() - 1) {
                    output << ", ";
                }
            }

            output << "] Time: "
                   << totalTime
                   << "\n";
        }
    }

    output.close();

    std::cout << "output.txt criado com sucesso.\n";

    return 0;
}