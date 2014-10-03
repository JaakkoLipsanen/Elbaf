#include <Engine\Game.h>
#include <Diagnostics\Logger.h>
#include <Engine\Screen.h>
#include <Input\Mouse.h>
#include <Graphics\VertexFormats.h>
#include <Core\CursorVisibility.h>
#include <Core\Global.h>
#include <Graphics\IVertexBuffer.h>
#include <Core\Array.h>
#include <Graphics\ShaderSource.h>
#include <Content\ImageLoader.h>
#include "DefaultCamera.h"
#include <Input\MouseButton.h>
#include <Input\Input.h>
#include <Engine\Time.h>
#include <Graphics\IShader.h>
#include <Graphics\ITexture.h>
#include <Graphics\IGraphicsContext.h>
#include <Graphics\CompareFunction.h>
#include <Graphics\IBlendState.h>
#include <Graphics\IDepthState.h>
#include <Graphics\ICullState.h>
#include <Graphics\OpenGL\OGL.h>
#include "NoiseGen.h"
#include <Engine/Scene.h>
#include <Engine/Stopwatch.h>
#include <Math/Range.h>


enum class DepthBufferFormat
{
	None,
	Depth16,
	Depth24Stencil8,
	Depth32,
};

class CustomScene : public Scene { };
class RenderTarget
{
public:
	static std::unique_ptr<RenderTarget> Create(DepthBufferFormat format)
	{
		GLuint frameBufferID;
		glGenFramebuffers(1, &frameBufferID);

		// Modifies global frame buffer. cache old and set it back?
		glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	}

private:
	GLuint _framebufferID;
	GLuint _colorTextureID;
	GLuint _depthTextureID;
};

#include <Core/WindowDescription.h>
class MyGame : public Game
{
protected:
	void SetupWindow(WindowDescription& description) override
	{
		description.Resolution = Size(1920, 1080);
	}

public:
	virtual std::unique_ptr<Scene> CreateDefaultScene() override
	{
		return std::make_unique<CustomScene>();
	}

	virtual void Initialize() override
	{
		Range<float> range(5, 10.05f);
		Range<int> rangeInt(9, 12);

		Logger::MessageStream << "C: " << (-1 % 4);
		Stopwatch sw("Initialize");

		// Initialize mouse settings
		Mouse::SetCursorVisibility(CursorVisibility::Disabled);
		Mouse::SetPosition({ Screen::GetWidth() / 2, Screen::GetHeight() / 2 });

		this->CreateSkybox();
		this->CreateTerrain();

		_shader = this->GetGraphicsContext().CreateShader(ShaderSource("BasicShader-vs.glsl", "BasicShader-fs.glsl"));
		_skyboxTexture = this->GetGraphicsContext().CreateTexture2D(Content::LoadImage("F:/Users/Jaakko/Desktop/Sky.png"));
		_camera = std::unique_ptr<DefaultCamera>(new DefaultCamera);

		_skyboxTexture->BindToSampler(0);
		_shader->SetTextureSampler("TextureSampler", 0);
	}

	virtual void PostUpdate() override
	{
		_camera->Update();
	}

	virtual void PreRender() override
	{
		_shader->SetParameter("MVP", _camera->GetProjection() * _camera->GetView());

		auto& graphicsContext = this->GetGraphicsContext();
		graphicsContext.Clear(Color::RoyalBlue);

		this->RenderSkybox();
		this->RenderTerrain();
	}

	void RenderSkybox()
	{
		auto& graphicsContext = this->GetGraphicsContext();
		graphicsContext.GetCullState().SetCullingEnabled(false); // culling must be off because the cube isn't inverted :/
		graphicsContext.GetDepthState().SetDepthWriteEnabled(false);

		_shader->SetParameter("MVP", _camera->GetProjection() * _camera->GetView() * Matrix::Translate(_camera->GetPosition()));
		_shader->SetParameter("UseLighting", false);

		_shader->ApplyShader();
		_skyboxBuffer->Bind();
		graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, _skyboxBuffer->GetVertexCount());
	}

	void RenderTerrain()
	{
		auto& graphicsContext = this->GetGraphicsContext();
		graphicsContext.GetDepthState().SetDepthWriteEnabled(true);
		graphicsContext.GetCullState().SetCullingEnabled(true);

		_shader->SetParameter("MVP", _camera->GetProjection() * _camera->GetView() * Matrix::Scale(2));
		_skyboxTexture->BindToSampler(0);
		_shader->SetTextureSampler("TextureSampler", 0);
		_shader->SetParameter("UseLighting", true);

		_shader->ApplyShader();
		_terrainBuffer->Bind();
		graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, _terrainBuffer->GetVertexCount());
	}

	void CreateSkybox()
	{
		Vector2f slotSize = Vector2f(1.0f / 4, 1.0f / 3);
		Vector2f pixelSize = Vector2f(1.0f / 4096.f, 1.0f / 3072);
		Color cubeMapColor = Color::White;
		static const VertexPositionColorTexture skyboxVertexData[] = {
			// front
			VertexPositionColorTexture({ -1.0f, -1.0f, -1.0f }, cubeMapColor, slotSize * Vector2f(0, 1)), // BL
			VertexPositionColorTexture({ -1.0f, 1.0f, -1.0f }, cubeMapColor, slotSize * Vector2f(0, 2)), // TL
			VertexPositionColorTexture({ 1, -1, -1.0f }, cubeMapColor, slotSize * Vector2f(1, 1)), // BR

			VertexPositionColorTexture({ -1.0f, 1.0f, -1.0f }, cubeMapColor, slotSize * Vector2f(0, 2)), // TL
			VertexPositionColorTexture({ 1.0f, 1.0f, -1.0f }, cubeMapColor, slotSize * Vector2f(1, 2)), // TR
			VertexPositionColorTexture({ 1, -1, -1.0f }, cubeMapColor, slotSize * Vector2f(1, 1)), // BR

			// back
			VertexPositionColorTexture({ 1.0f, -1.0f, 1 }, cubeMapColor, slotSize * Vector2f(2, 1)), // BL
			VertexPositionColorTexture({ 1.0f, 1.0f, 1 }, cubeMapColor, slotSize * Vector2f(2, 2)), // TL
			VertexPositionColorTexture({ -1, -1, 1 }, cubeMapColor, slotSize * Vector2f(3, 1)), // BR

			VertexPositionColorTexture({ 1.0f, 1.0f, 1 }, cubeMapColor, slotSize * Vector2f(2, 2)), // TL
			VertexPositionColorTexture({ -1, 1, 1 }, cubeMapColor, slotSize * Vector2f(3, 2)), // TR
			VertexPositionColorTexture({ -1, -1, 1 }, cubeMapColor, slotSize * Vector2f(3, 1)), // BR

			// left
			VertexPositionColorTexture({ 1.0f, -1.0f, -1 }, cubeMapColor, slotSize * Vector2f(1, 1)), // BL
			VertexPositionColorTexture({ 1.0f, 1.0f, -1 }, cubeMapColor, slotSize * Vector2f(1, 2)), // TL
			VertexPositionColorTexture({ 1.0f, -1, 1 }, cubeMapColor, slotSize * Vector2f(2, 1)), // BR

			VertexPositionColorTexture({ 1.0f, 1.0f, -1 }, cubeMapColor, slotSize * Vector2f(1, 2)), // TL
			VertexPositionColorTexture({ 1.0f, 1, 1 }, cubeMapColor, slotSize * Vector2f(2, 2)), // TR
			VertexPositionColorTexture({ 1.0f, -1, 1 }, cubeMapColor, slotSize * Vector2f(2, 1)), // BR

			// right
			VertexPositionColorTexture({ -1.0f, 1.0f, -1 }, cubeMapColor, slotSize * Vector2f(4, 2)), // TL
			VertexPositionColorTexture({ -1.0f, -1.0f, -1 }, cubeMapColor, slotSize * Vector2f(4, 1)), // BL
			VertexPositionColorTexture({ -1.0f, -1, 1 }, cubeMapColor, slotSize * Vector2f(3, 1)), // BR

			VertexPositionColorTexture({ -1.0f, 1, 1 }, cubeMapColor, slotSize * Vector2f(3, 2)), // TR
			VertexPositionColorTexture({ -1.0f, 1.0f, -1 }, cubeMapColor, slotSize * Vector2f(4, 2)), // TL
			VertexPositionColorTexture({ -1.0f, -1, 1 }, cubeMapColor, slotSize * Vector2f(3, 1)), // BR

			// top
			VertexPositionColorTexture({ -1.0f, 1.0f, -1 }, cubeMapColor, slotSize * Vector2f(1, 3)), // BL
			VertexPositionColorTexture({ -1.0f, 1.0f, 1 }, cubeMapColor, slotSize * Vector2f(2, 3)), // TR
			VertexPositionColorTexture({ 1.0f, 1, -1 }, cubeMapColor, slotSize * Vector2f(1, 2)), // BR

			VertexPositionColorTexture({ -1.0f, 1.0f, 1 }, Color::White, slotSize * Vector2f(2, 3)), // TR
			VertexPositionColorTexture({ 1.0f, 1, 1 }, cubeMapColor, slotSize * Vector2f(2, 2)), // TR
			VertexPositionColorTexture({ 1.0f, 1, -1 }, cubeMapColor, slotSize * Vector2f(1, 2)), // BR

			// bottom
			VertexPositionColorTexture({ -1.0f, -1.0f, 1 }, cubeMapColor, slotSize * Vector2f(2, 0) + Vector2f(-pixelSize.x, pixelSize.y)), // TR
			VertexPositionColorTexture({ -1.0f, -1.0f, -1 }, cubeMapColor, slotSize * Vector2f(1, 0) + Vector2f(pixelSize.x, pixelSize.y)), // BL
			VertexPositionColorTexture({ 1.0f, -1, -1 }, cubeMapColor, slotSize * Vector2f(1, 1) + Vector2f(pixelSize.x, -pixelSize.y)), // BR

			VertexPositionColorTexture({ 1.0f, -1, 1 }, cubeMapColor, slotSize * Vector2f(2, 1) + Vector2f(-pixelSize.x, -pixelSize.y)), // TR
			VertexPositionColorTexture({ -1.0f, -1.0f, 1 }, cubeMapColor, slotSize * Vector2f(2, 0) + Vector2f(-pixelSize.x, pixelSize.y)), // TR
			VertexPositionColorTexture({ 1.0f, -1, -1 }, cubeMapColor, slotSize * Vector2f(1, 1) + Vector2f(pixelSize.x, -pixelSize.y)), // BR
		};

		_skyboxBuffer = this->GetGraphicsContext().CreateVertexBuffer(BufferType::Static);
		_skyboxBuffer->SetVertexData(skyboxVertexData, Array::Length(skyboxVertexData));
	}

	void CreateTerrain()
	{
		std::vector<VertexPositionColorNormal> terrainVertexData;

		const int Size = 400;
		float grid[(Size + 1) * (Size + 1)];
		const float MaxHeight = 1;
		for (int y = 0; y < Size + 1; y++)
		{
			for (int x = 0; x < Size + 1; x++)
			{
				grid[x + y * Size] = scaled_octave_noise_2d(24, 0.4f, 0.0075f, 0, 60, x, y) + Global::Random.NextFloat(-0.5f, 0.5f); // Global::Random.NextFloat(0, MaxHeight);
			}
		}

		for (int y = 0; y < Size; y++)
		{
			for (int x = 0; x < Size; x++)
			{
				static const Color From = Color::PaleGreen;
				static const Color To = From;

				Vector3f blPos = { x, grid[x + y * Size], y };
				Vector3f brPos = { x + 1, grid[x + 1 + y * Size], y };
				Vector3f tlPos = { x, grid[x + (y + 1) * Size], y + 1.0f };
				Vector3f trPos = { x + 1, grid[x + 1 + (y + 1) * Size], y + 1 };

				Vector3f normalFirst = Vector::Cross(tlPos - blPos, brPos - blPos);
				Vector3f normalSecond = -Vector::Cross(tlPos - trPos, brPos - trPos);

				Color blColor = Color::Lerp(From, To, grid[x + y * Size] / MaxHeight);
				Color brColor = Color::Lerp(From, To, grid[x + 1 + y * Size] / MaxHeight);
				Color tlColor = Color::Lerp(From, To, grid[x + (y + 1) * Size] / MaxHeight);
				Color trColor = Color::Lerp(From, To, grid[x + 1 + (y + 1) * Size] / MaxHeight);

				typedef VertexPositionColorNormal V;

				terrainVertexData.emplace_back(blPos, blColor, normalFirst);
				terrainVertexData.push_back(V(tlPos, tlColor, normalFirst));
				terrainVertexData.push_back(V(brPos, brColor, normalFirst));

				terrainVertexData.push_back(V(tlPos, tlColor, normalSecond));
				terrainVertexData.push_back(V(trPos, trColor, normalSecond));
				terrainVertexData.push_back(V(brPos, brColor, normalSecond));
			}
		}

		_terrainBuffer = this->GetGraphicsContext().CreateVertexBuffer(BufferType::Static);
		_terrainBuffer->SetVertexData(terrainVertexData.data(), terrainVertexData.size());
	}

private:
	std::unique_ptr<IShader> _shader;
	std::unique_ptr<IVertexBuffer> _terrainBuffer;
	std::unique_ptr<IVertexBuffer> _skyboxBuffer;
	std::unique_ptr<DefaultCamera> _camera;
	std::unique_ptr<ITexture2D> _skyboxTexture;
};

int main()
{
	MyGame game;
	game.Run();

	return 1;
}