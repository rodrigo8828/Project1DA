#include <iostream>
#include <fstream>

#include "graph.h"
#include "parser.h"

int main() {
    InputData data = Parser::readInput("../input.txt");

    std::ofstream output("../output.txt");

    if (!output.is_open()) {
        std::cout << "Erro ao criar output.txt\n";
        return 0;
    }

    output << "Source:" << data.source << "\n";
    output << "Destination:" << data.destination << "\n";

    output.close();

    return 0;
}