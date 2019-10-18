#pragma once
#include <glm/glm.hpp>
class Material;

class SpotLight
{
public:
	glm::vec3 Position;
	glm::vec3 Direction;
	glm::vec3 Color;
	float Length;
	float Angle;

	void UploadToMaterial(const Material& TargetMaterial);
};