#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>

class Edge;

class Vertex {

    public:
        Vertex(std::string location, int id, std::string code, bool parking);
        int getId();
        std::string getLocation();
        std::string getCode();
        bool Parking();
        void addEdge(Edge* edge);
    
    private:
        std::string location;
        int id;
        std::string code;
        bool parking;
        std::vector<Edge*> con;

};

#endif