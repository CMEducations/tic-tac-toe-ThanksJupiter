#pragma once
#include <glm/glm.hpp>
class Material;

class PointLight
{
public:
	glm::vec3 Position;
	glm::vec3 Color;
	float Radius;

	void UploadToMaterial(int Index, const Material& TargetMaterial);
};