#include "graph.h"
#include "vertex.h"
#include "edge.h"

#include <climits>

void Graph::addVertex(Vertex* v) {
    vertexSet.push_back(v);
}

Vertex* Graph::findVertexByLocation(const std::string& location){
    for (Vertex* v : vertexSet){
        if (v->getLocation() == location){
            return v;
        }
    }
    return nullptr;
}

Vertex* Graph::findVertexByID(int id){
    for (Vertex* v : vertexSet){
        if (v->getId() == id){
            return v;
        }
    }
    return nullptr;
}

Vertex* Graph::findVertexByCode(const std::string& code) {
    for (Vertex* v : vertexSet) {
        if (v->getCode() == code) {
            return v;
        }
    }
    return nullptr;
}

void Graph::addEdge(const std::string& location1,const std::string& location2,int driving,int walking){

    Vertex* source = findVertexByCode(location1);
    Vertex* destination = findVertexByCode(location2);

    if (source == nullptr || destination == nullptr) return;

    Edge* edge1 = new Edge(destination,driving,walking);
    Edge* edge2 = new Edge(source,driving,walking);

    source->addEdge(edge1);
    destination->addEdge(edge2);
}

const std::vector<Vertex*>& Graph::getVertexSet() const {
    return vertexSet;
}

void Graph::resetAlgorithm() {
    for (Vertex* v : vertexSet) {
        v->setBestDistance(INT_MAX);
        v->setPrev(nullptr);
        v->setVisited(false);
    }
}

void Graph::algorithm(int sourceId) {
    resetAlgorithm();

    Vertex* source = findVertexByID(sourceId);
    if (source == nullptr) {
        return;
    }

    source->setBestDistance(0);
}

