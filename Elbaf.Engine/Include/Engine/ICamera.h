#pragma once
#include <Math/Vector.h>
#include <Math/Matrix.h>

class ICamera
{
public:
	ICamera() = default;
	virtual ~ICamera() = default;

	virtual Matrix4x4 GetView() const = 0;
	virtual Matrix4x4 GetProjection() const = 0;

	virtual Vector3f GetPosition() const = 0;
	virtual Vector3f GetDirection() const = 0;
	virtual float GetNearZ() const = 0;
	virtual float GetFarZ() const = 0;
};