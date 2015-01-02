#pragma once
#include <memory>

class Scene;
class ISceneManager
{
public:
	virtual ~ISceneManager() { }
	virtual void LoadScene(std::unique_ptr<Scene> scene) = 0;
};