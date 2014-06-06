#pragma once
#include <memory>
#include <Core\Scene.h>

class Game;
class SceneManager
{
	friend Game;
	std::unique_ptr<Scene> _currentScene;
	SceneManager(); // private constructor, only Game can access

protected:
	void Update();
	void Render();
public:
	~SceneManager();

	void ChangeScene(std::unique_ptr<Scene> newScene);
};

