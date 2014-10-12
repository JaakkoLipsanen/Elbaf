#pragma once

enum class TextureFormat; // ImageFormat?
struct Image // I should probably address some things here, like compression or something...? i dont know :( !!
{
	const void* ImageData;
	const int Width;
	const int Height;
	const TextureFormat Format;

	Image(const void* imageData, int width, int height, const TextureFormat& textureFormat, bool freeImageDataWhenDestructed = true)
		: ImageData(imageData), Width(width), Height(height), Format(textureFormat), _freeImageDataWhenDestructed(freeImageDataWhenDestructed)
	{
	}

	Image& operator=(Image& other) = delete;
	~Image();

	// pretty eek
	Image Copy() const;

private:
	const bool _freeImageDataWhenDestructed;
};
