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

class MyGame : public Game
{
	std::unique_ptr<Font> _font;
	std::unique_ptr<SpriteBatch> _batch;
	std::unique_ptr<Texture2D> _blankPixel;

protected:
	void SetupWindow(WindowDescription& description) override
	{
		description.Resolution = Size(1920, 1080);
	}

public:
	MyGame() : Game("Test") { }

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