#pragma once
#include "glm/glm.hpp"
#include <vector>

#define X_MAX 8
#define Y_MAX 8

struct Node
{
	int y;
	int x;
	int parentX;
	int parentY;
	float gCost;
	float hCost;
	float fCost;
	bool isObstacle;

	Node() {};
	Node(int _x, int _y) : x(_x), y(_y) { isObstacle = false; };
};

inline bool operator < (const Node& lhs, const Node& rhs)
{
	return lhs.fCost < rhs.fCost;
}

class Pathfinder
{
public:
	static bool isValid(int x, int y)
	{
		return x >= 0 && x < X_MAX && y >= 0 && y < Y_MAX;
	}

	static bool isDestination(int x, int y, Node dest)
	{
		return x == dest.x && y == dest.y;
	}

	static float calculateH(int x, int y, Node dest)
	{
		return (
			glm::sqrt(
			(x - dest.x) * (x - dest.x) +
			(y - dest.y) * (y - dest.y))
			);
	}

	static std::vector<Node> aStar(Node player, Node dest);
	static std::vector<Node> aStar(Node player, Node dest, Node grid[X_MAX][Y_MAX]);

	static std::vector<Node> makePath(Node map[Y_MAX][X_MAX], Node dest);

};