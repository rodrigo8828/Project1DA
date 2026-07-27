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
        const std::vector<Edge*>& getCon() const; //devolve uma referência, mas quem a recebe não pode alterar o vetor.
    
    private:
        std::string location;
        int id;
        std::string code;
        bool parking;
        std::vector<Edge*> con;

};

#endif