#pragma once
#include "IInputModule.h"
#include "IInputSystem.h"

class BaseInputModule : public IInputModule
{
public:
	virtual ~BaseInputModule() = 0;
protected:
	BaseInputModule(Engine& engine);
	virtual void AddInputSystem(IInputSystem* inputSystem, const type_info& typeInfo) override;
	virtual void RemoveInputSystem(const type_info& typeInfo) override;
	virtual IInputSystem* GetInputSystem(const type_info& typeInfo) override;

private:
	struct Impl;
	std::unique_ptr<Impl> _pImpl;
};