#pragma once
#include <memory>
#include <Input\IInputProvider.h>

namespace GLFW
{
	class InputProvider : public IInputProvider
	{
	public:
		InputProvider();
		virtual ~InputProvider() override;

		virtual void BeginFrame() override;
		virtual void EndFrame() override;
		virtual void Terminate() override;

		virtual KeyboardState const& GetKeyboardState() const override;
		virtual KeyboardState const& GetPreviousKeyboardState() const override;
		virtual MouseState const& GetMouseState() const override;
		virtual MouseState const& GetPreviousMouseState() const override;

	private:
		class Impl;
		std::unique_ptr<Impl> _pImpl;
	};
}