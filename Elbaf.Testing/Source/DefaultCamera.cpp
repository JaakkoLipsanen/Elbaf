#pragma once
#include "DefaultCamera.h"

#include <Engine\Screen.h>
#include <Input\KeyCode.h>
#include <Input\Input.h>
#include <Engine\Time.h>
#include <Math\FlaiMath.h>
#include <Diagnostics\Logger.h>

static const float NearZ = 0.1f;
static const float FarZ = 1000.0f;
static const float VerticalFOV = 75;

// from OGL tutorial mostly
DefaultCamera::DefaultCamera() : _position(Vector3f::One * 400)
{
	_projection = Matrix::CreatePerspective(VerticalFOV, Screen::GetSize().GetAspectRatio(), NearZ, FarZ);
	this->UpdateView();
}

Matrix4x4 DefaultCamera::GetView() const
{
	return _view;
}

Matrix4x4 DefaultCamera::GetProjection() const
{
	return _projection;
}

float DefaultCamera::GetNearZ() const
{
	return NearZ;
}

float DefaultCamera::GetFarZ() const
{
	return FarZ;
}

float DefaultCamera::GetVerticalFieldOfView() const
{
	return VerticalFOV;
}

float DefaultCamera::GetAspectRatio() const
{
	return 16.0f / 9.0f;
}

void DefaultCamera::Update()
{
	Vector3f cross = Vector::Normalize(Vector::Cross(this->CalculateDirection(), Vector3f::UnitY));
	const float DefaultMovementSpeed = 25.0f;
	float MovementSpeed = DefaultMovementSpeed * (Input::IsKeyPressed(KeyCode::LeftShift) ? 4 : 1);
	if (Input::IsKeyPressed(KeyCode::W))
	{
		_position += this->CalculateDirection() * MovementSpeed * Time::GetDeltaTime();
	}
	if (Input::IsKeyPressed(KeyCode::S))
	{
		_position -= this->CalculateDirection() * MovementSpeed * Time::GetDeltaTime();
	}
	if (Input::IsKeyPressed(KeyCode::A))
	{
		_position -= cross * MovementSpeed * Time::GetDeltaTime();
	}
	if (Input::IsKeyPressed(KeyCode::D))
	{
		_position += cross * MovementSpeed * Time::GetDeltaTime();
	}

	_rotationAngle += Input::GetMousePositionDelta() * Vector2f(-1, -1) * 0.005f;
	_rotationAngle.Y = FlaiMath::Clamp(_rotationAngle.y, -FlaiMath::Pi / 2 + 0.01f, FlaiMath::Pi / 2 - 0.01f);

	this->UpdateView();
}

void DefaultCamera::UpdateView()
{
	_view = Matrix::CreateLookAt(_position, _position + this->CalculateDirection(), Vector3f::UnitY);
}

Vector3f DefaultCamera::CalculateDirection() const
{
	return Vector::Normalize(Vector3f(
		cos(_rotationAngle.y) * sin(_rotationAngle.x),
		sin(_rotationAngle.y),
		cos(_rotationAngle.y) * cos(_rotationAngle.x)));
}