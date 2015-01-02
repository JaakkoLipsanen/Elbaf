#include <Engine\Time.h>

#include <Engine\TimeModule.h>
#include <Core\IEngine.h>

#include <chrono>

static TimeModule& GetTimeModule()
{
	return IEngine::GetInstance().GetModule<TimeModule>();
}

float Time::GetDeltaTime()
{
	return GetTimeModule().GetDeltaTime();
}

float Time::GetTotalTime()
{
	return GetTimeModule().GetTotalTime();
}

int Time::GetSystemTime()
{
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds >(
		std::chrono::high_resolution_clock::now().time_since_epoch()
		);

	return ms.count();
}

long long Time::GetSystemTimeInNano()
{
	std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds >(
		std::chrono::high_resolution_clock::now().time_since_epoch()
		);

	return ns.count();
}

double Time::GetCurrentSystemTime()
{
	return GetTimeModule().GetSystemTime();
}