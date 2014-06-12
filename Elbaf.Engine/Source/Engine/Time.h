
class TimeManager
{
	float _deltaTime;
	float _totalTime;
};

namespace Time
{
	float GetDeltaTime();
	float GetTotalTime();

	// todo: time scale, 'real' delta/total time, smoothed delta time etc
}