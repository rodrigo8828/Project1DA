#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

class Vertex;

class Graph {

private:
    std::vector<Vertex*> vertexSet;
    void resetAlgorithm();

public:
    void addVertex(Vertex* v);
    void addEdge(const std::string& location1,const std::string& location2,int driving,int walking);
    Vertex* findVertexByLocation(const std::string& location);
    Vertex* findVertexByID(int id);
    Vertex* findVertexByCode(const std::string& code);
    const std::vector<Vertex*>& getVertexSet() const;

};

#endif