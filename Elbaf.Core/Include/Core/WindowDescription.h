#pragma once
#include <Math\Size.h>

struct WindowDescription
{
	Size Resolution;
	std::string Title;
	bool IsFullScreen;
	bool IsResizable;
	bool HasBorders; // "does the window have close/minimize button and borders"?

	WindowDescription(const Size& resolution, const std::string& title, bool isFullScreen, bool isResizable, bool hasBorders = true) :
		Resolution(resolution), Title(title), IsFullScreen(isFullScreen), IsResizable(isResizable), HasBorders(hasBorders)
	{
	}
};