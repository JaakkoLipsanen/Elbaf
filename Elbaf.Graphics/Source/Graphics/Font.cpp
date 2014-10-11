#include <Graphics/Font.h>
#include <Graphics/ITexture.h>
#include <Math/FlaiMath.h>

class Font::Impl
{
public:
	std::string FontName; // can be empty
	int FontSize; // can be -1

	std::unique_ptr<ITexture2D> FontTexture;
	std::map<char, CharacterDefinition> Characters; // set vs vector?
	std::map<std::tuple<char, char>, Vector2f> Kerning;

	Impl(std::unique_ptr<ITexture2D> texture, std::map<char, CharacterDefinition> characters, std::map<std::tuple<char, char>, Vector2f> kerningData, const std::string& fontName = "", int fontSize = -1)
		: FontTexture(texture.release()), Characters(characters), Kerning(kerningData), FontName(fontName), FontSize(fontSize)
	{
		
	}
};

Font::Font(std::unique_ptr<ITexture2D> texture, std::map<char, CharacterDefinition> characters, std::map<std::tuple<char, char>, Vector2f> kerningData, std::string const& fontName, int fontSize)
	: _pImpl(new Font::Impl(std::move(texture), characters, kerningData, fontName, fontSize))
{
}

Font::~Font() = default;

ITexture2D& Font::GetTexture()
{
	return *_pImpl->FontTexture.get();
}

Vector2f Font::GetKerning(char previous, char next) const
{
	auto iterator = _pImpl->Kerning.find(std::tuple<char, char>(previous, next));
	if (iterator == _pImpl->Kerning.end())
	{
		return Vector2f::Zero;
	}

	return iterator->second;
}

Font::CharacterDefinition const& Font::GetCharacterDefinition(char character) const
{
	auto iterator = _pImpl->Characters.find(character);
	if (iterator == _pImpl->Characters.end())
	{
		throw std::exception("Character does not exist");
	}

	return iterator->second;
}

bool Font::ContainsCharacter(char character) const
{
	auto iterator = _pImpl->Characters.find(character);
	return iterator != _pImpl->Characters.end();
}

std::string const& Font::GetName() const
{
	return _pImpl->FontName;
}

int Font::GetFontSize() const
{
	return _pImpl->FontSize;
}

SizeF Font::MeasureText(std::string const& text) const
{
	float width = 0;
	float maxHeight = 0;
	for (int i = 0; i < text.size(); i++)
	{
		if (i != 0)
		{
			width += this->GetKerning(text[i - 1], text[i]).X;
		}

		auto& characterDefinition = this->GetCharacterDefinition(text[i]);
		width += characterDefinition.Advance.X;
		maxHeight = FlaiMath::Max(maxHeight, float(characterDefinition.TextureUV.Height)); // TODO: characterDefinition.OffsetFromTop is not being accounted for ATM!!
	}

	return SizeF(width, maxHeight);
}