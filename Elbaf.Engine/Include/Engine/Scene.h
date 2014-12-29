#pragma once

class Game;
class SceneModule;

// todo: intergrate CBES right into this class and expose the CBES API in here
// > alternatively, make a "CbesScene" or something similar?
class Scene
{
	friend class SceneModule;

public: 
	Scene();
	virtual ~Scene();

	// todo: GetGameObject, GetComponent etc etc?? or should they be in some inner class....?

protected:
	virtual void OnEntering() { }
	virtual void OnExiting() { }
	virtual void PreUpdate() { }
	virtual void PostUpdate() { }
	virtual void PreRender() { }
	virtual void PostRender() { }
	
	Game& GetGame();

private:
	
	// internal...? friend stuff or something? maybe private header base-class?
	void Initialize(Game& game, SceneModule& sceneModule);
	void Terminate();

	void Update();
	void Render();

	Game* _game;
};