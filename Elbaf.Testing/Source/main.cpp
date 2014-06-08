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
#include <Input\IInputSystem.h>

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
	}
};

class MyInput : public IInputSystem { };
int main()
{
	MyGame game;
	game.Run();

	IInputModule* module = nullptr;

	MyInput input;
	module->AddInputSystem(std::unique_ptr<MyInput>(new MyInput));
	/*Engine engine;
	engine.SetClearColor(Color::Red);
	engine.GetWindow().SetTitle("My Game");
	engine.GetGraphicsDevice().SetResolution(1920, 1080); */

	return 1;
}