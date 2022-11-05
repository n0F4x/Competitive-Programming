#include "Graph.hpp"

#include <queue>
#include <algorithm>


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
	auto level_graph{ std::make_unique<std::vector<std::vector<Edge*>>>() };
	bool reached_target = false;
	std::vector<size_t> visited;
	std::vector<size_t> visited_frontier;
	std::queue<std::vector<Edge*>> paths;
	for (auto& edge : source->_edges) {
		if (edge._capacity - edge._flow > 0) {
			paths.push({ &edge });
			visited.push_back(edge._to->_id);
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
				if (count(visited.begin(), visited.end(), edge._to->_id) == 0 && (edge._capacity - edge._flow) > 0) {
					auto new_path{ path };
					new_path.push_back(&edge);
					paths.push(new_path);
					visited_frontier.push_back(edge._to->_id);
					if (edge._to->_id == target->_id) {
						reached_target = true;
						level_graph->push_back(new_path);
					}
				}
			}
		}
		for (auto id : visited_frontier) {
			visited.push_back(id);
		}
		visited_frontier.clear();
	}
	return std::move(level_graph);
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
