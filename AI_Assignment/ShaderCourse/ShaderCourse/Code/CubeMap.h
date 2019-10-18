#pragma once
#include <GL/glew.h>

class CubeMap
{
public:
	GLuint Handle;
	void LoadFiles(const char** Paths);
	void Bind(int Index = 0);
};