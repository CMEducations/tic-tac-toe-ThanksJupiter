#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Material
{
public:
	static int MyValue;
	void LoadFiles(const char* VertexPath, const char* FragmentPath);
	void Use() const;
	void Set(const char* name, const glm::mat4& value) const;
	void Set(const char* name, const glm::vec3& value) const;
	void Set(const char* name, const int value) const;
	void Set(const char* name, const float value) const;

	GLuint ProgramHandle;
};