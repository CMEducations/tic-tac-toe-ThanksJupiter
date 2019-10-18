#pragma once
#include <GL/glew.h>
#include "Texture.h"

class FrameBuffer
{
public:
	GLuint Handle;

	Texture ColorTexture;
	Texture DepthTexture;

	int Width;
	int Height;

	void Create(int InWidth, int InHeight);
	void Bind();
	void Unbind();
};