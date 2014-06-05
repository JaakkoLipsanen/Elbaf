#include "Event.h"
/*
Event& Event::operator +=(FunctionPointer f)
{
	_functionPointers.push_back(f);
	return *this;
}

template <typename TFunc>
Event<TFunc>& Event<TFunc>::operator+=(FunctionPointer f)
{

}
*/

/*

template <typename TFunc>
class Event
{
	typedef typename std::add_pointer<TFunc>::type FunctionPointer;
	typedef std::deque<FunctionPointer> FunctionPointerSequence;

	FunctionPointerSequence _functionPointers;
public:
	Event& operator +=(FunctionPointer f)
	{
		_functionPointers.push_back(f);
		return *this;
	}

	Event& operator -=(FunctionPointer f)
	{
		_functionPointers.erase(std::remove(_functionPointers.begin(), _functionPointers.end(), f), _functionPointers.end());
		return *this;
	}

	template <typename TArg0>
	void operator()(TArg0 a1)
	{
		for (typename FunctionPointerSequence::iterator it(_functionPointers.begin()); it != _functionPointers.end(); ++it)
		{
			(*it)(a1);
		}
	}

	template <typename TArg0, typename TArg1>
	void operator()(const TArg0& a1, const TArg1& a2)
	{
		for (typename FunctionPointerSequence::iterator it(_functionPointers.begin()); it != _functionPointers.end(); ++it)
			(*it)(a1, a2);
	}

	// todo: make more operator() overloads
};*/