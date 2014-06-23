#pragma once
#include <memory>

// move to own headers
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

enum class ClearOptions;
enum class CompareFunction;
enum class PrimitiveType;
enum class BufferType;

struct Color;
struct Size;
struct Image;
struct ShaderSource;
struct BlendStatePreset;
struct DepthStatePreset;
struct CullStatePreset;

class ITexture;
class ITexture2D;
class IVertexBuffer;
class IShader;
class IBlendState;
class IDepthState;
class ICullState;

// todo: make DepthState, RasterizerState, StencilState etc? // TODO: MAKE THESE, BLENDSTATE ALREADY DONE
// update: those would really really be great... however they would also add a lot of new classes that have to be implemented per API :(
class IGraphicsContext
{
public:
	IGraphicsContext() = default;
	virtual ~IGraphicsContext() = default;

	virtual void Clear(const Color& color) = 0;
	virtual void Clear(const ClearOptions& clearOptions, const Color& color, float depth = 0, int stencilValue = 0) = 0;

	virtual Size GetResolution() const = 0;
	virtual void ChangeResolution(const Size& newSize) = 0;

	// cull
	virtual ICullState& GetCullState() = 0;
	virtual void SetCullState(const CullStatePreset& preset) = 0;

	// depth
	virtual IDepthState& GetDepthState() = 0;
	virtual void SetDepthState(const DepthStatePreset& preset) = 0;

	// blend
	virtual IBlendState& GetBlendState() = 0;
	virtual void SetBlendState(const BlendStatePreset& preset) = 0; // ????????????????????????????? I was thinking, maybe better would be "BlendStatePreset" or something like that

	// todo: render targets, vertexbuffers, stencil, scissor, depth states, textures(?) etc etc etc

	// DRAW
	virtual void DrawPrimitives(PrimitiveType primitiveType, int firstIndex, int count) = 0;

	// CREATE
	virtual std::unique_ptr<ITexture2D> CreateTexture2D(std::unique_ptr<Image> textureData) = 0;
	virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(BufferType bufferType) = 0;
	virtual std::unique_ptr<IShader> CreateShader(const ShaderSource& shaderData) = 0;
	virtual std::unique_ptr<IBlendState> CreateBlendState() = 0;
};