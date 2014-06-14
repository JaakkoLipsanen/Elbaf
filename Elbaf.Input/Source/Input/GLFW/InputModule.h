#pragma once
#include "..\IInputModule.h"
#include <Input\KeyCode.h>

namespace GLFW
{
	// okay fuck, it was a mistake making this use PIMPL. I really over-engineered this whole Input module.....
	class InputModule : public IInputModule
	{
	public:
		explicit InputModule(IEngine& engine);
		virtual const KeyboardState& GetKeyboardState() override;
		virtual const KeyboardState& GetPreviousKeyboardState() override;
		virtual const MouseState& GetMouseState() override;
		virtual const MouseState& GetPreviousMouseState() override;

		virtual void BeginFrame() override;
		virtual void EndFrame() override;

		virtual void Initialize() override;
		virtual void Terminate() override;

	private:
		struct Impl;
		std::unique_ptr<Impl> _pImpl;
	};
}