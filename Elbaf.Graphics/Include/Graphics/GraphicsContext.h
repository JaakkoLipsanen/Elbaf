#pragma once
#include <memory>
#include <Graphics/TextureFormat.h>
#include <vector>
#include <Math/Rectangle.h>

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

enum class DepthBufferFormat
{
	None,
	Depth16,
	Depth24Stencil8,
	Depth24,
	Depth32,
};


enum class ClearOptions;
enum class CompareFunction;
enum class PrimitiveType;
enum class BufferType;

struct Color;
struct Image;
struct ShaderSource;
struct BlendStatePreset;
struct DepthStatePreset;
struct CullStatePreset;
struct Size;

class ITexture;
class Texture2D;
class VertexBuffer;
class Shader;
class BlendState;
class DepthState;
class CullState;
class RenderTarget;

// todo: make DepthState, RasterizerState, StencilState etc? // TODO: MAKE THESE, BLENDSTATE ALREADY DONE
// update: those would really really be great... however they would also add a lot of new classes that have to be implemented per API :(
class GraphicsContext
{
public:
	GraphicsContext() = default;
	virtual ~GraphicsContext() = default;

	virtual void Clear(const Color& color) = 0;
	virtual void Clear(const ClearOptions& clearOptions, const Color& color, float depth = 1, int stencilValue = 0) = 0;

	virtual Size GetResolution() const = 0;
	virtual void ChangeResolution(const Size& newSize) = 0;

	// cull
	virtual CullState& GetCullState() = 0;
	virtual void SetCullState(const CullStatePreset& preset) = 0;

	// depth
	virtual DepthState& GetDepthState() = 0;
	virtual void SetDepthState(const DepthStatePreset& preset) = 0;

	// blend
	virtual BlendState& GetBlendState() = 0;
	virtual void SetBlendState(const BlendStatePreset& preset) = 0; // ????????????????????????????? I was thinking, maybe better would be "BlendStatePreset" or something like that

	// todo: render targets, vertexbuffers, stencil, scissor, depth states, textures(?) etc etc etc

	// DRAW
	virtual void DrawPrimitives(PrimitiveType primitiveType, int firstIndex, int count) = 0;

	// CREATE
	virtual std::unique_ptr<RenderTarget> CreateRenderTarget(int width, int height, DepthBufferFormat depthFormat = DepthBufferFormat::Depth24Stencil8, std::vector<TextureFormat> colorFormats = { TextureFormat::RBG8 }) = 0;
	virtual std::unique_ptr<Texture2D> CreateTexture2D(const Image& textureData) = 0;
	virtual std::unique_ptr<VertexBuffer> CreateVertexBuffer(BufferType bufferType) = 0;
	virtual std::unique_ptr<Shader> CreateShader(const ShaderSource& shaderData) = 0;
	virtual std::unique_ptr<BlendState> CreateBlendState() = 0;

	// BIND
	virtual void BindRenderTarget(RenderTarget* renderTarget, bool updateViewport = true) = 0;
	void BindRenderTarget(RenderTarget& renderTarget, bool updateViewport = true)  { this->BindRenderTarget(&renderTarget); }

	//
	virtual void SetViewport(Rectangle rectangle) = 0;
};