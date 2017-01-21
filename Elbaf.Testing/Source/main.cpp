#include <Engine\Game.h>
#include <Engine\Screen.h>
#include <Input\Mouse.h>
#include <Graphics/Font.h>
#include "TestScene.h"
#include <Core/CursorVisibility.h>
#include <Content/Content.h>
#include <Core/WindowDescription.h>
#include <Graphics/SpriteBatch.h>
#include <Graphics/TextureHelper.h>

#include <Core/IGameWindow.h>

class MyGame : public Game
{
	std::unique_ptr<Font> _font;
	std::unique_ptr<SpriteBatch> _batch;
	std::unique_ptr<Texture2D> _blankPixel;

protected:
	void SetupWindow(WindowDescription& description) override
	{
		description.Resolution = Size(1280, 800);
		description.HasBorders = false;
	}

public:
	MyGame() : Game("Test") { }

	virtual std::unique_ptr<Scene> CreateDefaultScene() override
	{
		return std::make_unique<TestScene>();
	}

	virtual void Initialize() override
	{
		this->GetWindow().SetPosition(Vector2i(320, 160));

		// Initialize mouse settings
		Mouse::SetCursorVisibility(CursorVisibility::Disabled);
		Mouse::SetPosition({ Screen::GetWidth() / 2, Screen::GetHeight() / 2 });

		_font = Content::LoadFont(this->GetGraphicsContext(), "Fonts/ArvoRegular.ttf", 32);

		_batch.reset(new SpriteBatch(this->GetGraphicsContext()));
		_blankPixel = TextureHelper::CreateBlankTexture(this->GetGraphicsContext());
	}

	virtual void PostRender() override
	{
	}
};

int main()
{
	MyGame game;
	game.Run();

	return 1;
}