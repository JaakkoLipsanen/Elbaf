#pragma once
#include <Math/Vector.h>
#include <Math/Size.h>

class IMonitor
{
public:
	virtual ~IMonitor() { };

	virtual Size GetSize() const = 0;
	virtual Vector2i GetPosition() const = 0;
	virtual int GetRefreshRate() const = 0;
	virtual std::string GetName() const = 0; // may return invalid value
	virtual Size GetPhysicalSize() const = 0; // in millimeters. may return invalid value
};