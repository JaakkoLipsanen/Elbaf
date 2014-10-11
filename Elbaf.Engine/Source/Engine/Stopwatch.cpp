#include <Engine/Stopwatch.h>
#include <string>

Stopwatch::Stopwatch(std::string name)
{
	_startTime = Time::GetCurrentSystemTime();
	_name = name;
	_hasStopped = false;
}

Stopwatch::~Stopwatch()
{
	this->Stop();
}

void Stopwatch::Stop()
{
	if (!_hasStopped)
	{
		// "Stopwatch (Terrain Generation): Time 0.552
		Logger::MessageStream << "Stopwatch";
		if (_name != "")
		{
			Logger::MessageStream << " (\"" << _name << "\")";
		}

		Logger::MessageStream << ": Time " << (this->DeltaTime() * 1000) << "ms \n";
		_hasStopped = true;
	}
}

double Stopwatch::DeltaTime()
{
	return Time::GetCurrentSystemTime() - _startTime;
}