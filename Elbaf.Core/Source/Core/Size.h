#pragma once
#include "Event.h"
#include <ostream>

struct Size
{
	const int Width;
	const int Height;

	Size(int width, int height);
	float GetAspectRatio();

	Size& operator=(const Size&) = delete;
};

inline std::ostream & operator << (std::ostream & stream, Size const& size)
{
	stream << "{ Width: " << size.Width << ", Height: " << size.Height << " }";
	return stream;
}