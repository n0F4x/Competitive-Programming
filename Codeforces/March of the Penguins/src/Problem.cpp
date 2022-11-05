#include "Problem.hpp"

#include "Graph.hpp"


void Problem::solve() {
    Graph graph;

    float jd_squared = _jumping_distance * _jumping_distance;
    for (const auto& ice_cube : _ice_cubes) {
        auto from = graph.getNode(graph.addNode());
        auto to = graph.getNode(graph.addNode());
        from->addEdge({ from.get(), to, ice_cube.capacity });
    }
    auto source = graph.getNode(graph.addNode());
    for (size_t i = 0; i < _ice_cubes.size(); i++) {
        auto node = graph.getNode(2 * i + 1);
        source->addEdge({ source.get(), graph.getNode(2 * i), _ice_cubes[i].penguins });
        for (size_t j = 0; j < _ice_cubes.size(); j++) {
            if (i == j) continue;

            auto d_x = static_cast<float>(_ice_cubes[i].position.x - _ice_cubes[j].position.x);
            auto d_y = static_cast<float>(_ice_cubes[i].position.y - _ice_cubes[j].position.y);
            if (d_x * d_x + d_y * d_y <= jd_squared) {
                node->addEdge({ node.get(), graph.getNode(2 * j), INT_MAX });
            }
        }
    }

    for (size_t i = 0; i < _ice_cubes.size(); i++) {
        if (graph.dinic(source, graph.getNode(2 * i)) == source->sum_capacity()) {
            _results.push_back(i);
        }
    }
}


std::istream& operator>>(std::istream& is, Problem& problem) {
    int n;
    is >> n >> problem._jumping_distance;
    problem._ice_cubes.clear();
    problem._results.clear();
    problem._ice_cubes.resize(n);
    for (auto& ice_cube : problem._ice_cubes) {
        is >> ice_cube.position.x >> ice_cube.position.y >> ice_cube.penguins >> ice_cube.capacity;
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Problem& problem) {
    if (!problem._results.empty()) {
        for (auto result : problem._results) {
            os << result << ' ';
        }
    } else {
        os << -1 << ' ';
    }
    os << '\n';
    return os;
}
