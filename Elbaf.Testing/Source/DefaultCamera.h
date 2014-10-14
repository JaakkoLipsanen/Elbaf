#pragma once
#include <Engine/ICamera.h>

// from OGL tutorial mostly
class DefaultCamera : public ICamera
{
public:
	DefaultCamera();
	virtual Matrix4x4 GetView() const override;
	virtual Matrix4x4 GetProjection() const override;

	void Update();
	virtual Vector3f GetPosition() const override  { return _position; }
	virtual Vector3f GetDirection() const override { return this->CalculateDirection(); }
	virtual float GetNearZ() const override;
	virtual float GetFarZ() const override;

	float GetVerticalFieldOfView() const;
	float GetAspectRatio() const;

private:
	Matrix4x4 _view;
	Matrix4x4 _projection;

	Vector3f _position;
	Vector2f _rotationAngle; // :| ?

	void UpdateView();
	Vector3f CalculateDirection() const;
};