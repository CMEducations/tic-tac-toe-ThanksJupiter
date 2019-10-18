#pragma once

#include "glm/glm.hpp"

struct Position
{
	glm::vec3 value;

	Position() { value = glm::vec3(0.f, 0.f, 0.f); }
	Position(const glm::vec3 _value) : value(_value) {}
};
