#pragma once
#include <Core\IModule.h>
#include <type_traits>

class IGameWindow;
class IEngine
{
public:
	IEngine();
	virtual ~IEngine() = default;

	template<typename TModule>
	TModule* GetModule()
	{
		static_assert(std::is_base_of<IModule, TModule>::value, "Type must inherit from IInputSystem!");
		return dynamic_cast<TModule*>(this->GetModuleInner(typeid(TModule)));
	}

	virtual IGameWindow& GetWindow() const = 0;
	static IEngine& GetInstance();

protected:
	virtual IModule* GetModuleInner(const type_info& typeInfo) const = 0;
};