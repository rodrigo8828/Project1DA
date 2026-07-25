#include "vertex.h"

Vertex::Vertex(std::string location, int id, std::string code, bool parking)
    : location(location),
      id(id),
      code(code),
      parking(parking)

{
}

int Vertex::getId() {
    return id;
}

std::string Vertex::getLocation() {
    return location;
}

std::string Vertex::getCode() {
    return code;
}

bool Vertex::Parking() {
    return parking;
}  

void Vertex::addEdge(Edge* edge) {
    con.push_back(edge);
}



