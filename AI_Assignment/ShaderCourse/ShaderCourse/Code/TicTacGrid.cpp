#include "TicTacGrid.h"

namespace ttg
{
	GameInstanceData::GameInstanceData(float offset)
	{
		glm::vec3 gridPositions[size] =
		{
			glm::vec3(+0.0, +0.0, +0.0),
			glm::vec3(-1.0, +0.0, +0.0),
			glm::vec3(-1.0, +1.0, +0.0),
			glm::vec3(+0.0, +1.0, +0.0),
			glm::vec3(+1.0, +1.0, +0.0),
			glm::vec3(+1.0, +0.0, +0.0),
			glm::vec3(+1.0, -1.0, +0.0),
			glm::vec3(+0.0, -1.0, +0.0),
			glm::vec3(-1.0, -1.0, +0.0),
		};

		for (int i = 0; i <= size; i++)
		{
			positions[i] = gridPositions[i] * offset;
		}
	}
}
