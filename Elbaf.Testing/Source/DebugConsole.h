#pragma once
#include <memory>

class Game;

class DebugConsole
{
public:
	explicit DebugConsole(Game& game);
	~DebugConsole();

	void LoadContent();
	void Update();
	void Render();

private:
	class Impl;
	std::unique_ptr<Impl> _pImpl;
};