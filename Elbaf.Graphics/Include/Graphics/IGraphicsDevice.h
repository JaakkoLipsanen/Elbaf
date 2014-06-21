#pragma once
#include <memory>

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

class ITexture;
class ITexture2D;
class IVertexBuffer;
class IShader;

// todo: make DepthState, RasterizerState, StencilState etc?
class IGraphicsDevice
{
public:
	IGraphicsDevice() = default;
	virtual ~IGraphicsDevice() = default;

	virtual void Clear(const Color& color) = 0;
	virtual void Clear(const ClearOptions& clearOptions, const Color& color, float depth = 0, int stencilValue = 0) = 0;

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

	virtual bool IsCullingEnabled() const = 0;
	virtual void SetCullingEnabled(bool enabled) = 0;

	// todo: render targets, vertexbuffers, stencil, scissor, depth states, textures(?) etc etc etc

	// DRAW
	virtual void DrawPrimitives(PrimitiveType primitiveType, int firstIndex, int count) = 0;

	// CREATE
	virtual std::unique_ptr<ITexture2D> CreateTexture2D(std::unique_ptr<Image> textureData) = 0;
	virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(BufferType bufferType) = 0;
	//virtual std::unique_ptr<IShader> CreateShader(std::unique_ptr<ShaderSource> shaderData) = 0;
	virtual std::unique_ptr<IShader> CreateShader(const ShaderSource& shaderData) = 0;
};