#pragma once
#include <memory>
#include <Graphics\IGraphicsModule.h>

namespace OGL
{
	// todo: why does this have to be outside of the class (and can't be in "private "part)? if this not, then GetGraphicsDevice-implementation gives an error (can't cast from GraphicsDevice* to IGraphicsDevice*)
	class GraphicsModule : public IGraphicsModule
	{
	public:
		GraphicsModule();
		virtual void Initialize() override;
		virtual void Terminate() override;
		virtual void EndFrame() override;
		virtual IGraphicsDevice* GetGraphicsDevice() const;
		virtual IGameWindow* GetGameWindow() const;
		virtual void OpenWindow(const Size& size = Size(1280, 720), const std::string& title = "Game", bool isFullScreen = false);

	private:
		struct GraphicsModuleImpl;
		std::unique_ptr<GraphicsModuleImpl> _pImpl;
	};
}

#if !OPENGL
#error ("Error: This is an OpenGL-specific class and "OPENGL" preprocessor is not defined!")
#endif