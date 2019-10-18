#include "Mesh.h"

void Mesh::LoadVerts(const float* Verts, int VertSize, const unsigned int* Indicies, int IndexSize)
{
	glGenVertexArrays(1, &VertexObject);
	glBindVertexArray(VertexObject);

	// Load vertex data
	glGenBuffers(1, &Buffer);
	glBindBuffer(GL_ARRAY_BUFFER, Buffer);
	glBufferData(GL_ARRAY_BUFFER, VertSize, Verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, (3 + 3 + 2) * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, (3 + 3 + 2) * sizeof(float), (void*)((3) * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, false, (3 + 3 + 2) * sizeof(float), (void*)((3 + 3) * sizeof(float)));

	// Load index data
	if (Indicies != nullptr)
	{
		glGenBuffers(1, &IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndexSize, Indicies, GL_STATIC_DRAW);
	}

	glBindVertexArray(0);
}

void Mesh::Bind()
{
	glBindVertexArray(VertexObject);
}
