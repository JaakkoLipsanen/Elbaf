#pragma once
#include <Graphics/IMonitor.h>
#include <memory>

struct GLFWmonitor;
namespace OGL
{
	class Monitor : public IMonitor
	{
	public:
		explicit Monitor(GLFWmonitor* monitor);
		~Monitor();

		Size GetSize() const override;
		Vector2i GetPosition() const override; // im not exactly sure what this returns...
		int GetRefreshRate() const override;
		std::string GetName() const override;
		Size GetPhysicalSize() const override;

	private:
		struct Impl;
		std::unique_ptr<Impl> _pImpl;
	};
}