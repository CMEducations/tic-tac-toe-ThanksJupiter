#pragma once
#include "glm/glm.hpp"

namespace ttg
{
	struct QuadData
	{
		glm::vec3 position;
		glm::vec3 normal;
		float offset;
		bool mouseOver = false;

		glm::vec3 lowLeft;
		glm::vec3 highLeft;
		glm::vec3 highRight;
		glm::vec3 lowRight;

		QuadData(float _offset, glm::vec3 _position);
	};

	bool IsMouseOver(QuadData* data, const glm::vec3& origin, const glm::vec3& direction);
}
