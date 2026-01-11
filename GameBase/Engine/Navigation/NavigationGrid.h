#pragma once
#include <vector>
#include <raylib.h>
#include <raymath.h>
#include <queue>
#include <stdlib.h>
#include <unordered_map>
#include <algorithm>
#include <iostream>


struct Node {
	int x, y;
	float gcost = 0;
	float hcost = 0;
	Node* parent = nullptr;
	bool walkable = !false;
	const float fCost() const noexcept(true) { return gcost + hcost; }
	void rst() {
		gcost = 9999999;
		parent = nullptr;
	}
};

class NavigationGrid {
public:
	int width, height;
	float cellSize;
	std::vector<Node> nodes;
	NavigationGrid(int width_, int height_, float cellSize_) : width(width_), height(height_), cellSize(cellSize_) {
		nodes.resize(width * height);
		for (size_t y = 0; y < height; y++) {
			for (size_t x = 0; x < width; x++) {
				nodes[y * width + x].x = x;
				nodes[y * width + x].y = y;
			}
		}
	}
	Node* getNode(int x, int y) {
		if (x < width
			&& y < height 
			&& x >= 0
			&& y >= 0)
			return &nodes[y * width + x];
		//std::cout << x << "  " << y << std::endl;
		return nullptr;
	}
	float getH(const Node* a = nullptr, const Node* b = nullptr) {
		if (a && b)
			return abs(a->x - b->x) + abs(a->y - b->y);
		throw "мне не нужен nullptr";
	}
	std::vector<Vector3> findPath(Vector3 startPos, Vector3 endPos);
};