#include <Graphics\ITexture.h>

Size ITexture2D::GetSize() const
{
	return Size(this->GetWidth(), this->GetHeight());
}