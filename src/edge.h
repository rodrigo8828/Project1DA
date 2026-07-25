#ifndef EDGE_H
#define EDGE_H

class Vertex;

class Edge{

    public:
        Edge(Vertex* destination, int driving, int walking);

    private: 
        Vertex* destination;
        int driving;
        int walking;

};



#endif