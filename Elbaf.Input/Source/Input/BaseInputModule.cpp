#include "BaseInputModule.h"
#include <map>
#include <Core\Diagnostics\Logger.h>
#include <Input\IInputSystem.h>

struct BaseInputModule::Impl
{
//	std::map<const int&, IInputSystem*> InputSystems;
};

BaseInputModule::BaseInputModule(Engine& engine) : IInputModule(engine)
{
}

BaseInputModule::~BaseInputModule() = default;

void BaseInputModule::AddInputSystem(IInputSystem* inputSystem, type_info const& typeInfo)
{
//	if (_pImpl->InputSystems.count(typeInfo) != 0)
	{
		Logger::LogError("Input Module already contains an InputSystem (" + std::string(typeInfo.name()) + ")");
		return;
	}

	//_pImpl->InputSystems.insert(std::pair<const type_info&, IInputSystem*>(typeInfo, inputSystem));
}

void BaseInputModule::RemoveInputSystem(type_info const& typeInfo)
{
//	if (_pImpl->InputSystems.count(typeInfo) == 0)
	{
		Logger::LogError("Input Module doesn't contain an InputSystem (" + std::string(typeInfo.name()) + ")");
		return;
	}

//	_pImpl->InputSystems.erase(typeInfo);
}

IInputSystem* BaseInputModule::GetInputSystem(type_info const& typeInfo)
{
//	auto x = _pImpl->InputSystems.find(typeInfo);
//	if (x == _pImpl->InputSystems.end())
	{
		return nullptr;
	}
	
	//return x->second;
}