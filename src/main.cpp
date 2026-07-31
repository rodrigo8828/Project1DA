#include <iostream>
#include <vector>
#include <utility>

#include "graph.h"
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

    int sourceId = 5;
    int destinationId = 4;
    int includeNodeId = 7;

    // Nó 2 é proibido
    std::vector<int> avoidNodes ;

    // Para este teste não vamos proibir segmentos,
    // porque queremos permitir a passagem por 3 -> 7
    std::vector<std::pair<int, int>> avoidSegments;

    int totalTime = 0;

    std::vector<int> route =
        graph.IncludeNode(
            sourceId,
            destinationId,
            includeNodeId,
            totalTime,
            avoidNodes,
            avoidSegments
        );

    std::cout << "Source: "
              << sourceId
              << "\n";

    std::cout << "Destination: "
              << destinationId
              << "\n";

    std::cout << "IncludeNode: "
              << includeNodeId
              << "\n";

    std::cout << "Nodes to exclude: ";

    for (std::size_t i = 0; i < avoidNodes.size(); i++) {
        std::cout << avoidNodes[i];

        if (i < avoidNodes.size() - 1) {
            std::cout << ",";
        }
    }

    std::cout << "\n";

    std::cout << "Edges to exclude: ";

    for (
        std::size_t i = 0;
        i < avoidSegments.size();
        i++
    ) {
        std::cout << "("
                  << avoidSegments[i].first
                  << ","
                  << avoidSegments[i].second
                  << ")";

        if (i < avoidSegments.size() - 1) {
            std::cout << ",";
        }
    }

    std::cout << "\n";

    if (route.empty()) {
        std::cout << "Restricted Route: none\n";
        return 0;
    }

    std::cout << "Restricted Route: [";

    for (std::size_t i = 0; i < route.size(); i++) {
        std::cout << route[i];

        if (i < route.size() - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "] Time: "
              << totalTime
              << "\n";

    return 0;
}