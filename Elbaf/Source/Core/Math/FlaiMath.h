#pragma once
#include <algorithm>
namespace FlaiMath
{
	template<class T>
	T Clamp(const T& value, const T& min, const T& max)
	{
		return std::max(min, std::min(value, max));
	}
}