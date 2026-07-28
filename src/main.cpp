#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#include "graph.h"
#include "parser.h"
#include "vertex.h"
int main() {

    // 1. Criar o grafo
    Graph graph;

    // 2. Ler os vértices
    Parser::readLocations(
        "../For Students-20250213T135713Z-001/For Students/Locations_small.csv",
        graph
    );

    // 3. Ler as arestas
    Parser::readDistances(
        "../For Students-20250213T135713Z-001/For Students/Distances_small.csv",
        graph
    );

     int sourceId = 3;
    int destinationId = 8;

    Vertex* source = graph.findVertexByID(sourceId);
    Vertex* destination = graph.findVertexByID(destinationId);

    if (source == nullptr) {
        std::cout << "Vertice de origem inexistente." << std::endl;
        return 0;
    }

    if (destination == nullptr) {
        std::cout << "Vertice de destino inexistente." << std::endl;
        return 0;
    }

    // Executar o algoritmo a partir da origem
    graph.algorithm(sourceId);

    // Verificar se existe percurso
    if (destination->getBestDistance() == INT_MAX) {
        std::cout << "Nao existe percurso de conducao entre "
                  << sourceId
                  << " e "
                  << destinationId
                  << "."
                  << std::endl;

        return 0;
    }

    // Reconstruir o percurso através do prev
    std::vector<int> path;

    Vertex* current = destination;

    while (current != nullptr) {
        path.push_back(current->getId());
        current = current->getPrev();
    }

    // O percurso foi construído do destino para a origem
    std::reverse(path.begin(), path.end());

    std::cout << "Origem: "
              << source->getLocation()
              << " (ID "
              << sourceId
              << ")"
              << std::endl;

    std::cout << "Destino: "
              << destination->getLocation()
              << " (ID "
              << destinationId
              << ")"
              << std::endl;

    std::cout << "Fastest Driving Route: [";

    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];

        if (i < path.size() - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "] Time: "
              << destination->getBestDistance()
              << " minutos"
              << std::endl;

    return 0;
}