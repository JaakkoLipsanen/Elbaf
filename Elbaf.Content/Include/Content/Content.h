#pragma once
#include <string>
#include <memory>
#include <Graphics/Image.h>
class Image;
class ITexture2D;
class Font;
class IGraphicsContext;
namespace Content
{
	std::unique_ptr<Image> LoadImage(const std::string& filePath);
	std::unique_ptr<ITexture2D> LoadTexture(std::string const& filePath);
	std::unique_ptr<Font> LoadFont(IGraphicsContext& graphicsContext, const std::string& fontPath, int fontSize);
}