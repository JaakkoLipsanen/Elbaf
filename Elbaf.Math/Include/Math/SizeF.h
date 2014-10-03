#pragma once
#include <ostream>
#include <Math/Vector.h>

struct Rectangle;
struct SizeF
{
	const float Width;
	const float Height;

	SizeF(float width, float height);
	float GetAspectRatio();

	operator Vector2f() const;
	Vector2f ToVector2f() const;
	Rectangle ToRectangle() const;

	static const SizeF Empty;
};

inline std::ostream & operator << (std::ostream & stream, SizeF const& size)
{
	stream << "{ Width: " << size.Width << ", Height: " << size.Height << " }";
	return stream;
}