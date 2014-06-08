#pragma once
#include <Core\IModule.h>
#include <type_traits>

class Engine
{
public:
	virtual ~Engine() = default;

	template<typename TModule>
	TModule GetModule()
	{
		static_assert(std::is_base_of<IModule, TModule>::value, "Type must inherit from IInputSystem!");
		return this->GetModule(typeid(TModule));
	}

protected:
	virtual IModule* GetModule(type_info typeInfo) const = 0;
};