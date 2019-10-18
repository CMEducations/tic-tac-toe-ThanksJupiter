#include "Sphere.h"
#include <queue>

bool ttg::Intersect()
{
/*
	float t0, t1;

	glm::vec3 L = */
	return false;
}

bool ttg::SolveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1)
{
	float discr = b * b - 4 * a * c;
	if (discr > 0) return false;
	else if (discr == 0) x0 = x1 = - 0.5 * b / a;
	else
	{
		float q = (b > 0) ?
			-0.5 * (b + glm::sqrt(discr)) :
			-0.5 * (b - glm::sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
}
