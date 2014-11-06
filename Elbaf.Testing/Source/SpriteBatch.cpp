#include <SpriteBatch.h>
#include <Diagnostics/Ensure.h>
#include <Graphics/VertexBuffer.h>
#include <Graphics/GraphicsContext.h>
#include <Graphics/ShaderSource.h>
#include <Graphics/VertexElement.h>
#include <Graphics/VertexDeclaration.h>
#include <Graphics/Shader.h>
#include <Graphics/Texture.h>
#include <Math/RectangleF.h>

#include <Graphics/BlendState.h>
#include <Graphics/CullState.h>
#include <Graphics/DepthState.h>

struct SpriteVertex
{
	Vector2f Position;
	Vector4f Color; // todo: just use Color and send the data to gpu as 3x Byte (normalized)? also, this should be 4-element (alpha)....
	Vector2f TextureCoordinate;

	SpriteVertex(Vector2f position, ::Color color, Vector2f textureCoordinate) : Position(position), Color(color.ToVector4f()), TextureCoordinate(textureCoordinate)
	{
	}

	static const VertexDeclaration Declaration; // = VertexDeclaration({ VertexElement(), VertexElement() }); // VertexDeclaration({ VertexElement() });
	static const VertexDeclaration& GetVertexDeclaration()
	{
		return Declaration;
	}
};

// VertexPositionColorTexture
const VertexDeclaration SpriteVertex::Declaration = VertexDeclaration({
	VertexElement(0, 2, VertexElementType::Float, false, offsetof(SpriteVertex, Position)),
	VertexElement(1, 4, VertexElementType::Float, false, offsetof(SpriteVertex, Color)),
	VertexElement(2, 2, VertexElementType::Float, false, offsetof(SpriteVertex, TextureCoordinate)) });


// okay this fucking sucks.. in glsl, I cant index a sampler-array per-vertex (the index must be an uniform)... so I have to flush the buffer everytime the texture changes..
static const std::string SpriteShaderSource = R"XXX(
	
	#(vertex-shader)
	#(name "SpriteBatch VS")
	#version 430

	layout(location = 0) in vec2 VertexPosition;
	layout(location = 1) in vec4 VertexColor;
	layout(location = 2) in vec2 VertexUV;
	
	out vec4 FragmentColor;
	out vec2 FragmentUV;
	
	uniform mat4x4 ViewProjection;
	
	void FragmentShader() {
		gl_Position = ViewProjection * vec4(VertexPosition, 0, 1);

		FragmentColor = VertexColor;
		FragmentUV = VertexUV;	
	}

	#(fragment-shader)
	#(name "SpriteBatch FS")
	#version 430
	
	in vec4 FragmentColor;
	in vec2 FragmentUV;

	layout(location = 0) out vec4 color;

	uniform sampler2D TextureSampler;
	
	void main() {
		color = texture2D(TextureSampler, FragmentUV);
		color *= FragmentColor;
	}

	)XXX";

class SpriteBatch::Impl
{
public:
	explicit Impl(GraphicsContext& graphicsContext) :
		GraphicsContext(graphicsContext), HasBegun(false), SpriteShader(graphicsContext.CreateShader(ShaderSource::FromSource(SpriteShaderSource))), VertexBuffer(graphicsContext.CreateVertexBuffer(BufferType::Dynamic)), CurrentTexture(nullptr)
	{
	}

	bool HasBegun;
	std::unique_ptr<VertexBuffer> VertexBuffer;
	std::unique_ptr<Shader> SpriteShader;
	std::vector<SpriteVertex> Vertices;
	GraphicsContext& GraphicsContext;
	Texture2D* CurrentTexture;

	void Flush()
	{
		if (this->Vertices.size() == 0)
		{
			this->CurrentTexture = nullptr;
			return;
		}

		this->GraphicsContext.GetDepthState().SetDepthTestEnabled(false);
		this->GraphicsContext.GetDepthState().SetDepthTestEnabled(false);
		this->GraphicsContext.GetBlendState().SetBlendEnabled(true);
		this->GraphicsContext.GetCullState().SetCullingEnabled(false);

		Ensure::NotNull(this->CurrentTexture);
		this->VertexBuffer->SetVertexData(this->Vertices.data(), this->Vertices.size());

		this->VertexBuffer->Bind();
		this->SpriteShader->Bind();
		this->CurrentTexture->BindToSampler(0);
		this->SpriteShader->SetTextureSampler("TextureSampler", 0);
		this->SpriteShader->SetParameter("ViewProjection", 
			Matrix::Scale(1, -1, 1) * 
			Matrix::Translate(-1.f, -1.0f, 0) *
			Matrix::Scale(1.0f / this->GraphicsContext.GetResolution().Width * 2, 1.0f / this->GraphicsContext.GetResolution().Height * 2, 0));
		
		this->GraphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, this->Vertices.size());

		this->Vertices.clear();
		this->CurrentTexture = nullptr;
	}
};

SpriteBatch::SpriteBatch(GraphicsContext& graphicsContext)
	: _pImpl(new Impl(graphicsContext))
{
}

SpriteBatch::~SpriteBatch() = default;
void SpriteBatch::Begin()
{
	Ensure::False(_pImpl->HasBegun);
	_pImpl->HasBegun = true;
}

void SpriteBatch::End()
{
	Ensure::True(_pImpl->HasBegun);

	_pImpl->Flush();
	_pImpl->HasBegun = false;
}

void SpriteBatch::Draw(Texture2D& texture, Vector2f position, Color color)
{
	this->Draw(texture, position, color, 0, Vector2f::One, Vector2f::Zero);
}

void SpriteBatch::Draw(Texture2D& texture, Vector2f position, Color color, float rotation, Vector2f scale)
{
	this->Draw(texture, position, color, rotation, scale, Vector2f::Zero);
}

void SpriteBatch::Draw(Texture2D& texture, Vector2f position, Color color, float rotation, Vector2f scale, Vector2f origin)
{
	if (_pImpl->CurrentTexture != nullptr && _pImpl->CurrentTexture != &texture) // compare address
	{
		_pImpl->Flush();
	}

	_pImpl->CurrentTexture = &texture;
	Vector2f size = Vector2f(texture.GetSize().ToVector2i()) * scale;

	SpriteVertex TL = SpriteVertex(position, color, Vector2f::Zero);
	SpriteVertex TR = SpriteVertex(position + Vector2f::UnitX * size, color, Vector2f::UnitX);
	SpriteVertex BL = SpriteVertex(position + Vector2f::UnitY * size, color, Vector2f::UnitY);
	SpriteVertex BR = SpriteVertex(position + size, color, Vector2f::One);

	_pImpl->Vertices.push_back(BL);
	_pImpl->Vertices.push_back(TL);
	_pImpl->Vertices.push_back(TR);

	_pImpl->Vertices.push_back(BL);
	_pImpl->Vertices.push_back(TR);
	_pImpl->Vertices.push_back(BR);
}