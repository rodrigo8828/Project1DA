#include "vertex.h"

#include <climits>

Vertex::Vertex(std::string location, int id, std::string code, bool parking)
    : location(location),
      id(id),
      code(code),
      parking(parking),
      bestDistance(INT_MAX),
      prev(nullptr),
      visited(false)

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

const std::vector<Edge*>& Vertex::getCon() const {
    return con;
}

int Vertex::getBestDistance() const {
    return bestDistance;
}

void Vertex::setBestDistance(int distance){
    bestDistance = distance;
}

Vertex* Vertex::getPrev() const {
    return prev;
}

void Vertex::setPrev(Vertex* newPrev){
    prev = newPrev;
}

bool Vertex::isVisited() const{
    return visited;
}

void Vertex::setVisited(bool visited_){
    visited = visited_;
}


