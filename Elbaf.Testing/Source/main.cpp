#include <Engine\Game.h>
#include <Diagnostics\Logger.h>
#include <Engine\Screen.h>
#include <Input\Mouse.h>
#include <Graphics/OpenGL/OGL.h>
#include <Graphics/Font.h>
#include <Graphics/FontRenderer.h>
#include "TestScene.h"
#include <Core/CursorVisibility.h>
#include <Content/Content.h>

enum class DepthBufferFormat
{
	None,
	Depth16,
	Depth24Stencil8,
	Depth32,
};

class RenderTarget
{
public:
	static std::unique_ptr<RenderTarget> Create(DepthBufferFormat format)
	{
		GLuint frameBufferID;
		glGenFramebuffers(1, &frameBufferID);

		// Modifies global frame buffer. cache old and set it back?
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	}

private:
	GLuint _framebufferID;
	GLuint _colorTextureID;
	GLuint _depthTextureID;
};

#include <Core/WindowDescription.h>
class MyGame : public Game
{
	std::unique_ptr<Font> _font;
	std::unique_ptr<FontRenderer> _fontRenderer;

protected:
	void SetupWindow(WindowDescription& description) override
	{
		description.Resolution = Size(1920, 1080);
	}

public:
	virtual std::unique_ptr<Scene> CreateDefaultScene() override
	{
		return std::make_unique<TestScene>();
	}

	virtual void Initialize() override
	{
		// Initialize mouse settings
		Mouse::SetCursorVisibility(CursorVisibility::Disabled);
		Mouse::SetPosition({ Screen::GetWidth() / 2, Screen::GetHeight() / 2 });

		_font = Content::LoadFont(this->GetGraphicsContext(), "F:\\Users\\Jaakko\\Desktop\\ArvoRegular.ttf", 32);
		_fontRenderer.reset(new FontRenderer(this->GetGraphicsContext()));
	}

	virtual void PostRender() override
	{
		_fontRenderer->DrawText2D(*_font.get(), "ELBAF", Vector2f::One * 8, Color::White * 0.5f);
	}
};

int main()
{
	MyGame game;
	game.Run();

	return 1;
}