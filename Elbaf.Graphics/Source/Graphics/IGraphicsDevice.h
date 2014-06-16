#pragma once

enum class CullMode
{
	CounterClockwise,
	Clockwise,
};

enum class CullFace
{
	Front,
	Back,
	FrontAndBack,
};

struct Size;
enum class ClearOptions;
enum class CompareFunction;
enum class PrimitiveType;
struct Color;
class IGraphicsModule;

// todo: make DepthState, RasterizerState, StencilState etc?
class IGraphicsDevice
{
public:
	virtual ~IGraphicsDevice() = default;

	virtual void Clear(const Color& color) = 0;
	virtual void Clear(const ClearOptions& clearOptions, const Color& color, float depth = 0, int stencilValue = 0) = 0;

	// returns the old resolution

	virtual Size GetResolution() const = 0;
	virtual void ChangeResolution(const Size& newSize) = 0;

	virtual bool IsDepthTestEnabled() const = 0;
	virtual void SetDepthTestEnabled(bool isEnabled) = 0;

	virtual CompareFunction GetDepthFunction() const = 0;
	virtual void SetDepthFunction(CompareFunction compareFunction) = 0;

	virtual CullMode GetCullMode() const = 0;
	virtual void SetCullMode(CullMode cullMode) = 0;

	virtual CullFace GetCullFace() const = 0;
	virtual void SetCullFace(CullFace cullFace) = 0;

	// todo: render targets, vertexbuffers, stencil, scissor, depth states, textures(?) etc etc etc

	// DRAW
	virtual void DrawPrimitives(PrimitiveType primitiveType, int firstIndex, int count) = 0;
};