#pragma once

enum class TextureFormat; // ImageFormat?
struct Image // I really should probably address some things here, like compression..?
{
	const void* ImageData;
	const int Width;
	const int Height;
	const TextureFormat Format;

	Image(void* imageData, int width, int height, TextureFormat textureFormat)
		: ImageData(imageData), Width(width), Height(height), Format(textureFormat)
	{
	}

	Image& operator=(Image& other) = delete;
	~Image();
};