#include "Quad.h"


namespace ttg
{
	QuadData::QuadData(float _offset, glm::vec3 _pos)
	{
		offset = _offset;
		position = _pos;
		lowLeft = glm::vec3(_pos.x - offset, _pos.y - offset, 0.0f);
		highLeft = glm::vec3(_pos.x - offset, _pos.y + offset, 0.0f);
		highRight = glm::vec3(_pos.x + offset, _pos.y + offset, 0.0f);
		lowRight = glm::vec3(_pos.x + offset, _pos.y - offset, 0.0f);
	}

	bool IsMouseOver(QuadData* data, const glm::vec3& origin, const glm::vec3& direction)
	{
		glm::vec3 C = data->position;
		glm::vec3 L = C - origin;

		float tca = glm::dot(L, direction);
		if (tca < 0) return false;




		/*bool withinX = mx > data->lowLeft.r && mx < data->lowRight.r;
		bool withinY = my > data->lowLeft.g && my < data->highLeft.g;*/

		return false;
		//return withinX && withinY;
	}
}
