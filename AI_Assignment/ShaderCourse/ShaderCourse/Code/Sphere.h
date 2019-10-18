#pragma once

#include "glm/glm.hpp"

namespace ttg
{
	struct SphereData
	{
		glm::vec3 position;
		float radius;

		SphereData(const glm::vec3& _position, const float& _radius) : position(_position), radius(_radius) {}
	};

	bool Intersect();
	bool SolveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1);
}
