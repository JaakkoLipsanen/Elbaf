#pragma once
#include <Math/Vector.h>
#include <Core/Color.h>
#include <memory>

struct RectangleF;
struct Rectangle;
class Font;
class Texture2D;
class GraphicsContext;

enum class TextCorner
{
	BottomLeft,
	BottomRight,
	TopRight,
	TopLeft,
	Center,
};

class SpriteBatch
{
public:
	explicit SpriteBatch(GraphicsContext& graphicsContext);
	~SpriteBatch();

	void Begin();
	void End();

	void Draw(Texture2D& texture, Vector2f position, Color color = Color::White);
	void Draw(Texture2D& texture, Vector2f position, Color color, float rotation, Vector2f scale);
	void Draw(Texture2D& texture, Vector2f position, Color color, float rotation, Vector2f scale, Vector2f origin);
	void Draw(Texture2D& texture, Vector2f position, Color color, float rotation, Vector2f scale, Vector2f origin, Rectangle sourceRectangle);

	void Draw(Texture2D& texture, RectangleF destinationRectangle, Color color);
	void Draw(Texture2D& texture, RectangleF destinationRectangle, Color color, Rectangle sourceRectangle);

	void DrawText(Font& font, const std::string& text, Vector2f position, Color color = Color::White, TextCorner origin = TextCorner::TopLeft);

private:
	class Impl;
	std::unique_ptr<Impl> _pImpl;
};