#pragma once
#include <Core\IGameWindow.h>

struct WindowDescription;
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
		
		virtual void SetPosition(Vector2i position) override;
		
		//not exposed by IGameWindow
		void Open(const WindowDescription& description);
		void Terminate(); 
		GLFWwindow* GetGLFWwindow() const;

	private:
		GLFWwindow* _window;
	};
}

#if !OPENGL
#error ("Error: This is an OpenGL-specific class and "OPENGL" preprocessor is not defined!")
#endif