#include "Event.h"

template<typename TFunc>
Event<TFunc>& Event<TFunc>::operator +=(FunctionPointer f)
{
	_functionPointers.push_back(f);
	return *this;
}

template<typename TFunc>
Event<TFunc>& Event<TFunc>::operator -= (FunctionPointer f)
{
	_functionPointers.erase(std::remove(_functionPointers.begin(), _functionPointers.end(), f), _functionPointers.end());
	return *this;
}