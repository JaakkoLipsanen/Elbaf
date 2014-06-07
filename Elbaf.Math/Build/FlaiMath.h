#pragma once
namespace FlaiMath
{
	template<class T>
	T Clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : (value > max ? max : value);
	}
}