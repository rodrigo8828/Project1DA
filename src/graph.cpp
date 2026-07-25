#include "graph.h"
#include "vertex.h"

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

