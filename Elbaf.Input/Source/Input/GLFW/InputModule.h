#pragma once
#include "..\IInputModule.h"
#include <Input\KeyCode.h>
#include <Input\BaseInputModule.h>

namespace GLFW
{
	class InputModule : public BaseInputModule
	{
	public:
		InputModule(Engine& engine);
		virtual const KeyboardState& GetKeyboardState() override;
		virtual const KeyboardState& GetPreviousKeyboardState() override;

		virtual void BeginFrame() override;
		virtual void EndFrame() override;

	private:
		struct Impl;
		std::unique_ptr<Impl> _pImpl;
	};
}