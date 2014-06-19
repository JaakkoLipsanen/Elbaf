#pragma once
#include <Math\Matrix.h>

class ICamera
{
public:
	virtual const Matrix4x4& GetView() const = 0;
	virtual const Matrix4x4& GetProjection() const = 0;

	virtual ~ICamera() { }
};