#pragma once

#include "Position.h"
#include "Transform.h"

class Player
{
public:
	glm::vec3 position = glm::vec3(0.f);

	float Yaw = 0.f;
	float Pitch = 0.f;

	glm::vec3 GetForwardVector();
	glm::vec3 GetRightVector();
	void AddYaw(float YawAngle);
	void AddPitch(float PitchAngle);
	glm::mat4 GetViewMatrix();
	Transform GetTransform() const;
};
