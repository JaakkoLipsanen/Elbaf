#pragma once
#include <Core\IModule.h>
#include <memory>

// for fucks sake. cant name this "TimeModule" because then I can't have a field named "TimeModule" in the Game.cpp. for fucks sake. I could make ITimeModule and just make this inherit from it but... fuck...
class TimeModule final : public IModule
{
public:
	explicit TimeModule(IEngine& engine);

	float GetDeltaTime() const;
	float GetTotalTime() const;

	virtual void Initialize() override;
	virtual void Terminate() override;
	virtual void BeginFrame() override;

private:
	double _deltaTime;
	double _totalTime;

	double _previousTime = 0.0;
	double _maxDelta = 0.1; // 10fps. todo: make this changeable?
};