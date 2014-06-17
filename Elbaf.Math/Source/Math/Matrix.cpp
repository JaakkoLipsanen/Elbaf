#include "Matrix.h"
#include <glm\gtc\matrix_transform.hpp>

Matrix4x4 Matrix::CreateLookAt(Vector3f const& eye, Vector3f const& target, Vector3f const& up)
{
	return glm::lookAt(eye, target, up);
}

Matrix4x4 Matrix::CreateOrtographic(float const& left, float const& right, float const& bottom, float const& top)
{
	return glm::ortho(left, right, bottom, top);
}

Matrix4x4 Matrix::CreateOrtographic(float const& left, float const& right, float const& bottom, float const& top, float const& zNear, float const& zFar)
{
	return glm::ortho(left, right, bottom, top, zNear, zFar);
}

Matrix4x4 Matrix::CreatePerspective(float const& verticalFov, float const& aspectRatio, float const& zNear, float const& zFar)
{
	return glm::perspective(verticalFov, aspectRatio, zNear, zFar);
}

// scale
Matrix4x4 Matrix::Scale(Vector3f const& scale)
{
	return glm::scale(Matrix4x4(), scale);
}

Matrix4x4 Matrix::Scale(float const& scale)
{
	return glm::scale(Matrix4x4(), Vector3f(scale));
}

Matrix4x4 Matrix::Scale(float const& x, float const& y, float const& z)
{
	return glm::scale(Matrix4x4(), Vector3f(x, y, z));
}

// translate
Matrix4x4 Matrix::Translate(Vector3f const& translateAmount)
{
	return glm::translate(Matrix4x4(), translateAmount);
}

Matrix4x4 Matrix::Translate(float const& x, float const& y, float const& z)
{
	return glm::translate(Matrix4x4(), Vector3f(x, y, z));
}

// rotate
Matrix4x4 Matrix::RotateAroundAxis(float const& angle, Vector3f const& rotateAxis)
{
	return glm::rotate(Matrix4x4(), angle, rotateAxis);
}

// misc
Matrix4x4 Matrix::Inverse(Matrix4x4 const& input)
{
	return glm::inverse(input);
}

Matrix4x4 Matrix::Transpose(Matrix4x4 const& input)
{
	return glm::transpose(input);
}