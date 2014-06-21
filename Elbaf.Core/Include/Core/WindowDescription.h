#pragma once
#include <Math\Size.h>

struct WindowDescription
{
	Size Resolution;
	std::string Title;
	bool IsFullScreen;

	WindowDescription(const Size& resolution, const std::string& title, bool isFullScreen) :
		Resolution(resolution), Title(title), IsFullScreen(isFullScreen)
	{
	}
};