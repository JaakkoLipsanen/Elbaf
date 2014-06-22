#pragma once

namespace FlaiMath
{
	const float Pi = 3.14159265358979323846264338327950288419716939937510582097494459230781640f;
	const float TwoPi = FlaiMath::Pi * 2;
	const float HalfPi = FlaiMath::Pi / 2;
	const float QuarterPi = FlaiMath::Pi / 4;

	template<typename T>
	T Clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : (value > max ? max : value);
	}


	template<typename T>
	T Scale(const T& input, const T& oldMin, const T& oldMax, const T& newMin, const T& newMax)
	{
		return newMin + ((newMax - newMin) * (input - oldMin)) / (oldMax - oldMin);
	}

	// not sure if works
	template<typename T, class TIterator>
	void Scale(TIterator begin, TIterator end, const T& oldMin, const T& oldMax, const T& newMin, const T& newMax)
	{
		while (begin != end)
		{
			*(begin) = newMin + ((newMax - newMin) * (*(begin) - oldMin)) / (oldMax - oldMin);
			++begin;
		}
	}
}