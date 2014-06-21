#pragma once

class IEngine;
class IModule
{
public:
	explicit IModule(IEngine& engine); // Game& in the constructor? 
	virtual ~IModule() = default;
	IModule& operator=(const IModule& other) = delete; // to not show an warning

	virtual void Initialize() = 0;
	virtual void Terminate() = 0;

	virtual void BeginFrame() { }
	virtual void Update() { }
	virtual void EndFrame() { }

	virtual void OnClosing() { }

protected:
	IEngine& _engine;
};