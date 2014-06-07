#pragma once
enum class ClearOptions : int
{
	Color = 0,// = GL_COLOR_BUFFER_BIT,
	Depth = 1,// = GL_DEPTH_BUFFER_BIT,
	Stencil = 2,// = GL_STENCIL_BUFFER_BIT,
	All = 3, // Color | Depth | Stencil
};