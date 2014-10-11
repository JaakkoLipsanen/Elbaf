#pragma once

#include <Engine/Time.h>
#include <Diagnostics/Logger.h>
struct Stopwatch
{
	explicit Stopwatch(std::string name = "");
	~Stopwatch();

	void Stop();
	double DeltaTime();

private:
	std::string _name;
	double _startTime;
	bool _hasStopped;
};