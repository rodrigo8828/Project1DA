#include "edge.h"

Edge::Edge(Vertex* destination, int driving, int walking)
    : destination(destination),
      driving(driving),
      walking(walking)

{
}

Vertex* Edge::getDestination() const {
    return destination;
}

int Edge::getDriving() const {
    return driving;
}

int Edge::getWalking() const {
    return walking;
}