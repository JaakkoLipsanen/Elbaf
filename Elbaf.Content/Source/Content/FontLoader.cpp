#include <Content/FontLoader.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H // NOT NEEDED

#include <Diagnostics/Logger.h>
#include <Diagnostics/Ensure.h>
#include <Math/Range.h>
#include <vector>
#include <Graphics/Font.h>
#include <algorithm>
#include <Math/FlaiMath.h>
#include <Graphics/IGraphicsContext.h>
#include <Graphics/Image.h>
#include <Graphics/TextureFormat.h>
#include <iostream>
#include <fstream>

#include <chrono>

class FontLoader::Impl
{
public:
	FT_Library _library;
	Impl()
	{
		auto error = FT_Init_FreeType(&_library);
		Ensure::False(error, "FontLoader: Something failed while loading FreeType");
	}

	~Impl()
	{
		FT_Done_FreeType(_library);
	}

	void FindOptimalRectangles(std::vector<std::pair<char, Rectangle>>& characterSizes, std::map<char, Rectangle>& results, int* textureWidth, int* textureHeight)
	{
		// TODO: Better algorithm..
		typedef std::pair<char, Rectangle> CharRectangle;
		std::sort(characterSizes.begin(), characterSizes.end(), [](const CharRectangle& a, const CharRectangle& b)
		{
			return a.second.Height > b.second.Height;
		});

		int totalWidth = 0;
		for (int i = 0; i < characterSizes.size(); i++)
		{
			auto& current = characterSizes[i];
			results.insert(std::make_pair(current.first, Rectangle(totalWidth, 0, current.second.Width, current.second.Height)));

			totalWidth += current.second.Width + 1; // + 1 == padding
		}

		*textureHeight = FlaiMath::NextPowerOfTwo(characterSizes[0].second.Height);
		*textureWidth = FlaiMath::NextPowerOfTwo(totalWidth);
	}

	// todo: load font from memory? FreeType supports this also
	std::unique_ptr<Font> LoadFont(IGraphicsContext& graphicsContext, const std::string& path, int fontSize, Range<char> characterRange = Range<char>(32, 122), int dpi = 0, bool useKerning = false) // todo: "face_index" (third parameter in FT_New_Face)? Some font formats allow multiple fonts to be embedded in a single file
	{
		Ensure::True(_library != NULL, "FontLoader: Cannot load font because FreeType was not initialized correctly");
		
		FT_Face fontFace;
		auto error = FT_New_Face(_library, path.c_str(), 0, &fontFace);
		Ensure::False(error, "FontLoader: Something failed while loading font \"" + path + "\". Error code: " + std::to_string(error)); // TODO: NEEDLESS STRING CONCATS

		error = FT_Set_Char_Size(fontFace, 0, fontSize * 64, dpi, dpi);
		Ensure::False(error, "FontLoader: Something failed while loading font (set-char-size) \"" + path + "\". Error code: " + std::to_string(error)); // TODO: NEEDLESS STRING CONCATS

		std::map<char, int> charToGlyphIndex;
		std::map<char, FT_Glyph> glyphs;
		std::vector<std::pair<char, Rectangle>> charRectangleList;
		for (char character = characterRange.Min; character <= characterRange.Max; character++)
		{
			int glyphIndex = FT_Get_Char_Index(fontFace, character);
			charToGlyphIndex.insert(std::make_pair(character, glyphIndex));
			if (glyphIndex == 0)
			{
				// character is not included in the font
				continue;
			}

			error = FT_Load_Glyph(fontFace, glyphIndex, FT_LOAD_RENDER);
			Ensure::False(error, "FontLoader: Loading glyph failed");

			FT_Glyph glyph;
			error = FT_Get_Glyph(fontFace->glyph, &glyph);
			Ensure::False(error, "FontLoader: Extracting glyph failed");

			glyphs.insert(std::make_pair(character, glyph));
			
			FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyph;
			charRectangleList.push_back(std::make_pair(character, Rectangle(0, 0, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows)));

			// const Vector2f& advance, float offsetFromLeft, float offsetFromTop, const Rectangle& textureUv)
			//	Font::CharacterDefinition characterDefinition()
			//	characters.push_back(character);
		}

		// kerning
		std::map<std::tuple<char, char>, Vector2f> kerning;
		if (useKerning) // okay, dont use kerning always.. or, well, ever. FT_Get_Kerning is super slow and it has to be called really fuckin many times so GG. takes +5s on 64pt font
		{
			for (char character = characterRange.Min; character <= characterRange.Max; character++)
			{
				for (char other = characterRange.Min; other <= characterRange.Max; other++)
				{
					if (charToGlyphIndex[character] != 0 && charToGlyphIndex[other] != 0)
					{
						FT_Vector delta;

						auto error = FT_Get_Kerning(fontFace, charToGlyphIndex[character], charToGlyphIndex[other], FT_KERNING_DEFAULT, &delta);
						Ensure::False(error, "FontLoader: Kerning failed");
						if (delta.x != 0 || delta.y != 0)
						{
							kerning.insert(std::make_pair(std::make_tuple(character, other), Vector2f(delta.x / 64, delta.y / 64))); // delta == 0, 0 in case of error, so no need to check for error
						}
					}
				}
			}
		}

		int textureWidth;
		int textureHeight;
		std::map<char, Rectangle> uvCoordinates;
		this->FindOptimalRectangles(charRectangleList, uvCoordinates, &textureWidth, &textureHeight);

		std::map<char, Font::CharacterDefinition> characters;
		byte* buffer = new byte[textureWidth * textureHeight]();; // possible memory leak if the part before last line of this function throws an exception. But it shouldn't really..
		for (auto& pair : uvCoordinates)
		{
			char character = pair.first;
			Rectangle uv = pair.second;

			FT_BitmapGlyph glyph = (FT_BitmapGlyph)glyphs[character];
			Ensure::True(glyph->bitmap.width == uv.Width && glyph->bitmap.rows == uv.Height, "Values are out of sync?");
			
			FT_Vector origin = { 0, 0 };
			FT_Glyph_To_Bitmap(&glyphs[character], FT_RENDER_MODE_NORMAL, &origin, true);

		
			// blit the bitmap to the final buffer
			for (int y = 0; y < uv.Height; y++)
			{
				for (int x = 0; x < uv.Width; x++)
				{
					buffer[(uv.X + x) + (uv.Y + y) * textureWidth] = glyph->bitmap.buffer[x + y * uv.Width];
				}
			}

			characters.insert(std::make_pair(character, Font::CharacterDefinition(Vector2f(glyph->root.advance.x / 65536.0f, glyph->root.advance.y / 65536.0f), glyph->left, glyph->top, uv)));
			FT_Done_Glyph(glyphs[character]);
		}

		Logger::MessageStream << "W: " << textureWidth << ", H: " << textureHeight << "\n";
		std::string fontName = std::string(fontFace->family_name) + " " + fontFace->style_name;
		FT_Done_Face(fontFace);

		return std::unique_ptr<Font>(new Font(graphicsContext.CreateTexture2D(std::make_unique<Image>(buffer, textureWidth, textureHeight, TextureFormat::Red8)), characters, kerning, fontName, fontSize));
	}
};

FontLoader::FontLoader() : _pImpl(new Impl) { }
FontLoader::~FontLoader() = default;

std::unique_ptr<Font> FontLoader::LoadFont(IGraphicsContext& graphicsContext, std::string const& path, int fontSize, Range<char> characterRange, int dpi)
{
	return _pImpl->LoadFont(graphicsContext, path, fontSize, characterRange, dpi);
}