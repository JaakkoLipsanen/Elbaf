#pragma once

namespace Array
{
	template<class T, size_t N>
	size_t Length(T(&)[N]) { return N; }
}