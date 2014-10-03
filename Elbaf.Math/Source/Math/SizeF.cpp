#include <Math\SizeF.h>

#include <Diagnostics\Ensure.h>
#include <Math\Vector.h>
#include <Math/Rectangle.h>

const SizeF SizeF::Empty = SizeF(0, 0);
SizeF::SizeF(float width, float height) : Width(width), Height(height)
{
	Ensure::True(width >= 0 && height >= 0);
}

float SizeF::GetAspectRatio()
{
	return this->Width / this->Height;
}

Vector2f SizeF::ToVector2f() const
{
	return *this;
}

Rectangle SizeF::ToRectangle() const
{
	return Rectangle(0, 0, this->Width, this->Height);
}

SizeF::operator Vector2f() const
{
	return Vector2f(this->Width, this->Height);
}