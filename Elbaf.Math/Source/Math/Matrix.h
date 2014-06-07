#pragma once
#include <glm\glm.hpp>
#include "Vector.h"

// todo: typedef others?
typedef glm::mat4 Matrix4x4;

namespace Matrix
{
	Matrix4x4 CreateLookAt(Vector3f eye, Vector3f target, Vector3f up);
	// CreatePerspective, CreateOrthogonal, Translate, Scale, Rotate etc etc
}