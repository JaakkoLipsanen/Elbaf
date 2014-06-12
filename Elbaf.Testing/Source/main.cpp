#include <iostream>
#include <Math\Fundamental.h>
#include <Math\Vector.h>
#include <Core\IGameWindow.h>
#include <Core\Color.h>
#include <Engine\Game.h>
#include <Engine\Platform.h>
#include <Graphics\IGraphicsDevice.h>
#include <Core\CursorType.h>
#include <Input\IInputModule.h>
#include <Graphics\IGraphicsModule.h>
#include <type_traits>
#include <Input\KeyboardState.h>
#include <Core\Diagnostics\Logger.h>
#include <Input\Input.h>

class MyGame : public Game
{
public:
	virtual std::unique_ptr<Scene> CreateDefaultScene() override
	{
		return std::unique_ptr<Scene>(nullptr);
	}

	virtual void Initialize() override
	{
		this->GetWindow()->SetCursorType(CursorType::Hidden);
	}

	virtual void PreRender() override
	{
		this->GetGraphicsDevice()->Clear(Color::RoyalBlue);
		if (Input::IsMouseButtonPressed(MouseButton::Left))
		{
			this->GetGraphicsDevice()->Clear(Color::Red);
		}

		if (Input::GetScrollWheelDelta() != 0)
		{
			Logger::LogMessage(Input::GetScrollWheelDelta());
		}
	}
};

int main()
{
	MyGame game;
	game.Run();

	/*Engine engine;
	engine.SetClearColor(Color::Red);
	engine.GetWindow().SetTitle("My Game");
	engine.GetGraphicsDevice().SetResolution(1920, 1080); */

	return 1;
}