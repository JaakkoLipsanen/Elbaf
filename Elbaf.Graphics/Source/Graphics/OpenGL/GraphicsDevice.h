#pragma once
#include <Graphics\IGraphicsDevice.h>
#include <memory>

struct Size;
struct WindowDescription;

namespace OGL
{
	class GraphicsDevice : public IGraphicsDevice
	{
	public:
		GraphicsDevice();
		virtual ~GraphicsDevice() override;

		virtual IGameWindow& GetGameWindow() override;
		virtual GraphicsContext& GetContext() override;
		virtual RendererAPI GetRendererAPI() const override;
		virtual void OpenWindow(const WindowDescription& windowDescription) override;
		virtual void RunMessagePump() override;

		virtual void BeginFrame() override;
		virtual void EndFrame() override;
		virtual void Terminate() override;

	private:
		class Impl;
		std::unique_ptr<Impl> _pImpl;
	};
}