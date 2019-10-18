#pragma once

#include "glm/glm.hpp"

class BezierSurface
{
public:
	const int GridSize = 4;
	float Size = 1.0;

	glm::vec3 ControlVertices[4 * 4];
	glm::vec3* Vertices;

	glm::vec3 PositionVertex;

	int UResolution = 8;
	int VResolution = 8;

	float U = 0.0;
	float V = 0.0;

	void Setup();

	void RecalculateVertices();
	glm::vec3 EvaluateBezierSurface(glm::vec3 P[], float U, float V);
	glm::vec3 EvaluateBezierCurve(glm::vec3 P[], float T);
	glm::vec3* CalculateVertices(glm::vec3* CV, int ResU, int ResV);
};
