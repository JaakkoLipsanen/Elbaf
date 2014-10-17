#pragma once
#include <string>
#include <memory>
#include <Graphics/Image.h>
class Image;
class Texture2D;
class Font;
class GraphicsContext;
namespace Content
{
	std::unique_ptr<Image> LoadImage(const std::string& filePath);
	std::unique_ptr<Texture2D> LoadTexture(std::string const& filePath);
	std::unique_ptr<Font> LoadFont(GraphicsContext& graphicsContext, const std::string& fontPath, int fontSize);
}