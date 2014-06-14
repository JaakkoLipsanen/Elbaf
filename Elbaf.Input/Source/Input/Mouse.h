#pragma once
#include <Core\CursorVisibility.h>
#include <Math\Vector.h>

namespace Mouse
{
	void SetCursorVisibility(CursorVisibility cursorType);
	void SetPosition(const Vector2f& position);
}