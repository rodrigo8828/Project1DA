#include <iostream>
#include <vector>
#include <climits>
#include <utility>

#include "graph.h"
#include "parser.h"
#include "vertex.h"

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

    int sourceId = 8;
    int destinationId = 1;

    Vertex* source = graph.findVertexByID(sourceId);
    Vertex* destination = graph.findVertexByID(destinationId);

    if (source == nullptr) {
        std::cout << "Vertice de origem inexistente.\n";
        return 0;
    }

    if (destination == nullptr) {
        std::cout << "Vertice de destino inexistente.\n";
        return 0;
    }

    // Melhor rota
    graph.algorithm(sourceId);

    std::vector<int> bestRoute = graph.getPath(destinationId);

    if (bestRoute.empty()) {
        std::cout << "Output:\n";
        std::cout << "Fastest Driving Route: none\n";
        std::cout << "Best alternative independent route: none\n";
        return 0;
    }

    int bestTime = destination->getBestDistance();

    // Criar restricoes automaticamente a partir da melhor rota
    std::vector<int> forbiddenNodes;
    std::vector<std::pair<int, int>> forbiddenSegments;

    // Proibir apenas os nos intermedios
    for (int i = 1; i < static_cast<int>(bestRoute.size()) - 1; i++) {
        forbiddenNodes.push_back(bestRoute[i]);
    }

    // Proibir todos os segmentos da melhor rota
    for (int i = 0; i < static_cast<int>(bestRoute.size()) - 1; i++) {
        forbiddenSegments.push_back({
            bestRoute[i],
            bestRoute[i + 1]
        });
    }

    // Melhor rota alternativa independente
    graph.algorithm(
        sourceId,
        forbiddenNodes,
        forbiddenSegments
    );

    std::vector<int> alternativeRoute =
        graph.getPath(destinationId);

    int alternativeTime = INT_MAX;

    if (!alternativeRoute.empty()) {
        alternativeTime = destination->getBestDistance();
    }

    std::cout << "Input:\n";
    std::cout << "Source: " << sourceId << "\n";
    std::cout << "Destination: " << destinationId << "\n";

    std::cout << "Output:\n";

    std::cout << "Fastest Driving Route: [";

    for (int i = 0; i < static_cast<int>(bestRoute.size()); i++) {
        std::cout << bestRoute[i];

        if (i < static_cast<int>(bestRoute.size()) - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "] Time: "
              << bestTime
              << "\n";

    if (alternativeRoute.empty()) {
        std::cout
            << "Best alternative independent route: none\n";
    }
    else {
        std::cout
            << "Best alternative independent route: [";

        for (
            int i = 0;
            i < static_cast<int>(alternativeRoute.size());
            i++
        ) {
            std::cout << alternativeRoute[i];

            if (
                i <
                static_cast<int>(alternativeRoute.size()) - 1
            ) {
                std::cout << ", ";
            }
        }

        std::cout << "], Time: "
                  << alternativeTime
                  << "\n";
    }

    return 0;
}