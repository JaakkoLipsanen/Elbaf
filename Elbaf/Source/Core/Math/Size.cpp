#include "Size.h"
#include "Diagnostics\Ensure.h"
#include <string>

Size::Size(int width, int height) : Width(width), Height(height)
{
	//Ensure::True(width >= 0 && height >= 0);
}

float Size::GetAspectRatio()
{
	return this->Width / float(this->Height);
}