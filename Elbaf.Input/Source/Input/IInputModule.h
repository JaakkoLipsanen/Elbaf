#pragma once
#include <Core\IModule.h>
#include <memory>
#include <Input\MouseState.h>

class type_info;
class IInputSystem;
struct KeyboardState;
class IInputModule : public IModule
{
public:
	explicit IInputModule(Engine& engine);

	virtual const KeyboardState& GetKeyboardState() = 0;
	virtual const KeyboardState& GetPreviousKeyboardState() = 0;
	virtual const MouseState& GetMouseState() = 0;
	virtual const MouseState& GetPreviousMouseState() = 0;

	template<typename TInputSystem>
	void AddInputSystem(std::unique_ptr<TInputSystem> inputSystem)
	{
		static_assert(std::is_base_of<IInputSystem, TInputSystem>::value, "Type must inherit from IInputSystem!");
		this->AddInputSystem(dynamic_cast<IInputSystem*>(inputSystem.release()), typeid(TInputSystem));
	}

	template<typename TInputSystem>
	void RemoveInputSystem(TInputSystem inputSystem)
	{
		static_assert(std::is_base_of<IInputSystem, TInputSystem>::value, "Type must inherit from IInputSystem!");
		this->RemoveInputSystem(typeid(TInputSystem));
	}

	template<typename TInputSystem>
	TInputSystem* GetInputSystem()
	{
		return dynamic_cast<TInputSystem*>(this->GetInputSystem(typeid(TInputSystem)));
	}

protected:
	virtual void AddInputSystem(IInputSystem* inputSystem, const type_info& typeInfo) = 0;
	virtual void RemoveInputSystem(const type_info& typeInfo) = 0;
	virtual IInputSystem* GetInputSystem(const type_info& typeInfo) = 0;
};