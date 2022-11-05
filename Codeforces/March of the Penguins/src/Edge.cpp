#include "Edge.hpp"


Edge::Edge(Node* from, std::shared_ptr<Node> to, int capacity) : _from{ from }, _to{ to }, _capacity{ capacity } {}
