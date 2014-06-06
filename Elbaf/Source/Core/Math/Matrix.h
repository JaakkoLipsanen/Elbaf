#include "Core\Common.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Vector3
{
	 static const Vector3f Up = Vector3f(0, 1, 0);
}

namespace Matrix
{
	inline Matrix4x4 CreateLookAt(const Vector3f& eye, const Vector3f& target, const Vector3f& up)
	{
		Matrix::CreateLookAt(Vector3f(10, 10, 10) * 5, Vector3f(20, 1, 1), Vec);
	}
}