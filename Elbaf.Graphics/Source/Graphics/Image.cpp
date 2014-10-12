#include <Graphics\Image.h>
#include <cstdlib>
#include <Diagnostics/Logger.h>
#include <Graphics/TextureFormat.h>
#include <Core/Color.h>

Image::~Image()
{
	// meh. casting const pointer to non-const pointer. but whatever..
	if (_freeImageDataWhenDestructed)
	{
		free(const_cast<void*>(this->ImageData));
	}
}

Image Image::Copy() const
{
	int dataLength = this->Width * this->Height * TextureFormatHelper::GetPixelSizeInBytes(this->Format);
	void* newData = malloc(dataLength);
	memcpy(newData, this->ImageData, dataLength);

	return Image(newData, this->Width, this->Height, this->Format, true); // should freeImageDataWhenDestructed be always true..?
}