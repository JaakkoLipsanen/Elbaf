#pragma once
#include <ostream>

struct SizeF
{
	const float Width;
	const float Height;

	SizeF(float width, float height);
	float GetAspectRatio();
};

inline std::ostream & operator << (std::ostream & stream, SizeF const& size)
{
	stream << "{ Width: " << size.Width << ", Height: " << size.Height << " }";
	return stream;
}