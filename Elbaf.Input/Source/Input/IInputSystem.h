#pragma once

class IInputSystem
{
public:
	virtual ~IInputSystem() = 0; // force IInputSystem to be abstract/non-instantiable

private:
	virtual void Initialize() { }
	virtual void BeginFrame() { }
	virtual void PreUpdate() { }
	virtual void EndFrame() { }
	virtual void OnClosing() { }
};

inline IInputSystem::~IInputSystem() = default;