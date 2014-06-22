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

class MyGame : public Game
{
public:
	virtual std::unique_ptr<Scene> CreateDefaultScene() override
	{
		return std::unique_ptr<Scene>(nullptr);
	}

	virtual void Initialize() override
	{
		Logger::LogMessage(Screen::GetSize());
		Mouse::SetCursorVisibility(CursorVisibility::Disabled);
		Mouse::SetPosition({ Screen::GetWidth() / 2, Screen::GetHeight() / 2 });

		static const VertexPosition vertexData[] = {
			VertexPosition({ 0.5f, -0.5f, 0 }),
			VertexPosition({ 0.1f, -0.5f, 0 }),
			VertexPosition({ 0, 0, 0.0f }) };

		static const VertexPositionColor vertexData2[] = {
			VertexPositionColor({ -1.0f, 0.0f, 0 }, Color::Red),
			VertexPositionColor({ 0, 1.0f, 0 }, Color::Green),
			VertexPositionColor({ 1, 0, 0.0f }, Color::Blue) };

		Vector2f slotSize = Vector2f(1.0f / 4, 1.0f / 3);
		Vector2f pixelSize = Vector2f(1.0f / 3600.0f, 1.0f / 2700);
		Color cubeMapColor = Color::White;
		static const VertexPositionColorTexture vertexData3[] = {
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
			VertexPositionColorTexture({ 1.0f, 1, 1 }, cubeMapColor, slotSize * Vector2f(2,2)), // TR
			VertexPositionColorTexture({ 1.0f, 1, -1 }, cubeMapColor, slotSize * Vector2f(1, 2)), // BR


			// bottom
			VertexPositionColorTexture({ -1.0f, -1.0f, 1 }, cubeMapColor, slotSize * Vector2f(2, 0) + Vector2f(-pixelSize.x, pixelSize.y)), // TR
			VertexPositionColorTexture({ -1.0f, -1.0f, -1 }, cubeMapColor, slotSize * Vector2f(1, 0) + Vector2f(pixelSize.x, pixelSize.y)), // BL
			VertexPositionColorTexture({ 1.0f, -1, -1 }, cubeMapColor, slotSize * Vector2f(1, 1) + Vector2f(pixelSize.x, -pixelSize.y)), // BR

			VertexPositionColorTexture({ 1.0f, -1, 1 }, cubeMapColor, slotSize * Vector2f(2, 1) + Vector2f(-pixelSize.x, -pixelSize.y)), // TR
			VertexPositionColorTexture({ -1.0f, -1.0f, 1 }, cubeMapColor, slotSize * Vector2f(2, 0) + Vector2f(-pixelSize.x, pixelSize.y)), // TR
			VertexPositionColorTexture({ 1.0f, -1, -1 }, cubeMapColor, slotSize * Vector2f(1, 1) + Vector2f(pixelSize.x, -pixelSize.y)), // BR
		};

		std::vector<VertexPositionColor> vertexDataNew;

		const int Size = 300;
		float grid[(Size + 1) * (Size + 1)];
		const float MaxHeight = 0.4f;
		for (int y = 0; y < Size + 1; y++)
		{
			for (int x = 0; x < Size + 1; x++)
			{
				grid[x + y * Size] = Global::Random.NextFloat(0, MaxHeight);
			}
		}

		for (int y = 0; y < Size; y++)
		{
			for (int x = 0; x < Size; x++)
			{
				static const Color From = Color::LightBlue;
				static const Color To = Color::White * 0.1f;
				VertexPositionColor bl({ x, grid[x + y * Size], y }, Color::Lerp(From, To, grid[x + y * Size] / MaxHeight));
				VertexPositionColor br({ x + 1, grid[x + 1 + y * Size], y }, Color::Lerp(From, To, grid[x + 1 + y * Size] / MaxHeight));
				VertexPositionColor tl({ x, grid[x + (y + 1) * Size], y + 1 }, Color::Lerp(From, To, grid[x + (y + 1) * Size] / MaxHeight));
				VertexPositionColor tr({ x + 1, grid[x + 1 + (y + 1) * Size], y + 1 }, Color::Lerp(From, To, grid[x + 1 + (y + 1) * Size] / MaxHeight));

				vertexDataNew.push_back(bl);
				vertexDataNew.push_back(tl);
				vertexDataNew.push_back(br);

				vertexDataNew.push_back(tl);
				vertexDataNew.push_back(tr);
				vertexDataNew.push_back(br);
			}
		}

		auto& graphicsContext = this->GetGraphicsContext();
		_buffer3 = graphicsContext.CreateVertexBuffer(BufferType::Static);	
		_buffer2 = graphicsContext.CreateVertexBuffer(BufferType::Static);

		_buffer2->SetVertexData(vertexDataNew.data(), vertexDataNew.size());
		_buffer3->SetVertexData(vertexData3, Array::Length(vertexData3));

		_shader = graphicsContext.CreateShader(ShaderSource("BasicShader-vs.glsl", "BasicShader-fs.glsl"));
		_texture = graphicsContext.CreateTexture2D(Content::LoadImage("F:/Users/Jaakko/Desktop/Skybox1.png"));
		_camera = std::unique_ptr<DefaultCamera>(new DefaultCamera);

		_texture->BindToSampler(0);
		_shader->SetTextureSampler("TextureSampler", 0);
	}

	virtual void PreRender() override
	{
		_camera->Update();
		_shader->SetParameter("MVP", _camera->GetProjection() * _camera->GetView());

		if (Input::IsNewMouseButtonPress(MouseButton::Right))
		{
			static const VertexPosition vertexData[] = {
				VertexPosition({ 0.5f, -0.5f, 0 }),
				VertexPosition({ 0.1f, -0.5f, 0 }),
				VertexPosition({ 0, 0, 0.0f }) };

			_buffer2->SetVertexData(vertexData, 3);
		}


		this->GetGraphicsContext().Clear(Color::RoyalBlue);
		if (Input::IsMouseButtonPressed(MouseButton::Left) || true)
		{
			auto& blendState = this->GetGraphicsContext().GetBlendState();
			blendState.SetBlendEnabled(true);
			blendState.SetSourceBlend(BlendFactor::SourceAlpha);
			blendState.SetDestinationBlend(BlendFactor::OneMinusSourceAlpha);

			this->GetGraphicsContext().SetCullingEnabled(false); // culling must be off because the cube isn't inverted :/

			this->GetGraphicsContext().SetDepthWriteEnabled(false);
			_shader->ApplyShader();
			_shader->SetParameter("MVP", _camera->GetProjection() * _camera->GetView() * (Matrix::Translate(_camera->GetPosition()) * Matrix::RotateAroundAxis(Time::GetTotalTime() * 0, Vector3f::UnitZ) * Matrix::Scale(1)));
			_buffer3->Bind();
			this->GetGraphicsContext().DrawPrimitives(PrimitiveType::TriangleList, 0, _buffer3->GetVertexCount());
			this->GetGraphicsContext().SetDepthWriteEnabled(true );
			this->GetGraphicsContext().SetCullingEnabled(true);

			_shader->SetParameter("MVP", _camera->GetProjection() * _camera->GetView());
			_texture->BindToSampler(0);
			_shader->SetTextureSampler("TextureSampler", 0);

			_shader->ApplyShader();
			_buffer2->Bind();
			this->GetGraphicsContext().DrawPrimitives(PrimitiveType::TriangleList, 0, _buffer2->GetVertexCount()); 
		}

		if (Input::GetScrollWheelDelta() != 0)
		{
			Logger::LogMessage(Input::GetScrollWheelDelta());
		}
	}

private:
	std::unique_ptr<IShader> _shader;
	std::unique_ptr<IVertexBuffer> _buffer2;
	std::unique_ptr<IVertexBuffer> _buffer3;
	std::unique_ptr<DefaultCamera> _camera;
	std::unique_ptr<ITexture2D> _texture;
};

int main()
{
	MyGame game;
	game.Run();

	return 1;
}