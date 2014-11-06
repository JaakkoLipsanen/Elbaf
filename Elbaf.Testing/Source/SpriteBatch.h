#pragma once
#include <Math/Vector.h>
#include <Core/Color.h>
#include <memory>

class Texture2D;
class GraphicsContext;

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

private:
	class Impl;
	std::unique_ptr<Impl> _pImpl;
};