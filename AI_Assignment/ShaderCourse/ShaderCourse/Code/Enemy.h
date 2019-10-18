#pragma once

#include "Position.h"
#include "Transform.h"
#include <vector>
#include "AStar.h"

class Enemy
{
public:
	glm::vec3 position = glm::vec3(0.f);
	glm::vec3 desiredPosition = glm::vec3(0.f);

	int currentPathIndex = 10;
	std::vector<Node> currentPath = std::vector<Node>();

	int curX = 0;
	int curY = 0;

	int goalX = 0;
	int goalY = 0;

	float Yaw = 0.f;
	float Pitch = 0.f;

	glm::vec3 GetForwardVector();
	glm::vec3 GetRightVector();
	void AddYaw(float YawAngle);
	void AddPitch(float PitchAngle);
	glm::mat4 GetViewMatrix();
	Transform GetTransform() const;
};
