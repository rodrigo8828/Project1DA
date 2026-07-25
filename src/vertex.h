#ifndef VERTEX_H
#define VERTEX_H

#include <string>

class Vertex {

    public:
        Vertex(std::string location, int id, std::string code, bool parking);
    
    private:
        std::string location;
        int id;
        std::string code;
        bool parking;

};

#endif