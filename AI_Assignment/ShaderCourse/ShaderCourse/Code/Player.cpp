#include "Player.h"

glm::vec3 Player::GetForwardVector()
{
	glm::quat YawQuat = glm::angleAxis(glm::radians(Yaw), glm::vec3(0.f, 1.f, 0.f));
	glm::quat PitchQuat = glm::angleAxis(glm::radians(Pitch), glm::vec3(1.f, 0.f, 0.f));

	glm::quat FinalQuat = YawQuat * PitchQuat;
	return FinalQuat * glm::vec3(0.f, 0.f, -1.f);
}

glm::vec3 Player::GetRightVector()
{
	return glm::normalize(glm::cross(GetForwardVector(), glm::vec3(0.f, 1.f, 0.f)));
}

void Player::AddYaw(float YawAngle)
{
	Yaw += YawAngle;
}

void Player::AddPitch(float PitchAngle)
{
	Pitch += PitchAngle;
	Pitch = glm::clamp(Pitch, -85.f, 85.f);
}

glm::mat4 Player::GetViewMatrix()
{
	return glm::lookAt(position, position + GetForwardVector(), glm::vec3(0.f, 1.f, 0.f));
}

Transform Player::GetTransform() const
{
	Transform Result;
	Result.Position = position;

	// Calculate rotation
	glm::quat YawQuat = glm::angleAxis(glm::radians(Yaw), glm::vec3(0.f, 1.f, 0.f));
	glm::quat PitchQuat = glm::angleAxis(glm::radians(Pitch), glm::vec3(1.f, 0.f, 0.f));
	Result.Rotation = YawQuat * PitchQuat;

	return Result;
}