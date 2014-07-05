#pragma once
#include <Math/Vector.h>
#include <Math/Matrix.h>

class ICamera
{
public:
	ICamera() = default;
	virtual ~ICamera() = default;

	virtual Matrix4x4 GetView() = 0;
	virtual Matrix4x4 GetProjection() = 0;
};