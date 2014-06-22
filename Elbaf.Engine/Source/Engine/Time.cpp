#include <Engine\Time.h>

#include <Engine\TimeModule.h>
#include <Core\IEngine.h>

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