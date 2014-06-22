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
#include <Graphics\OpenGL\OGL.h>
#include <Input\Input.h>
#include <Engine\Time.h>
#include <Graphics\IShader.h>
#include <Graphics\ITexture.h>
#include <Graphics\IGraphicsContext.h>

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

		static const VertexPositionColorTexture vertexData3[] = {
			// front
			VertexPositionColorTexture({ -1.0f, -1.0f, -1.0f }, Color::Transparent, Vector2f::Zero), // BL
			VertexPositionColorTexture({ -1.0f, 1.0f, -1.0f }, Color::Transparent, Vector2f(0, 1)), // TL
			VertexPositionColorTexture({ 1, -1, -1.0f }, Color::Transparent, Vector2f(1, 0)), // BR
		
			VertexPositionColorTexture({ -1.0f, 1.0f, -1.0f }, Color::Transparent, Vector2f(0, 1)), // TL
			VertexPositionColorTexture({ 1.0f, 1.0f, -1.0f }, Color::Transparent, Vector2f(1, 1)), // TR
			VertexPositionColorTexture({ 1, -1, -1.0f }, Color::Transparent, Vector2f(1, 0)), // BR

			// back
			VertexPositionColorTexture({ 1.0f, -1.0f, 1 }, Color::Transparent, Vector2f::Zero), // BL
			VertexPositionColorTexture({ 1.0f, 1.0f, 1 }, Color::Transparent, Vector2f(0, 1)), // TL
			VertexPositionColorTexture({ -1, -1, 1 }, Color::Transparent, Vector2f(1, 0)), // BR

			VertexPositionColorTexture({ 1.0f, 1.0f, 1 }, Color::Transparent, Vector2f(0, 1)), // TL
			VertexPositionColorTexture({ -1, 1, 1 }, Color::Transparent, Vector2f(1, 1)), // TR
			VertexPositionColorTexture({ -1, -1, 1 }, Color::Transparent, Vector2f(1, 0)), // BR

			// left
			VertexPositionColorTexture({ 1.0f, -1.0f, -1 }, Color::Transparent, Vector2f::Zero), // BL
			VertexPositionColorTexture({ 1.0f, 1.0f, -1 }, Color::Transparent, Vector2f(0, 1)), // TL
			VertexPositionColorTexture({ 1.0f, -1, 1 }, Color::Transparent, Vector2f(1, 0)), // BR

			VertexPositionColorTexture({ 1.0f, 1.0f, -1 }, Color::Transparent, Vector2f(0, 1)), // TL
			VertexPositionColorTexture({ 1.0f, 1, 1 }, Color::Transparent, Vector2f(1, 1)), // TR
			VertexPositionColorTexture({ 1.0f, -1, 1 }, Color::Transparent, Vector2f(1, 0)), // BR


			// right
			VertexPositionColorTexture({ -1.0f, 1.0f, -1 }, Color::Transparent, Vector2f(0, 1)), // TL
			VertexPositionColorTexture({ -1.0f, -1.0f, -1 }, Color::Transparent, Vector2f::Zero), // BL
			VertexPositionColorTexture({ -1.0f, -1, 1 }, Color::Transparent, Vector2f(1, 0)), // BR

			VertexPositionColorTexture({ -1.0f, 1, 1 }, Color::Transparent, Vector2f(1, 1)), // TR
			VertexPositionColorTexture({ -1.0f, 1.0f, -1 }, Color::Transparent, Vector2f(0, 1)), // TL
			VertexPositionColorTexture({ -1.0f, -1, 1 }, Color::Transparent, Vector2f(1, 0)), // BR



			// top
			VertexPositionColorTexture({ -1.0f, 1.0f, -1 }, Color::Transparent, Vector2f(0, 0)), // BL
			VertexPositionColorTexture({ -1.0f, 1.0f, 1 }, Color::Transparent, Vector2f(0, 1)), // TR
			VertexPositionColorTexture({ 1.0f, 1, -1 }, Color::Transparent, Vector2f(1, 0)), // BR

			VertexPositionColorTexture({ -1.0f, 1.0f, 1 }, Color::Transparent, Vector2f(0, 1)), // TR
			VertexPositionColorTexture({ 1.0f, 1, 1 }, Color::Transparent, Vector2f(1, 1)), // TR
			VertexPositionColorTexture({ 1.0f, 1, -1 }, Color::Transparent, Vector2f(1, 0)), // BR


			// bottom
			VertexPositionColorTexture({ -1.0f, -1.0f, 1 }, Color::Transparent, Vector2f(0, 1)), // TR
			VertexPositionColorTexture({ -1.0f, -1.0f, -1 }, Color::Transparent, Vector2f(0, 0)), // BL
			VertexPositionColorTexture({ 1.0f, -1, -1 }, Color::Transparent, Vector2f(1, 0)), // BR

			VertexPositionColorTexture({ 1.0f, -1, 1 }, Color::Transparent, Vector2f(1, 1)), // TR
			VertexPositionColorTexture({ -1.0f, -1.0f, 1 }, Color::Transparent, Vector2f(0, 1)), // TR
			VertexPositionColorTexture({ 1.0f,- 1, -1 }, Color::Transparent, Vector2f(1, 0)), // BR
		};

		std::vector<VertexPositionColor> vertexDataNew;

		const int Size = 300;
		float grid[(Size + 1) * (Size + 1)];

		for (int y = 0; y < Size + 1; y++)
		{
			for (int x = 0; x < Size + 1; x++)
			{
				grid[x + y * Size] = Global::Random.NextFloat(0, 1);
			}
		}

		for (int y = 0; y < Size; y++)
		{
			for (int x = 0; x < Size; x++)
			{

				VertexPositionColor bl({ x, grid[x + y * Size], y }, Color::Brown * 0.1f);
				VertexPositionColor br({ x + 1, grid[x + 1 + y * Size], y }, Color::RosyBrown);
				VertexPositionColor tl({ x, grid[x + (y + 1) * Size], y + 1 }, Color::SaddleBrown);
				VertexPositionColor tr({ x + 1, grid[x + 1 + (y + 1) * Size], y + 1 }, Color::SandyBrown);

				vertexDataNew.push_back(bl);
				vertexDataNew.push_back(tl);
				vertexDataNew.push_back(br);

				vertexDataNew.push_back(tl);
				vertexDataNew.push_back(tr);
				vertexDataNew.push_back(br);
			}
		}

		auto& graphicsDevice = this->GetGraphicsContext();
		_buffer3 = graphicsDevice.CreateVertexBuffer(BufferType::Static); // IVertexBuffer::CreateVertexBuffer(vertexData3, Array::Length(vertexData3));	
		_buffer2 = graphicsDevice.CreateVertexBuffer(BufferType::Static);

		_buffer2->SetVertexData(vertexDataNew.data(), vertexDataNew.size());
		_buffer3->SetVertexData(vertexData3, Array::Length(vertexData3));

		_shader = graphicsDevice.CreateShader(ShaderSource("BasicShader-vs.glsl", "BasicShader-fs.glsl"));
		_texture = graphicsDevice.CreateTexture2D(Content::LoadImage("F:/Users/Jaakko/Desktop/Zoro.png"));
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
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ZERO);
		
			_shader->ApplyShader();
			_texture->BindToSampler(0);
			_shader->SetTextureSampler("TextureSampler", 0);

			_buffer2->Bind();
			this->GetGraphicsContext().DrawPrimitives(PrimitiveType::TriangleList, 0, _buffer2->GetVertexCount()); 
		
			_shader->SetParameter("MVP", _camera->GetProjection() * _camera->GetView() * (Matrix::Translate(-20, 0, 0) * Matrix::RotateAroundAxis(Time::GetTotalTime() * 20, Vector3f::UnitZ) * Matrix::Scale(10)));
			_buffer3->Bind();
			this->GetGraphicsContext().DrawPrimitives(PrimitiveType::TriangleList, 0, _buffer3->GetVertexCount());
			glDisable(GL_BLEND);
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