#pragma once
#include "Core\Game.h"

class TestGame : public Game
{
public:
	TestGame();
	~TestGame();

	virtual std::unique_ptr<Scene> CreateDefaultScene() override;
};

