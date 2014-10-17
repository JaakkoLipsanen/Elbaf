#pragma once
#include <Graphics/Font.h>
#include <Graphics/GraphicsContext.h>
#include <Core/Color.h>

enum class TextCorner
{
	BottomLeft,
	BottomRight,
	TopRight,
	TopLeft,
	Center,
};


// todo: 3D font rendering..?
class FontRenderer
{

public:
	explicit FontRenderer(GraphicsContext& graphicsContext);
	~FontRenderer();

	void DrawText2D(Font& font, const std::string& text, Vector2f position, Color color = Color::White, TextCorner originCorner = TextCorner::TopLeft);
	void DrawTextShaded2D(Font& font, const std::string& text, Vector2f position, Color backgroundColor = Color::Black, Color foregroundColor = Color::White, TextCorner originCorner = TextCorner::TopLeft);

private:

	class Data;
	std::unique_ptr<FontRenderer::Data> _pData;
};
