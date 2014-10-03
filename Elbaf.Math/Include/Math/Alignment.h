#pragma once
#include <Math/Vector.h>

enum class Axis
{
	Horizontal,
	Vertical
};

namespace AxisHelper
{
	static Vector2i ToUnitVector(const Axis& axis)
	{
		return (axis == Axis::Horizontal) ? Vector2i::UnitX : Vector2i::UnitY;
	}

	static Axis Inverse(const Axis& axis)
	{
		return (axis == Axis::Horizontal) ? Axis::Vertical : Axis::Horizontal;
	}
}