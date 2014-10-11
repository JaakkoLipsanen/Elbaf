#pragma once
#include <memory>
#include <string>
#include <Graphics\Image.h>
#include <Graphics/Font.h>
#include <Graphics/IGraphicsContext.h>

namespace Content
{
	std::unique_ptr<Image> LoadImage(const std::string& filePath);
	std::unique_ptr<Font> LoadFont(IGraphicsContext& graphicsContext, const std::string& fontPath, int fontSize);
}