#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>

class Mesh
{
public:
	void LoadVerts(const float* Verts, int VertSize, const unsigned int* Indicies, int IndexSize);
	void Bind();

	GLuint VertexObject;
	GLuint Buffer;
	GLuint IndexBuffer;
};