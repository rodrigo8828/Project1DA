#include <iostream>

#include "graph.h"
#include "parser.h"
#include "vertex.h"
#include "edge.h"

int main() {

    Graph graph;

    Parser::readLocations(
        "../For Students-20250213T135713Z-001/For Students/Locations.csv",
        graph
    );

    Parser::readDistances(
        "../For Students-20250213T135713Z-001/For Students/Distances.csv",
        graph
    );

    Vertex* v = graph.findVertexByCode("PA9908");

    if (v == nullptr) {
        std::cout << "Vertex nao encontrado!" << std::endl;
        return 0;
    }

    std::cout << "Local: " << v->getLocation() << std::endl;
    std::cout << "Code: " << v->getCode() << std::endl;
    std::cout << "Ligacoes:\n";

    for (Edge* e : v->getCon()) {

        std::cout << " -> "
                  << e->getDestination()->getCode()
                  << " | Driving: ";

        if (e->getDriving() == -1) {
            std::cout << "X";
        }
        else {
            std::cout << e->getDriving();
        }

        std::cout << " | Walking: "
                  << e->getWalking()
                  << std::endl;
    }

    return 0;
}