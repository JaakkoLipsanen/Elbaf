#pragma once
#include "Color.h"
#include <Core\Math\Size.h>

class Game;


class GraphicsDevice
{
	friend Game;
	const Game& _game;

	void Initialize();
	void Terminate();

public:
	GraphicsDevice(const Game& game);
	~GraphicsDevice();

	void Clear(const Color& color);
	void Clear(ClearOptions clearOptions, const Color& color, float depth = 0, int stencil = 0);

	void SetResolution(Size size);
	void SwapBuffers();
};

