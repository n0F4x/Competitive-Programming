#pragma once

#include "Node.hpp"
#include <memory>

class Graph;

class Edge {
friend Node;
friend Graph;

private:
    Node* _from;
    std::shared_ptr<Node> _to;
    int _capacity;
    int _flow = 0;

public:
    Edge(Node* from, std::shared_ptr<Node> to, int capacity);
};
