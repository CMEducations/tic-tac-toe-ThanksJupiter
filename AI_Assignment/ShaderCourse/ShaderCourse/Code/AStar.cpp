#include "AStar.h"
#include <iostream>
#include <stack>

std::vector<Node> Pathfinder::aStar(Node player, Node dest)
{
	std::vector<Node> empty;
	if (!isValid(dest.x, dest.y))
	{
		std::cout << "pos x: " << dest.x << " & pos y: " << dest.y <<
			"one or both of 'em are invalid" << std::endl;
	}

	if (isDestination(player.x, player.y, dest))
	{
		std::cout << "you are at the destination" << std::endl;
		return empty;
	}

	bool closedList[X_MAX][Y_MAX];
	Node allMap[X_MAX][Y_MAX];

	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			allMap[x][y].fCost = INFINITY;
			allMap[x][y].gCost = INFINITY;
			allMap[x][y].fCost = INFINITY;
			allMap[x][y].parentX = -1;
			allMap[x][y].parentY = -1;
			allMap[x][y].x = x;
			allMap[x][y].y = y;

			closedList[x][y] = false;
		}
	}

	int x = player.x;
	int y = player.y;

	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	std::vector<Node> openList;
	openList.emplace_back(allMap[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < X_MAX * Y_MAX)
	{
		Node node;
		do
		{
			float temp = INFINITY;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin();
				 it != openList.end(); it = next(it))
			{
				Node n = *it;
				if (n.fCost < temp)
				{
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!isValid(node.x, node.y));

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		for (int newX = -1; newX <= 1; newX++)
		{
			for (int newY = -1; newY <= 1; newY++)
			{
				float gNew, hNew, fNew;

				if (isValid(x + newX, y + newY))
				{
					if (isDestination(x + newX, y + newY, dest))
					{
						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						destinationFound = true;
						return makePath(allMap, dest);
					} 
					else if (closedList[x + newX][y + newY] == false)
					{
						gNew = node.gCost + 1.0;
						hNew = calculateH(x + newX, y + newY, dest);
						fNew = gNew + hNew;

						if (allMap[x + newX][y + newY].fCost == INFINITY ||
							allMap[x + newX][y + newY].fCost > fNew)
						{
							allMap[x + newX][y + newY].fCost = fNew;
							allMap[x + newX][y + newY].gCost = gNew;
							allMap[x + newX][y + newY].hCost = hNew;
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							openList.emplace_back(allMap[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (destinationFound == false)
	{
		std::cout << "destination not found" << std::endl;
		return empty;
	}
}

std::vector<Node> Pathfinder::aStar(Node player, Node dest, Node grid[X_MAX][Y_MAX])
{
	std::vector<Node> empty;
	if (!isValid(dest.x, dest.y))
	{
		std::cout << "pos x: " << dest.x << " & pos y: " << dest.y <<
			"one or both of 'em are invalid" << std::endl;
	}

	if (isDestination(player.x, player.y, dest))
	{
		std::cout << "you are at the destination" << std::endl;
		return empty;
	}

	bool closedList[X_MAX][Y_MAX];
	Node allMap[X_MAX][Y_MAX];

	for (int x = 0; x < X_MAX; x++)
	{
		for (int y = 0; y < Y_MAX; y++)
		{
			if (grid[x][y].isObstacle)
			{
				closedList[x][y] = true;
				continue;
			}

			allMap[x][y].fCost = INFINITY;
			allMap[x][y].gCost = INFINITY;
			allMap[x][y].fCost = INFINITY;
			allMap[x][y].parentX = -1;
			allMap[x][y].parentY = -1;
			allMap[x][y].x = x;
			allMap[x][y].y = y;

			closedList[x][y] = false;
		}
	}

	int x = player.x;
	int y = player.y;

	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	std::vector<Node> openList;
	openList.emplace_back(allMap[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < X_MAX * Y_MAX)
	{
		Node node;
		do
		{
			float temp = INFINITY;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin();
				 it != openList.end(); it = next(it))
			{
				Node n = *it;
				if (n.fCost < temp)
				{
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!isValid(node.x, node.y));

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		for (int newX = -1; newX <= 1; newX++)
		{
			for (int newY = -1; newY <= 1; newY++)
			{
				float gNew, hNew, fNew;

				if (isValid(x + newX, y + newY))
				{
					if (isDestination(x + newX, y + newY, dest))
					{
						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						destinationFound = true;
						return makePath(allMap, dest);
					} else if (closedList[x + newX][y + newY] == false)
					{
						gNew = node.gCost + 1.0;
						hNew = calculateH(x + newX, y + newY, dest);
						fNew = gNew + hNew;

						if (allMap[x + newX][y + newY].fCost == INFINITY ||
							allMap[x + newX][y + newY].fCost > fNew)
						{
							allMap[x + newX][y + newY].fCost = fNew;
							allMap[x + newX][y + newY].gCost = gNew;
							allMap[x + newX][y + newY].hCost = hNew;
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							openList.emplace_back(allMap[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (destinationFound == false)
	{
		std::cout << "Destination not found" << std::endl;
		return empty;
	}
}

std::vector<Node> Pathfinder::makePath(Node map[Y_MAX][X_MAX], Node dest)
{
	try
	{
		std::cout << "found a path" << std::endl;
		int x = dest.x;
		int y = dest.y;

		std::stack<Node> path;
		std::vector<Node> usablePath;

		while (!(map[x][y].parentX == x && map[x][y].parentY == y)
			   && map[x][y].x != -1 && map[x][y].y != -1)
		{
			path.push(map[x][y]);
			int tempX = map[x][y].parentX;
			int tempY = map[x][y].parentY;
			x = tempX;
			y = tempY;
		}
		path.push(map[x][y]);

		while (!path.empty())
		{
			Node top = path.top();
			path.pop();
			usablePath.emplace_back(top);
		}
		return usablePath;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}
