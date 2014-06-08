#pragma once
#include <string>
#include "Size.h"

enum class CursorType;
class IGameWindow
{
public:
	virtual ~IGameWindow() {}

	virtual void SetTitle(const std::string& title) = 0;
	virtual void SetCursorType(const CursorType& cursorType) = 0;
 // virtual void SetResolution(const Size& newSize) = 0; // this doesn't belong here. "SetSize" would
	// void SetPosition(const Vector2i& position) = 0; ?
	virtual bool IsOpen() const = 0;
	virtual bool IsExiting() const = 0;

	virtual void* GetInternalHandle() const = 0; // returns internal window handle. In OpenGL/GLFW, it should return GLFWwindow*

	/*
	static const std::string& DefaultTitle;
	static const Size& DefaultSize;
	static const bool& IsFullscreenByDefault;
	*/
};

/*
const std::string& IGameWindow::DefaultTitle = "Game";
const Size& IGameWindow::DefaultSize = Size(1280, 720);
const bool& IGameWindow::IsFullscreenByDefault = false;
*/