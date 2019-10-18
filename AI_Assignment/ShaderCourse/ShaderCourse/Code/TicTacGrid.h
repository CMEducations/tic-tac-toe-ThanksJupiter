#pragma once
#include "glm/glm.hpp"

namespace ttg
{
	const int size = 9;
	const int rows = 3;
	const int columns = 3;

	struct GameInstanceData
	{
		int states[size] = { 0 };
		glm::vec3 positions[size] = {};

		GameInstanceData(float offset);
	};
}
