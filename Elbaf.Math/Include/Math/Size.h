#pragma once
#include <ostream>

struct Size
{
	int Width;
	int Height;

	Size(int width, int height);
	float GetAspectRatio() const;

	Size& operator=(const Size&) = default;
};

inline std::ostream & operator << (std::ostream & stream, Size const& size)
{
	stream << "{ Width: " << size.Width << ", Height: " << size.Height << " }";
	return stream;
}