#pragma once
#include "DefaultCamera.h"
#include <Engine\Screen.h>
#include <Input\Input.h>
#include <Engine\Time.h>

// from OGL tutorial mostly
DefaultCamera::DefaultCamera()
{
	_projection = Matrix::CreatePerspective(90, Screen::GetSize().GetAspectRatio(), 0.1f, 1000.0f);
	this->UpdateView();
}

Matrix4x4 const& DefaultCamera::GetView() const
{
	return _view;
}

Matrix4x4 const& DefaultCamera::GetProjection() const
{
	return _projection;
}

void DefaultCamera::Update()
{
	Vector3f cross = Vector::Cross(this->CalculateDirection(), Vector3f::UnitY);
	const float MovementSpeed = 25.0f;
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

	this->UpdateView();
}

void DefaultCamera::UpdateView()
{
	_view = Matrix::CreateLookAt(_position, _position + this->CalculateDirection(), Vector3f::UnitY);
}

Vector3f DefaultCamera::CalculateDirection() const
{
	return Vector3f(
		cos(_rotationAngle.y) * sin(_rotationAngle.x),
		sin(_rotationAngle.y),
		cos(_rotationAngle.y) * cos(_rotationAngle.x));
}