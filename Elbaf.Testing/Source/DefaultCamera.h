#pragma once
#include "ICamera.h"

// from OGL tutorial mostly
class DefaultCamera : public ICamera
{
public:
	DefaultCamera();
	virtual Matrix4x4 const& GetView() const override;
	virtual Matrix4x4 const& GetProjection() const override;

	void Update();
	const Vector3f& GetPosition() const { return _position; }

private:
	Matrix4x4 _view;
	Matrix4x4 _projection;

	Vector3f _position = Vector3f::UnitY * 40;
	Vector2f _rotationAngle; // :| ?

	void UpdateView();
	Vector3f CalculateDirection() const;
};