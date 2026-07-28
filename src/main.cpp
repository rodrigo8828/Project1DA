#include <iostream>
#include <vector>
#include <utility>
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

    // 4. Dados do teste
    int sourceId = 5;
    int destinationId = 4;

    // Nó que queremos evitar
    std::vector<int> avoidNodes = {2};

    // Neste teste não evitamos segmentos
    std::vector<std::pair<int, int>> avoidSegments = {{4,7}};

    // 5. Verificar origem e destino
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

    // Não faz sentido evitar a origem ou o destino
    for (int nodeId : avoidNodes) {
        if (nodeId == sourceId || nodeId == destinationId) {
            std::cout << "RestrictedDrivingRoute:none\n";
            return 0;
        }
    }

    // 6. Calcular a rota respeitando as restrições
    graph.algorithm(
        sourceId,
        avoidNodes,
        avoidSegments
    );

    // 7. Reconstruir a rota
    std::vector<int> restrictedRoute =
        graph.getPath(destinationId);

    // 8. Mostrar os dados utilizados
    std::cout << "Input:\n";
    std::cout << "Source: " << sourceId << "\n";
    std::cout << "Destination: " << destinationId << "\n";

    std::cout << "AvoidNodes:";

    for (std::size_t i = 0; i < avoidNodes.size(); i++) {
        std::cout << avoidNodes[i];

        if (i < avoidNodes.size() - 1) {
            std::cout << ",";
        }
    }

    std::cout << "\n";

    std::cout << "AvoidSegments:";

    for (std::size_t i = 0; i < avoidSegments.size(); i++) {
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

    // 9. Mostrar o resultado
    std::cout << "Output:\n";
    std::cout << "Source:" << sourceId << "\n";
    std::cout << "Destination:" << destinationId << "\n";

    if (restrictedRoute.empty()) {
        std::cout << "RestrictedDrivingRoute:none\n";
        return 0;
    }

    // O algoritmo já terminou, por isso o destino contém
    // a distância da rota restrita
    int restrictedTime =
        destination->getBestDistance();

    std::cout << "RestrictedDrivingRoute:";

    for (
        std::size_t i = 0;
        i < restrictedRoute.size();
        i++
    ) {
        std::cout << restrictedRoute[i];

        if (i < restrictedRoute.size() - 1) {
            std::cout << ",";
        }
    }

    std::cout << "("
              << restrictedTime
              << ")\n";

    return 0;
}