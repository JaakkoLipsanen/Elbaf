#include "SizeF.h"
#include "Diagnostics\Ensure.h"
#include <Math\Vector.h>

SizeF::SizeF(float width, float height) : Width(width), Height(height)
{
	Ensure::True(width >= 0 && height >= 0);
}

float SizeF::GetAspectRatio()
{
	return this->Width / this->Height;
}