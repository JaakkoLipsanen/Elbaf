#pragma once
#include <functional>
#include <vector>
#include <algorithm>

// todo: move these to some other header? these dont really belong here. Maybe Function.h or something? Function::Create?
template<typename TCaller, typename TReturn>
static std::function<TReturn()> CreateFunction(TCaller* caller, TReturn(TCaller::*value)())
{
	using namespace std::placeholders;
	return std::bind(value, caller);
}

template<typename TCaller, typename TReturn, typename TParameter1>
static std::function<TReturn(TParameter1)> CreateFunction(TCaller* caller, TReturn(TCaller::*value)(TParameter1))
{
	using namespace std::placeholders;
	return std::bind(value, caller, _1);
}

template<typename TCaller, typename TReturn, typename TParameter1, typename TParameter2>
static std::function<TReturn(TParameter1, TParameter2)> CreateFunction(TCaller* caller, TReturn(TCaller::*value)(TParameter1, TParameter2))
{
	using namespace std::placeholders;
	return std::bind(value, caller, _1, _2);
}

template<typename TCaller, typename TReturn, typename TParameter1, typename TParameter2, typename TParameter3>
static std::function<TReturn(TParameter1, TParameter2, TParameter3)> CreateFunction(TCaller* caller, TReturn(TCaller::*value)(TParameter1, TParameter2, TParameter3))
{
	using namespace std::placeholders;
	return std::bind(value, caller, _1, _2, _3);
}

template <typename TFunc>
class Event final
{
public:

	template<typename TCaller, typename TReturn, typename TParameter1, typename TParameter2>
	static std::function<TReturn(TParameter1, TParameter2)> CreateListener(TCaller* caller, TReturn(TCaller::*value)(TParameter1, TParameter2))
	{
		using namespace std::placeholders;
		return std::bind(&value, caller, _1, _2);
	}

	void Add(std::function<TFunc> function)
	{
		_functions.push_back(function);
	}

	Event<TFunc>& operator +=(std::function<TFunc> function)
	{
		_functions.push_back(function);
		return *this;
	}

	// this doesn't work :( unfortunately, std::function<T> doesn't implement == operator so you cant use std::remove (or lots of other functions)
	// one way to implement un-subscribing would be for example A: doing adding listener like Add(pointer-to-parent, std::function<T>) or B: Add(string-id, std::function<T>) and then make Remove implement similiar stuff. plah!
 /* Event<TFunc>& operator -=(std::function<TFunc> function)
	{
		_functions.erase(std::remove(_functions.begin(), _functions.end(), function), _functions.end());
		return *this;
	} */

	void Invoke()
	{
		for (auto& func : _functions)
		{
			func();
		}
	}

	template<typename TArgument1>
	void Invoke(TArgument1 argument1)
	{
		for (auto& func : _functions)
		{
			func(argument1);
		}
	}

	template<typename TArgument1, typename TArgument2>
	void Invoke(TArgument1 argument1, TArgument2 argument2)
	{
		for (auto& func : _functions)
		{
			func(argument1, argument2);
		}
	}

	template<typename TArgument1, typename TArgument2, typename TArgument3>
	void Invoke(TArgument1 argument1, TArgument2 argument2, TArgument3 argument3)
	{
		for (auto& func : _functions)
		{
			func(argument1, argument2, argument3);
		}
	}

	int GetListenerCount()
	{
		return static_cast<int>(_functions.size());
	}

	void Clear()
	{
		_functions.clear();
	}

private:
	std::vector<std::function<TFunc>> _functions; // use deque?
};

