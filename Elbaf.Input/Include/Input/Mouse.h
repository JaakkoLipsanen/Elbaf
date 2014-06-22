#pragma once
#include <Math\Vector.h>

enum class CursorVisibility;
namespace Mouse
{
	void SetCursorVisibility(CursorVisibility cursorType);
	void SetPosition(const Vector2f& position);
}