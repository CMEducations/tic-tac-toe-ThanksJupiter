#include "BezierSurface.h"

void BezierSurface::Setup()
{
	int y = 0;
	for (int i = 0, y = 0; y < GridSize; y++)
	{
		for (int x = 0; x < GridSize; x++, i++)
		{
			ControlVertices[i] = glm::vec3(x * Size, 0.0, y * Size);
		}
	}

	RecalculateVertices();
}

void BezierSurface::RecalculateVertices()
{
	PositionVertex = EvaluateBezierSurface(ControlVertices, U, V);
	Vertices = CalculateVertices(ControlVertices, UResolution, VResolution);
}

glm::vec3 BezierSurface::EvaluateBezierSurface(glm::vec3 p[], float u, float v)
{
	glm::vec3 PU[4] = {};

	for (int i = 0; i < 4; ++i)
	{
		glm::vec3 CurveP[4] = {};
		CurveP[0] = p[i * 4];
		CurveP[1] = p[i * 4 + 1];
		CurveP[2] = p[i * 4 + 2];
		CurveP[3] = p[i * 4 + 3];
		PU[i] = EvaluateBezierCurve(CurveP, U);
	}

	return EvaluateBezierCurve(PU, V);
}

glm::vec3 BezierSurface::EvaluateBezierCurve(glm::vec3 P[], float T)
{
	float B0 = (1 - T) * (1 - T) * (1 - T);
	float B1 = 3 * T * (1 - T) * (1 - T);
	float B2 = 3 * T * T * (1 - T);
	float B3 = T * T * T;
	return P[0] * B0 + P[1] * B1 + P[2] * B2 + P[3] * B3;
}

glm::vec3* BezierSurface::CalculateVertices(glm::vec3* CV, int ResU, int ResV)
{
	glm::vec3 TmpVerts[9 * 9] = {};

	int UDivs = ResU - 1;
	int VDivs = ResV - 1;

	for (int u = 0, i = 0; u <= UDivs; u++)
	{
		for (int v = 0; v <= VDivs; v++, i++)
		{
			TmpVerts[i] = EvaluateBezierSurface(CV, v / (float)VDivs, u / (float)UDivs);
		}
	}

	return TmpVerts;
}
