#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

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

    if (
        data.source == -1 ||
        data.destination == -1
    ) {
        output.close();
        return 0;
    }

    Vertex* source =
        graph.findVertexByID(data.source);

    Vertex* destination =
        graph.findVertexByID(data.destination);

    if (
        source == nullptr ||
        destination == nullptr
    ) {
        output.close();
        return 0;
    }

    if (!data.restricted) {

        graph.algorithm(data.source);

        std::vector<int> bestRoute =
            graph.getPath(data.destination);

        output << "Source:"
               << data.source
               << "\n";

        output << "Destination:"
               << data.destination
               << "\n";

        if (bestRoute.empty()) {

            output << "BestDrivingRoute:none\n";
            output << "AlternativeDrivingRoute:none\n";
        }

        else {

            int bestTime =
                graph.findVertexByID(
                    data.destination
                )->getBestDistance();

            std::vector<int> forbiddenNodes;

            for (
                std::size_t i = 1;
                i + 1 < bestRoute.size();
                i++
            ) {
                forbiddenNodes.push_back(
                    bestRoute[i]
                );
            }

            std::vector<std::pair<int, int>>
                forbiddenSegments;

            for (
                std::size_t i = 0;
                i + 1 < bestRoute.size();
                i++
            ) {
                forbiddenSegments.push_back({
                    bestRoute[i],
                    bestRoute[i + 1]
                });
            }

            graph.algorithm(
                data.source,
                forbiddenNodes,
                forbiddenSegments
            );

            std::vector<int> alternativeRoute =
                graph.getPath(data.destination);

            output << "BestDrivingRoute:";

            for (
                std::size_t i = 0;
                i < bestRoute.size();
                i++
            ) {
                output << bestRoute[i];

                if (i < bestRoute.size() - 1) {
                    output << ",";
                }
            }

            output << "("
                   << bestTime
                   << ")\n";

            if (alternativeRoute.empty()) {

                output
                    << "AlternativeDrivingRoute:none\n";
            }

            else {

                int alternativeTime =
                    graph.findVertexByID(
                        data.destination
                    )->getBestDistance();

                output
                    << "AlternativeDrivingRoute:";

                for (
                    std::size_t i = 0;
                    i < alternativeRoute.size();
                    i++
                ) {
                    output << alternativeRoute[i];

                    if (
                        i <
                        alternativeRoute.size() - 1
                    ) {
                        output << ",";
                    }
                }

                output << "("
                       << alternativeTime
                       << ")\n";
            }
        }
    }

    else {

        std::vector<int> route;
        int totalTime = 0;

        if (data.includeNode != -1) {

            route = graph.IncludeNode(
                data.source,
                data.destination,
                data.includeNode,
                totalTime,
                data.avoidNodes,
                data.avoidSegments
            );
        }

        else {

            graph.algorithm(
                data.source,
                data.avoidNodes,
                data.avoidSegments
            );

            route =
                graph.getPath(data.destination);

            if (!route.empty()) {

                totalTime =
                    graph.findVertexByID(
                        data.destination
                    )->getBestDistance();
            }
        }

        output << "Source:"
               << data.source
               << "\n";

        output << "Destination:"
               << data.destination
               << "\n";

        if (route.empty()) {

            output
                << "RestrictedDrivingRoute:none\n";
        }

        else {

            output
                << "RestrictedDrivingRoute:";

            for (
                std::size_t i = 0;
                i < route.size();
                i++
            ) {
                output << route[i];

                if (i < route.size() - 1) {
                    output << ",";
                }
            }

            output << "("
                   << totalTime
                   << ")\n";
        }
    }

    output.close();

    std::cout
        << "output.txt criado com sucesso.\n";

    return 0;
}