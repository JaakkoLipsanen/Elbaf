#include "Time.h"

static TimeModule& GetTimeModule()
{
	return *IEngine::GetInstance().GetModule<TimeModule>();
}

float Time::GetDeltaTime()
{
	return GetTimeModule().GetDeltaTime();
}

float Time::GetTotalTime()
{
	return GetTimeModule().GetTotalTime();
}