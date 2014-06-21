#pragma once
#include <Core\IGameWindow.h>

struct GLFWwindow;
namespace OGL
{
	class GameWindow : public IGameWindow
	{
	public:
		GameWindow() = default;
		virtual ~GameWindow() override = default;

		virtual void SetTitle(const std::string& title) override;
		virtual bool IsOpen() const override;
		virtual void* GetInternalHandle() const override; // returns internal window handle. In OpenGL/GLFW, it should return GLFWwindow*
		virtual bool IsExiting() const override;
		// virtual void SetResolution(const Size& newSize) = 0; // this doesn't belong here. "SetSize" would
		// void SetPosition(const Vector2i& position) = 0; ?
		
		//not exposed by IGameWindow
		void Open(const Size& size, const std::string& title, bool fullScreen);
		void Terminate(); 
		GLFWwindow* GetGLFWwindow() const;

	private:
		GLFWwindow* _window;
	};
}

#if !OPENGL
#error ("Error: This is an OpenGL-specific class and "OPENGL" preprocessor is not defined!")
#endif