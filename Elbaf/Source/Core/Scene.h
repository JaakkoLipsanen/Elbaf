#pragma once
class Game;
class GraphicsDevice;
class SceneManager;

class Scene
{
	friend SceneManager;

protected:
	Game& _game;
	GraphicsDevice& _graphicsDevice;

	virtual void Initialize() = 0;
	virtual void Update() { }
	virtual void Render() { }
	virtual void OnExiting() { }

public:
	Scene();
	virtual ~Scene() = default;
};

