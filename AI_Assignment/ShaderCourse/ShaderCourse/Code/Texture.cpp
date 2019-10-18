#include "Texture.h"
#include <SOIL.h>
#include <cstring>

void SwizzleRows(unsigned char* Data, int Width, int Height)
{
	unsigned char* Temp = new unsigned char[Width * 4];
	int NumSwaps = Height / 2;

	for (int i = 0; i < NumSwaps; ++i)
	{
		unsigned char* SourcePtr = Data + (Width * 4) * i;
		unsigned char* TargetPtr = Data + (Width * 4) * (Height - i - 1);

		// Step 1) Copy the source row to the temp buffer
		memcpy(Temp, SourcePtr, Width * 4);

		// Step 2) Copy the target row to the source row
		memcpy(SourcePtr, TargetPtr, Width * 4);

		// Step 3) Copy the temp buffer to our target row
		memcpy(TargetPtr, Temp, Width * 4);
	}

	delete[] Temp;
}

void Texture::LoadFile(const char* File)
{
	int Width;
	int Height;
	int Channels;
	unsigned char* ImagePixels = SOIL_load_image(File, &Width, &Height, &Channels, SOIL_LOAD_RGBA);
	SwizzleRows(ImagePixels, Width, Height);

	glGenTextures(1, &Handle);
	glBindTexture(GL_TEXTURE_2D, Handle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ImagePixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	SOIL_free_image_data(ImagePixels);
}

void Texture::Bind(int Index)
{
	glActiveTexture(GL_TEXTURE0 + Index);
	glBindTexture(GL_TEXTURE_2D, Handle);
}
