#pragma once
#include <string>
#include "Size.h"

class IGameWindow
{
public:
	virtual ~IGameWindow() {}

	virtual void SetTitle(const std::string& title) = 0;
	virtual bool IsOpen() const = 0;
	virtual bool IsExiting() const = 0;

	virtual void* GetInternalHandle() const = 0; // returns internal window handle. In OpenGL/GLFW, it should return GLFWwindow*
	// void SetPosition(const Vector2i& position) = 0; ?
};