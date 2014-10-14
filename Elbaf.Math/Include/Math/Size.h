#pragma once
#include <ostream>
#include <Math/Fundamental.h>
#include <Math/Vector.h>

struct Size
{
	int Width;
	int Height;

	Size(int width, int height);
	Size(const Vector2i& vector);
	float GetAspectRatio() const;

	operator Vector2i() const;
};

inline std::ostream & operator << (std::ostream & stream, Size const& size)
{
	stream << "{ Width: " << size.Width << ", Height: " << size.Height << " }";
	return stream;
}