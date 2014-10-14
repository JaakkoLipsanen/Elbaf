#include <Math\Size.h>

#include <string>
#include <Diagnostics\Ensure.h>

Size::Size(Vector2i const& vector)
	: Width(vector.X), Height(vector.Y)
{
}

Size::operator Vector2i() const
{
	return Vector2i(this->Width, this->Height);
}


Size::Size(int width, int height) : Width(width), Height(height)
{
	Ensure::True(width >= 0 && height >= 0);
}

float Size::GetAspectRatio() const
{
	return this->Width / float(this->Height);
}