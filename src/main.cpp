#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <string>

#include "graph.h"
#include "vertex.h"
#include "parser.h"


void printRoute(const std::vector<int>& route) {

    std::cout << "[";

    for (std::size_t i = 0; i < route.size(); i++) {

        std::cout << route[i];

        if (i < route.size() - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "]";
}


void bestAlternativeRoute(Graph& graph) {

    int source;
    int destination;

    std::cout << "\nSource: ";
    std::cin >> source;

    std::cout << "Destination: ";
    std::cin >> destination;

    if (
        graph.findVertexByID(source) == nullptr ||
        graph.findVertexByID(destination) == nullptr
    ) {
        std::cout << "Invalid source or destination.\n";
        return;
    }

    graph.algorithm(source);

    std::vector<int> bestRoute =
        graph.getPath(destination);

    if (bestRoute.empty()) {

        std::cout << "Best Driving Route: none\n";
        std::cout << "Alternative Driving Route: none\n";

        return;
    }

    int bestTime =
        graph.findVertexByID(destination)
        ->getBestDistance();

    std::vector<int> forbiddenNodes;

    for (
        std::size_t i = 1;
        i + 1 < bestRoute.size();
        i++
    ) {
        forbiddenNodes.push_back(bestRoute[i]);
    }

    std::vector<std::pair<int, int>> forbiddenSegments;

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
        source,
        forbiddenNodes,
        forbiddenSegments
    );

    std::vector<int> alternativeRoute =
        graph.getPath(destination);

    std::cout << "\nBest Driving Route: ";
    printRoute(bestRoute);

    std::cout << " Time: "
              << bestTime
              << "\n";

    if (alternativeRoute.empty()) {

        std::cout
            << "Alternative Driving Route: none\n";
    }

    else {

        int alternativeTime =
            graph.findVertexByID(destination)
            ->getBestDistance();

        std::cout
            << "Alternative Driving Route: ";

        printRoute(alternativeRoute);

        std::cout << " Time: "
                  << alternativeTime
                  << "\n";
    }
}


void restrictedRoute(Graph& graph) {

    int source;
    int destination;

    std::cout << "\nSource: ";
    std::cin >> source;

    std::cout << "Destination: ";
    std::cin >> destination;

    if (
        graph.findVertexByID(source) == nullptr ||
        graph.findVertexByID(destination) == nullptr
    ) {
        std::cout << "Invalid source or destination.\n";
        return;
    }

    std::vector<int> avoidNodes;
    std::vector<std::pair<int, int>> avoidSegments;

    int numberNodes;

    std::cout << "Number of nodes to exclude: ";
    std::cin >> numberNodes;

    for (int i = 0; i < numberNodes; i++) {

        int node;

        std::cout << "Node "
                  << i + 1
                  << ": ";

        std::cin >> node;

        avoidNodes.push_back(node);
    }

    int numberSegments;

    std::cout << "Number of segments to exclude: ";
    std::cin >> numberSegments;

    for (int i = 0; i < numberSegments; i++) {

        int a;
        int b;

        std::cout << "Segment "
                  << i + 1
                  << " - first node: ";

        std::cin >> a;

        std::cout << "Segment "
                  << i + 1
                  << " - second node: ";

        std::cin >> b;

        avoidSegments.push_back({a, b});
    }

    int includeNode;

    std::cout << "Include node (-1 for none): ";
    std::cin >> includeNode;

    std::vector<int> route;
    int totalTime = 0;

    if (includeNode != -1) {

        route = graph.IncludeNode(
            source,
            destination,
            includeNode,
            totalTime,
            avoidNodes,
            avoidSegments
        );
    }

    else {

        graph.algorithm(
            source,
            avoidNodes,
            avoidSegments
        );

        route = graph.getPath(destination);

        if (!route.empty()) {

            totalTime =
                graph.findVertexByID(destination)
                ->getBestDistance();
        }
    }

    if (route.empty()) {

        std::cout << "\nRestricted Route: none\n";
        return;
    }

    std::cout << "\nRestricted Route: ";

    printRoute(route);

    std::cout << " Time: "
              << totalTime
              << "\n";
}


void batchMode(Graph& graph) {

    InputData data =
        Parser::readInput("../input.txt");

    std::ofstream output("../output.txt");

    if (!output.is_open()) {
        std::cout << "Erro ao criar output.txt\n";
        return;
    }

    if (
        data.source == -1 ||
        data.destination == -1
    ) {
        output.close();
        return;
    }

    if (
        graph.findVertexByID(data.source) == nullptr ||
        graph.findVertexByID(data.destination) == nullptr
    ) {
        output.close();
        return;
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
        << "Batch mode terminado. output.txt criado.\n";
}


int main(int argc, char* argv[]) {

    Graph graph;

    Parser::readLocations(
        "../For Students-20250213T135713Z-001/For Students/Locations_small.csv",
        graph
    );

    Parser::readDistances(
        "../For Students-20250213T135713Z-001/For Students/Distances_small.csv",
        graph
    );

    if (
        argc > 1 &&
        std::string(argv[1]) == "batch"
    ) {

        batchMode(graph);

        return 0;
    }

    int option;

    do {

        std::cout << "\n";
        std::cout
            << "====== ROUTE PLANNING TOOL ======\n";
        std::cout << "\n";

        std::cout
            << "1 - Best and Alternative Route\n";

        std::cout
            << "2 - Restricted Route\n";

        std::cout
            << "0 - Exit\n";

        std::cout << "\nOption: ";

        std::cin >> option;

        if (option == 1) {

            bestAlternativeRoute(graph);
        }

        else if (option == 2) {

            restrictedRoute(graph);
        }

        else if (option == 0) {

            std::cout << "Exiting...\n";
        }

        else {

            std::cout << "Invalid option.\n";
        }

    } while (option != 0);

    return 0;
}