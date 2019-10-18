#include "Transform.h"
#include <glm/gtx/matrix_decompose.hpp>

glm::vec3 Transform::TransformPosition(const glm::vec3& InPosition) const
{
	return glm::vec3(GetMatrix() * glm::vec4(InPosition, 1.f));
}

glm::quat Transform::TransformRotation(const glm::quat& InRotation) const
{
	return Rotation * InRotation;
}

glm::vec3 Transform::InverseTransformPosition(const glm::vec3& InPosition) const
{
	return glm::vec3(glm::inverse(GetMatrix()) * glm::vec4(InPosition, 1.f));
}

glm::quat Transform::InverseTransformRotation(const glm::quat& InRotation) const
{
	return glm::inverse(Rotation) * InRotation;
}

Transform Transform::Inverse() const
{
	glm::mat4 MyMatrix = GetMatrix();
	MyMatrix = glm::inverse(MyMatrix);

	Transform ResultTransform;
	glm::vec3 Skew;
	glm::vec4 Perspective;

	glm::decompose(MyMatrix, ResultTransform.Scale, ResultTransform.Rotation, ResultTransform.Position, Skew, Perspective);
	return ResultTransform;
}

glm::mat4 Transform::GetMatrix() const
{
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(1.f), Scale);
	glm::mat4 RotationMatrix = glm::mat4_cast(Rotation);
	glm::mat4 PositionMatrix = glm::translate(glm::mat4(1.f), Position);

	return PositionMatrix * RotationMatrix * ScaleMatrix;
}

Transform Transform::operator*(const Transform& Other) const
{
	glm::mat4 MyMatrix = GetMatrix();
	glm::mat4 OtherMatrix = Other.GetMatrix();
	glm::mat4 ResultMatrix = MyMatrix * OtherMatrix;

	Transform ResultTransform;
	glm::vec3 Skew;
	glm::vec4 Perspective;

	glm::decompose(ResultMatrix, ResultTransform.Scale, ResultTransform.Rotation, ResultTransform.Position, Skew, Perspective);
	return ResultTransform;
}
