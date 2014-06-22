#include <Engine\TimeModule.h>
#include <algorithm>

static double GetCurrentTime();
TimeModule::TimeModule(IEngine& engine): IModule(engine) { }

float TimeModule::GetDeltaTime() const
{
	return static_cast<float>(_deltaTime);
}

float TimeModule::GetTotalTime() const
{
	return static_cast<float>(_totalTime);
}

void TimeModule::BeginFrame()
{
	double currentTime = GetCurrentTime();
	double delta = std::min(currentTime - _previousTime, _maxDelta);
	_deltaTime = delta;
	_totalTime += delta;

	_previousTime = currentTime;
}

void TimeModule::Initialize()
{
	_previousTime = GetCurrentTime();
	_deltaTime = 0.0;
	_totalTime = 0.0;
}

void TimeModule::Terminate()
{
}

#if OPENGL
#include <GLFW\glfw3.h>
static double GetCurrentTime()
{
	return glfwGetTime();
}
#endif