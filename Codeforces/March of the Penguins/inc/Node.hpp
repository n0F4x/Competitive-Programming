#pragma once

#include <vector>

class Edge;
class Graph;


class Node {
    friend Graph;

private:
    size_t _id;
    std::vector<Edge> _edges;

public:
    Node(size_t id);

    void addEdge(Edge& edge);
    void addEdge(Edge&& edge);

    int sum_capacity();
};
