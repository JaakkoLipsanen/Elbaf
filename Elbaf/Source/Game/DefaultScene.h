#pragma once
#include <Core\Scene.h>

class DefaultScene : public Scene
{
public:
	DefaultScene();
	~DefaultScene();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Render() override;
};

