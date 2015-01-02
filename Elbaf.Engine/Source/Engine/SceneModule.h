#pragma once

#include <Core\IModule.h>
#include <Engine/ISceneManager.h>
#include <memory>

class Scene;
class Game;

// should this be a private header? maybe make ISceneManager public or something?
class SceneModule : public IModule, public ISceneManager
{
public:
	explicit SceneModule(Game& game);
	virtual ~SceneModule() override;

	virtual void Initialize() override;
	virtual void Terminate() override;
	virtual void Update() override;

	// todo: should rendering happen in SceneModule::Update? that would be a "more correct" approach maybe...? 
	void Render();
	virtual void LoadScene(std::unique_ptr<Scene> scene) override;
	Scene& GetCurrentScene();

private:
	void LoadNextScene();
	std::unique_ptr<Scene> _currentScene;
	std::unique_ptr<Scene> _nextSceneToLoad;
};