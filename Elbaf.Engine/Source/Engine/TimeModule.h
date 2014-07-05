#pragma once
#include <Core\IModule.h>
#include <memory>

class TimeModule final : public IModule
{
public:
	explicit TimeModule(IEngine& engine);
	virtual ~TimeModule() = default;

	float GetDeltaTime() const;
	float GetTotalTime() const;
	double GetSystemTime() const;

	virtual void Initialize() override;
	virtual void Terminate() override;
	virtual void BeginFrame() override;

private:
	double _deltaTime;
	double _totalTime;

	double _previousTime = 0.0;
	double _maxDelta = 0.1; // 10fps. todo: make this changeable?
};