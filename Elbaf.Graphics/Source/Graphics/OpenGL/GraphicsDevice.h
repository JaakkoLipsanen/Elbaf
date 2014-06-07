#pragma once
#include <Graphics\IGraphicsDevice.h>

namespace OGL
{
	// okay I'm having a bit of a "fuck that" feelings atm.. So basically, don't focus so much on the portability/abstractness, just get it done!
	class GraphicsDevice : public IGraphicsDevice
	{
	public:
		virtual ~GraphicsDevice() override;

		virtual void Clear(const Color& color) override;
		virtual void Clear(const ClearOptions& clearOptions, const Color& color, float depth = 0, int stencilValue = 0) override;

		virtual Size ChangeResolution(const Size& newSize) override;
	};
}

#if !OPENGL
#error ("Error: This is an OpenGL-specific class and "OPENGL" preprocessor is not defined!")
#endif