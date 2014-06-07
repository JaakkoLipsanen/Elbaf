#pragma once
class IModule
{
public:
	IModule() = default; // Game& in the constructor? 
	virtual ~IModule() = default;

	virtual void Initialize() = 0;
	virtual void Terminate() = 0;

	virtual void BeginFrame() { }
	virtual void Update() { }
	virtual void EndFrame() { }

	virtual void OnClosing() { }
};