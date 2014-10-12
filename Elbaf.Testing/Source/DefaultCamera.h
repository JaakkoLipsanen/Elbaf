#pragma once
#include <Engine/ICamera.h>

// from OGL tutorial mostly
class DefaultCamera : public ICamera
{
public:
	DefaultCamera();
	virtual Matrix4x4 GetView() override;
	virtual Matrix4x4 GetProjection() override;

	void Update();
	Vector3f GetPosition() const { return _position; }

private:
	Matrix4x4 _view;
	Matrix4x4 _projection;

	Vector3f _position;
	Vector2f _rotationAngle; // :| ?

	void UpdateView();
	Vector3f CalculateDirection() const;
};