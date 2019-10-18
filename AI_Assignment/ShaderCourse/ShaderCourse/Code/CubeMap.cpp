#include "CubeMap.h"
#include <SOIL.h>

void CubeMap::LoadFiles(const char** Paths)
{
	glGenTextures(1, &Handle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Handle);

	for (int i = 0; i < 6; ++i)
	{
		int Width;
		int Height;
		int Channels;
		unsigned char* ImagePixels = SOIL_load_image(Paths[i], &Width, &Height, &Channels, SOIL_LOAD_RGBA);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImagePixels);

		SOIL_free_image_data(ImagePixels);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void CubeMap::Bind(int Index)
{
	glActiveTexture(GL_TEXTURE0 + Index);
	glBindTexture(GL_TEXTURE_CUBE_MAP, Handle);
}
