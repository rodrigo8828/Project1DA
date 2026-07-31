#include "graph.h"
#include "vertex.h"
#include "edge.h"

#include <climits>
#include <queue>
#include <algorithm>

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

Vertex* Graph::findVertexByID(int id) const{
    for (Vertex* v : vertexSet){
        if (v->getId() == id){
            return v;
        }
    }
    return nullptr;
}

Vertex* Graph::findVertexByCode(const std::string& code) {
    for (Vertex* v : vertexSet) {
        if (v->getCode() == code) {
            return v;
        }
    }
    return nullptr;
}

void Graph::addEdge(const std::string& location1,const std::string& location2,int driving,int walking){

    Vertex* source = findVertexByCode(location1);
    Vertex* destination = findVertexByCode(location2);

    if (source == nullptr || destination == nullptr) return;

    Edge* edge1 = new Edge(destination,driving,walking);
    Edge* edge2 = new Edge(source,driving,walking);

    source->addEdge(edge1);
    destination->addEdge(edge2);
}

const std::vector<Vertex*>& Graph::getVertexSet() const {
    return vertexSet;
}

void Graph::resetAlgorithm() {
    for (Vertex* v : vertexSet) {
        v->setBestDistance(INT_MAX);
        v->setPrev(nullptr);
        v->setVisited(false);
    }
}

struct CompareDistance {
    bool operator()(const std::pair<int, Vertex*>& a,
                    const std::pair<int, Vertex*>& b) const {
        return a.first > b.first;
    }
};

void Graph::algorithm(
    int sourceId,
    const std::vector<int>& forbiddenNodes,
    const std::vector<std::pair<int, int>>& forbiddenSegments)  {

    resetAlgorithm();

    Vertex* source = findVertexByID(sourceId);
    if (source == nullptr) {
        return;
    }

    source->setBestDistance(0);

    std::priority_queue<
    std::pair<int, Vertex*>,
    std::vector<std::pair<int, Vertex*>>,
    CompareDistance
    > road;

    road.push({0, source});

    while (!road.empty()) {
        auto current = road.top();
        road.pop();
        int currentDistance = current.first;
        Vertex* currentVertex = current.second;
        if (currentVertex->isVisited()) {
        continue;
        }

        currentVertex->setVisited(true);

        for (Edge* edge : currentVertex->getCon()) {
        Vertex* nextVert = edge->getDestination();

        bool isForbiddenNode = false;

        for (int nodeId : forbiddenNodes) {
            if (nextVert->getId() == nodeId) {
                isForbiddenNode = true;
                break;
            }
        }
        if (isForbiddenNode) {
            continue;
        }
        bool isForbiddenSegment = false;

        for (const auto& edge : forbiddenSegments) {
            bool direction =
                edge.first == currentVertex->getId() &&
                edge.second == nextVert->getId();

            bool oppositeDirection =
                edge.first == nextVert->getId() &&
                edge.second == currentVertex->getId();

            if (direction || oppositeDirection) {
                isForbiddenSegment = true;
                break;
            }
        }

        if (isForbiddenSegment) {
            continue;
        }
        if (edge->getDriving() == -1) {
        continue;
        }
        if (nextVert->isVisited()) {
        continue;
        }
        int newDistance = currentDistance + edge->getDriving();

        if (newDistance < nextVert->getBestDistance()) {
        nextVert->setBestDistance(newDistance);
        nextVert->setPrev(currentVertex);
        road.push({newDistance,nextVert});
        }
        }
        
    }
}

    std::vector<int> Graph::getPath(int destinationID) const {
    std::vector<int> path;
    Vertex* current = findVertexByID(destinationID);
    if (current == nullptr || current->getBestDistance() == INT_MAX) return path;
    while (current != nullptr) {
    path.push_back(current->getId());
    current = current->getPrev();
    }
    std::reverse(path.begin(), path.end());
    return path;
    }

    std::vector<int> Graph::IncludeNode(
        int sourceID,
        int destinationID,
        int includeNodeID,
        int& totalTime,
        const std::vector<int>& forbiddenNodes,
        const std::vector<std::pair<int, int>>& forbiddenSegments
    ) {
        std::vector<int> final;

        Vertex* includeNode = findVertexByID(includeNodeID);

        if (includeNode == nullptr) {
            return final;
        }
        for (int nodeID : forbiddenNodes) {
        if (nodeID == includeNodeID) {
            return final;
        }
        }
    algorithm(sourceID,forbiddenNodes,forbiddenSegments);

    std::vector<int> firstRoute = getPath(includeNodeID);

        if (firstRoute.empty()) return final;

        int firstTime = includeNode->getBestDistance();

    algorithm(includeNodeID,forbiddenNodes,forbiddenSegments);

    std::vector<int> secondRoute = getPath(destinationID);

    if (secondRoute.empty()) return final;

    Vertex* destination = findVertexByID(destinationID);
    int secondTime = destination->getBestDistance();
    
    final = firstRoute;

    for (std::size_t i = 1; i < secondRoute.size(); i++) {
        final.push_back(secondRoute[i]);
    }

    totalTime = firstTime + secondTime;

    return final;
}
    