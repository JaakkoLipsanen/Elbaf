#include <Graphics/FontRenderer.h>
#include <Graphics/ShaderSource.h>
#include <vector>
#include <Graphics/VertexFormats.h>
#include <Graphics/IVertexBuffer.h>
#include <Math/RectangleF.h>
#include <Math/Matrix.h>
#include <Graphics/IShader.h>
#include <Graphics/IBlendState.h>
#include <Graphics/ICullState.h>
#include <Graphics/IDepthState.h>

const std::string VertexShader = R"XXX(
		#version 330 core

		// Input vertex data, different for all executions of this shader.
		layout(location = 0) in vec3 vertexPosition_modelspace;
		layout(location = 1) in vec4 vertexColor;
		layout(location = 2) in vec2 vertexUV;

		uniform mat4 MVP;

		out vec4 fragmentColor;
		out vec2 fragmentUV;

		void main()
		{
			gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
			fragmentUV = vertexUV;
			fragmentColor = vertexColor;
		})XXX";

const std::string FragmentShader = R"XXX(
		#version 330 core 
										
		in vec4 fragmentColor;			
		in vec2 fragmentUV;						

		// Ouput data
		out vec4 color;

		uniform sampler2D TextureSampler;
		void main()
		{
			// Output color = red 
			color = fragmentColor;
			color.rgba *= texture2D(TextureSampler, fragmentUV).r;
		})XXX";

struct FontRenderer::Data
{
	std::vector<VertexPositionColorTexture> Vertices;
	std::unique_ptr<IVertexBuffer> VertexBuffer;
	std::unique_ptr<IShader> FontShader;
	IGraphicsContext& GraphicsContext;

	Data(IGraphicsContext& graphicsContext) :
		GraphicsContext(graphicsContext),
		FontShader(graphicsContext.CreateShader(ShaderSource::FromSource(VertexShader, FragmentShader))),
		VertexBuffer(graphicsContext.CreateVertexBuffer(BufferType::Dynamic))
	{
	}

	void DrawCharacter(Font& font, char character, Vector2f& position, Color color)
	{
		auto& characterDefinition = font.GetCharacterDefinition(character);
		Vector2f topLeftPosition = position + Vector2f(characterDefinition.OffsetFromLeft, -characterDefinition.OffsetFromTop);

		auto& texture = font.GetTexture();
		RectangleF uvRectangle = static_cast<RectangleF>(characterDefinition.TextureUV) / Vector2f(texture.GetSize().Width, texture.GetSize().Height);
		RectangleF destinationRectangle(topLeftPosition.X, topLeftPosition.Y, characterDefinition.TextureUV.Width, characterDefinition.TextureUV.Height);

		typedef VertexPositionColorTexture Vertex;
		this->Vertices.push_back(Vertex(Vector3f(destinationRectangle.MinX(), destinationRectangle.MinY() + destinationRectangle.Height, 0), color, uvRectangle.TopLeft()));
		this->Vertices.push_back(Vertex(Vector3f(destinationRectangle.MinX(), destinationRectangle.MinY(), 0), color, uvRectangle.BottomLeft()));
		this->Vertices.push_back(Vertex(Vector3f(destinationRectangle.MaxX(), destinationRectangle.MinY(), 0), color, uvRectangle.BottomRight()));

		this->Vertices.push_back(Vertex(Vector3f(destinationRectangle.MinX(), destinationRectangle.MinY() + destinationRectangle.Height, 0), color, uvRectangle.TopLeft()));
		this->Vertices.push_back(Vertex(Vector3f(destinationRectangle.MaxX(), destinationRectangle.MinY(), 0), color, uvRectangle.BottomRight()));
		this->Vertices.push_back(Vertex(Vector3f(destinationRectangle.MaxX(), destinationRectangle.MinY() + destinationRectangle.Height, 0), color, uvRectangle.TopRight()));

		position += characterDefinition.Advance;
	}

	void Flush(Font& font)
	{
		if (this->Vertices.size() == 0)
		{
			return;
		}

		this->GraphicsContext.GetDepthState().SetDepthTestEnabled(false);
		this->GraphicsContext.GetDepthState().SetDepthTestEnabled(false);
		this->GraphicsContext.GetBlendState().SetBlendEnabled(true);
		this->GraphicsContext.GetCullState().SetCullingEnabled(false);

		font.GetTexture().BindToSampler(0);
		this->VertexBuffer->SetVertexData(this->Vertices.data(), this->Vertices.size());
		this->VertexBuffer->Bind();

		this->FontShader->Bind();
		this->FontShader->SetParameter("MVP", Matrix::Scale(1, -1, 1) * Matrix::Translate(-1.f, -1.0f, 0) * Matrix::Scale(1.0f / this->GraphicsContext.GetResolution().Width * 2, 1.0f / this->GraphicsContext.GetResolution().Height * 2, 0));
		this->GraphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, this->Vertices.size());

		this->Vertices.clear();
	}
};

FontRenderer::FontRenderer(IGraphicsContext& graphicsContext) :
_pData(new Data(graphicsContext))
{
}
FontRenderer::~FontRenderer() = default;

void FontRenderer::DrawTextShaded2D(Font& font, std::string const& text, Vector2f position, Color backgroundColor, Color foregroundColor, TextCorner originCorner)
{
	this->DrawText2D(font, text, position, backgroundColor, originCorner);
	this->DrawText2D(font, text, position - Vector2f::One, foregroundColor, originCorner);
}

void FontRenderer::DrawText2D(Font& font, std::string const& text, Vector2f position, Color color, TextCorner originCorner)
{
	_pData->Vertices.clear();

	auto textArea = font.MeasureText(text);
	if (originCorner == TextCorner::TopLeft || originCorner == TextCorner::TopRight)
	{
		position.Y += textArea.Height;
	}

	if (originCorner == TextCorner::TopRight || originCorner == TextCorner::BottomRight)
	{
		position.X -= textArea.Width;
	}

	if (originCorner == TextCorner::Center)
	{
		position += Vector2f(-textArea.Width, textArea.Height) / 2.0f;
	}

	char previous = 0;
	for (int i = 0; i < text.size(); i++)
	{
		char character = text[i];
		if (!font.ContainsCharacter(text[i]))
		{
			character = '?';
		}

		position.X += font.GetKerning(previous, character).X;
		_pData->DrawCharacter(font, character, position, color);
		previous = text[i];
	}

	_pData->Flush(font);
}