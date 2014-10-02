#include <Math\Size.h>

#include <string>
#include <Diagnostics\Ensure.h>

Size::Size(int width, int height) : Width(width), Height(height)
{
	Ensure::True(width >= 0 && height >= 0);
}

float Size::GetAspectRatio() const
{
	return this->Width / float(this->Height);
}