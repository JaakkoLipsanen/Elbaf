#pragma once
#include <deque> // would it be possible to remove this? not sure..

template <typename TFunc>
class Event final
{
	typedef typename std::add_pointer<TFunc>::type FunctionPointer;
	typedef std::deque<FunctionPointer> FunctionPointerSequence;

public:
	Event& operator +=(FunctionPointer f);
	Event& operator -=(FunctionPointer f);

	void operator()()
	{
		for (typename FunctionPointerSequence::iterator it(_functionPointers.begin()); it != _functionPointers.end(); ++it)
		{
			(*it)();
		}
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

private:
	FunctionPointerSequence _functionPointers;
};

