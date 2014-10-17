#pragma once
#include <Math/Rectangle.h>
#include <memory>
#include <Graphics/Texture.h>
#include <map>
#include <Math/SizeF.h>

class Font
{
public:
	struct CharacterDefinition
	{
		const Vector2f Advance;
		const float OffsetFromLeft;
		const float OffsetFromTop;
		const Rectangle TextureUV;

		CharacterDefinition(const Vector2f& advance, float offsetFromLeft, float offsetFromTop, const Rectangle& textureUv)
			: Advance(advance), OffsetFromLeft(offsetFromLeft), OffsetFromTop(offsetFromTop), TextureUV(textureUv)
		{
		}
	};

	Font(std::unique_ptr<Texture2D> texture, std::map<char, CharacterDefinition> characters, std::map<std::tuple<char, char>, Vector2f> kerningData, const std::string& fontName = "", int fontSize = -1);
	~Font();

	Texture2D& GetTexture();
	Vector2f GetKerning(char previous, char next) const;
	const CharacterDefinition& GetCharacterDefinition(char character) const;

	bool ContainsCharacter(char character) const;
	const std::string& GetName() const; // returns empty string if not specified
	int GetFontSize() const; // return -1 if size is not specified

	SizeF MeasureText(const std::string& text) const;

private:
	class Impl;
	std::unique_ptr<Font::Impl> _pImpl;
};