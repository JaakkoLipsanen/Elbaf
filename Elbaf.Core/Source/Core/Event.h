#pragma once
#include <deque> // would it be possible to remove this? not sure..

template <typename TFunc>
class Event final
{
public:
	typedef typename std::add_pointer<TFunc>::type FunctionPointer;
private:
	typedef std::deque<FunctionPointer> FunctionPointerSequence;
public:

	Event<TFunc>& operator +=(FunctionPointer f)
	{
		_functionPointers.push_back(f);
		return *this;
	}

	Event<TFunc>& operator-= (FunctionPointer f)
	{
		_functionPointers.erase(std::remove(_functionPointers.begin(), _functionPointers.end(), f), _functionPointers.end());
		return *this;
	}

	void Invoke()
	{
		for (typename FunctionPointerSequence::iterator it(_functionPointers.begin()); it != _functionPointers.end(); ++it)
		{
			(*it)();
		}
	}

	template <typename TArg0>
	void Invoke(TArg0 a1)
	{
		for (typename FunctionPointerSequence::iterator it(_functionPointers.begin()); it != _functionPointers.end(); ++it)
		{
			(*it)(a1);
		}
	}

	template <typename TArg0, typename TArg1>
	void Invoke(const TArg0& a1, const TArg1& a2)
	{
		for (typename FunctionPointerSequence::iterator it(_functionPointers.begin()); it != _functionPointers.end(); ++it)
			(*it)(a1, a2);
	}

	// todo: make more operator() overloads

private:
	FunctionPointerSequence _functionPointers;
};

