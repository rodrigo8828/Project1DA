#ifndef EDGE_H
#define EDGE_H

class Vertex;

class Edge{

    public:
        Edge(Vertex* destination, int driving, int walking);

        Vertex* getDestination() const;
        int getDriving() const;
        int getWalking() const;

    private: 
        Vertex* destination;
        int driving;
        int walking;

};



#endif