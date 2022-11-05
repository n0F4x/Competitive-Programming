#include "Node.hpp"

#include "Edge.hpp"


Node::Node(size_t id) : _id{ id } {}

void Node::addEdge(Edge& edge) {
    _edges.emplace_back(edge);
}

void Node::addEdge(Edge&& edge) {
    _edges.emplace_back(std::move(edge));
}


int Node::sum_capacity() const {
    int res = 0;
    for (const auto& edge : _edges) {
        res += edge._capacity;
    }
    return res;
}
