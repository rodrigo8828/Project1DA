#include "graph.h"
#include "vertex.h"
#include "edge.h"

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

void Graph::addEdge(const std::string& location1,const std::string& location2,int driving,int walking){

    Vertex* source = findVertexByLocation(location1);
    Vertex* destination = findVertexByLocation(location2);

    if (source == nullptr || destination == nullptr) return;

    Edge* edge = new Edge(destination,driving,walking);

    source->addEdge(edge);
}

