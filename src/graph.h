#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <utility>

class Vertex;

class Graph {

private:
    std::vector<Vertex*> vertexSet;
    void resetAlgorithm();

public:
    void addVertex(Vertex* v);
    void addEdge(const std::string& location1,const std::string& location2,int driving,int walking);
    Vertex* findVertexByLocation(const std::string& location);
    Vertex* findVertexByID(int id) const;
    Vertex* findVertexByCode(const std::string& code);
    const std::vector<Vertex*>& getVertexSet() const;
    void algorithm (int sourceId, 
    const std::vector<int>& forbiddenNodes = {},
    const std::vector<std::pair<int, int>>& forbiddenSegments = {});
    std::vector<int> getPath(int destinationID) const;

};

#endif