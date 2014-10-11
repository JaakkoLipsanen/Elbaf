#pragma once
#include <memory>

#include <Graphics/Font.h>
#include <Graphics/IGraphicsContext.h>
#include <Math/Range.h>

class FontLoader
{
public:
	FontLoader();
	~FontLoader();

	std::unique_ptr<Font> LoadFont(IGraphicsContext& graphicsContext, const std::string& path, int fontSize, Range<char> characterRange = Range<char>(32, 122), int dpi = 0);

private:
	class Impl;
	std::unique_ptr<FontLoader::Impl> _pImpl;
};