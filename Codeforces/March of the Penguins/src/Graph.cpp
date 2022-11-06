#include "Graph.hpp"

#include <queue>
#include <algorithm>
#include <set>


Graph::Graph(const std::vector<std::shared_ptr<Node>>& nodes) : _nodes{ nodes } {}


size_t Graph::addNode() {
	_nodes.emplace_back(std::make_shared<Node>(_nodes.size()));
	return _nodes.size() - 1;
}

std::shared_ptr<Node> Graph::getNode(size_t id) {
	return _nodes.at(id);
}


std::unique_ptr<std::vector<std::vector<Edge*>>> Graph::make_level_graph(
	std::shared_ptr<Node> source, std::shared_ptr<Node> target
) {
	std::vector<bool> visited;
	visited.resize(_nodes.size(), false);
	visited[source->_id] = true;
	auto level_graph{ std::make_unique<std::vector<std::vector<Edge*>>>() };
	bool reached_target = false;
	std::vector<bool> visited_frontier{ visited };
	std::queue<std::vector<Edge*>> paths;
	for (auto& edge : source->_edges) {
		if (edge._capacity - edge._flow > 0) {
			paths.push({ &edge });
			visited.at(edge._to->_id) = true;
			if (edge._to->_id == target->_id) {
				reached_target = true;
				level_graph->push_back(paths.back());
			}
		}
	}
	while (!(reached_target || paths.empty())) {
		size_t original_size = paths.size();
		for (size_t i = 0; i < original_size; i++) {
			auto path = paths.front();
			paths.pop();
			for (auto& edge : path.back()->_to->_edges) {
				if ((edge._capacity - edge._flow) > 0 && !visited.at(edge._to->_id)) {
					auto new_path{ path };
					new_path.push_back(&edge);
					paths.push(new_path);
					visited_frontier.at(edge._to->_id) = true;
					if (edge._to->_id == target->_id) {
						reached_target = true;
						level_graph->push_back(new_path);
					}
				}
			}
		}
		visited = visited_frontier;
	}
	return level_graph;
}


int Graph::dinic(std::shared_ptr<Node> source, std::shared_ptr<Node> target) {
	int max_flow = 0;

	// Reset graph
	for (const auto& node : _nodes) {
		for (auto& edge : node->_edges) {
			edge._flow = 0;
		}
	}

	for (
		auto level_graph{ *make_level_graph(source, target) };
		!level_graph.empty();
		level_graph = *make_level_graph(source, target)
	) {
		for (const auto& path : level_graph) {
			int bottleneck = INT_MAX;
			for (auto& edge : path) {
				bottleneck = std::min(bottleneck, edge->_capacity - edge->_flow);
			}
			for (auto edge : path) {
				edge->_flow += bottleneck;
			}
			max_flow += bottleneck;
		}
	}

	return max_flow;
}
