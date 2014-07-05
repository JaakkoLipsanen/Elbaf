#pragma once

class Scene
{
public: 
	Scene();
	virtual ~Scene();

	// internal...? friend stuff or something? maybe private header base-class?
	void Initialize();
	void Terminate();

	void Update();
	void Render();

	// todo: GetGameObject, GetComponent etc etc?? or should they be in some inner class....?

protected:
	virtual void OnEntering() { }
	virtual void OnExiting() { }
	virtual void PreUpdate() { }
	virtual void PostUpdate() { }
	virtual void PreRender() { }
	virtual void PostRender() { }
};