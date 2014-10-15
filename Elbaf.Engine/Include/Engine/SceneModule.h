#pragma once

#include <Core\IModule.h>
#include <memory>

class Scene;
class Game;

// should this be a private header? maybe make ISceneManager public or something?
class SceneModule : public IModule
{
public:
	SceneModule(Game& game);
	virtual ~SceneModule() override;

	virtual void Initialize() override;
	virtual void Terminate() override;
	virtual void Update() override;

	// todo: should rendering happen in SceneModule::Update? that would be a "more correct" approach maybe...? 
	void Render();
	void LoadScene(std::unique_ptr<Scene> scene);
	Scene& GetCurrentScene();

private:
	std::unique_ptr<Scene> _currentScene;
};