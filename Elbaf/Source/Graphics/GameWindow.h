#pragma once
#include <memory>
#include "Graphics.h"
#include <Diagnostics\Logger.h>
#include <Core\Math\Size.h>

class GraphicsDevice;
class InputManager;
class GameWindow
{
	// these require access to GLFWwindow
	friend GraphicsDevice;
	friend InputManager;

	struct WindowDeleter {
		void operator ()(GLFWwindow *window) {
			// do nothing. at the moment, only way the window is destroyed is when GLFW is terminating (= exiting application). In that case, glfwTerminate will destroy the window.
			// destroying it here would try to destroy it twice
		}
	};

	const std::unique_ptr<GLFWwindow, WindowDeleter> _window;
	void SetWindowSize(const Size& size);
	void SwapBuffers();

public:
	explicit GameWindow(Size size, std::string title = "Window", bool isFullScreen = false);
	~GameWindow();

	// disallow copying
	GameWindow(const GameWindow&) = delete;
	GameWindow &operator=(const GameWindow&) = delete;

	Size GetWindowSize() const;

	std::string GetTitle() const;
	void SetTitle(const std::string& title);

	bool GetShouldClose() const;
	void SetShouldClose(bool value);

	bool IsCreated() const;
	void MakeContextCurrent();
};

