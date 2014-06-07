#pragma once

struct Size;
enum class ClearOptions;
struct Color;
class IGraphicsModule;

class IGraphicsDevice
{
public:
	virtual ~IGraphicsDevice() = default;

	virtual void Clear(const Color& color) = 0;
	virtual void Clear(const ClearOptions& clearOptions, const Color& color, float depth = 0, int stencilValue = 0) = 0;

	// returns the old resolution
	virtual Size ChangeResolution(const Size& newSize) = 0;

	// todo: render targets, vertexbuffers, stencil, scissor, depth states, textures(?) etc etc etc
};