#pragma once
#include <string>

namespace Ensure
{
	void True(bool argument);
	void True(bool argument, const std::string& message);

	void False(bool argument);
	void False(bool argument, const std::string& message);

	// okay this isn't very good since 'null' isn't clear thing in C++... I mean the object that pointer points at can be destroyed and the pointer isn't null
	void NotNull(void* argument);
	void NotNull(void* argument, const std::string& message);

	// okay this isn't very good since 'null' isn't clear thing in C++... I mean the object that pointer points at can be destroyed and the pointer isn't null
	void Null(void* argument);
	void Null(void* argument, const std::string& message);
}