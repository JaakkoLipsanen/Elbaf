#pragma once
#include <array>

namespace Array
{
	template<class T, size_t N>
	size_t Length(T(&arr)[N]) { return N; }
}