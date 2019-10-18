#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

const glm::quat quat_identity = glm::identity<glm::quat>();

class Transform
{
public:
	glm::vec3 Position = glm::vec3(0.f);
	glm::quat Rotation = glm::identity<glm::quat>();
	glm::vec3 Scale = glm::vec3(1.f);

	Transform() {}
	Transform(const glm::vec3& Position) : Position(Position) {}
	Transform(const glm::vec3& Position, const glm::quat& Rotation) : Position(Position), Rotation(Rotation) {}
	Transform(const glm::vec3& Position, const glm::vec3& Scale) :
		Position(Position), Scale(Scale){}
	Transform(const glm::vec3& Position, const glm::quat& Rotation, const glm::vec3& Scale) :
		Position(Position), Rotation(Rotation), Scale(Scale) {}

	glm::vec3 TransformPosition(const glm::vec3& InPosition) const;
	glm::quat TransformRotation(const glm::quat& InRotation) const;
	glm::vec3 InverseTransformPosition(const glm::vec3& InPosition) const;
	glm::quat InverseTransformRotation(const glm::quat& InRotation) const;

	Transform Inverse() const;
	glm::mat4 GetMatrix() const;
	Transform operator*(const Transform& Other) const;
};
