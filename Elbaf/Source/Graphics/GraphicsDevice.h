#pragma once
#include "Color.h"
#include <Core\Math\Size.h>

class Game;
enum class ClearOptions : int
{
	Color = 0,// = GL_COLOR_BUFFER_BIT,
	Depth = 1,// = GL_DEPTH_BUFFER_BIT,
	Stencil = 2,// = GL_STENCIL_BUFFER_BIT,
	All = 3, // Color | Depth | Stencil
};

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

