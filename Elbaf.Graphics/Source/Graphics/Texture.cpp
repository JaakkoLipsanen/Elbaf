#include <Graphics\Texture.h>

Size Texture2D::GetSize() const
{
	return Size(this->GetWidth(), this->GetHeight());
}