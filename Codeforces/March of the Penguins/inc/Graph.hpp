#pragma once

#include "Edge.hpp"
#include <memory>
#include <vector>


class Graph {
private:
    std::vector<std::shared_ptr<Node>> _nodes;

public:
    Graph() = default;
    explicit Graph(const std::vector<std::shared_ptr<Node>>& nodes);

    size_t addNode();
    std::shared_ptr<Node> getNode(size_t id);

    int dinic(std::shared_ptr<Node> source, std::shared_ptr<Node> target);

private:
    std::unique_ptr<std::vector<std::vector<Edge*>>> make_level_graph(
        std::shared_ptr<Node> source, std::shared_ptr<Node> target);
};
