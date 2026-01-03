#include "NavigationGrid.h"

std::vector<Vector3> NavigationGrid::findPath(Vector3 startPos, Vector3 endPos) {
	int 
		startX = round(startPos.x / cellSize),
		startY = round(startPos.z / cellSize),
		endX   = round(endPos.x / cellSize),
		endY   = round(endPos.z / cellSize);
	Node
		*startNode = this->getNode(startX, startY),
		*endNode = this->getNode(endX, endY);

	if (!startNode || !endNode || !endNode->walkable || !startNode->walkable) return {};
	for (auto& e : nodes) e.rst();
	auto cmp = [] (const Node* a, const Node* b) {
		return a->fCost() > b->fCost();
		};
	std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> openSet(cmp);
	startNode->gcost = 0;
	startNode->hcost = this->getH(startNode, endNode);
	openSet.push(startNode);
	while (not openSet.empty()) {
		Node* curr = openSet.top();
		openSet.pop();
		if (curr == endNode) {
			std::vector<Vector3> path;
			while (curr) {
				path.push_back({ curr->x * cellSize, 0.f, curr->y * cellSize });
				curr = curr->parent;
			}
			std::reverse(path.begin(), path.end());
			return path;
		}
		int dx[] = {0, 0, 1, -1};
		int dy[] = {1, -1, 0, 0};
		for (size_t i = 0; i < std::size(dx); i++) {
			Node* neighbour = getNode(curr->x + dx[i], curr->y + dy[i]);
			if (not neighbour || not neighbour->walkable) continue;
			float nwCost = curr->gcost + 1;
			if (nwCost < neighbour->gcost) {
				neighbour->parent = curr;
				neighbour->gcost = nwCost;
				neighbour->hcost = getH(neighbour, endNode);
				openSet.push(neighbour);
			}
		}
	}
	return {};
}