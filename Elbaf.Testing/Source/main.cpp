#include <iostream>

#include "DefaultCamera.h"
#include <Engine\Game.h>
#include <Core\Diagnostics\Logger.h>
#include <Engine\Screen.h>
#include <Input\Mouse.h>
#include <Graphics\IGraphicsDevice.h>
#include <Graphics\VertexFormats.h>
#include <Graphics\IVertexBuffer.h>
#include <Graphics\IShader.h>
#include <Engine\Time.h>
#include <Input\Input.h>
#include <Graphics\OpenGL\OGL.h>

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

		std::vector<VertexPositionColor> vertexDataNew;

		const int Size = 300;
		float grid[(Size + 1) * (Size + 1)];

		for (int y = 0; y < Size + 1; y++)
		{
			for (int x = 0; x < Size + 1; x++)
			{
				grid[x + y * Size] = RandomFloat(0, 1);
			}
		}

		for (int y = 0; y < Size; y++)
		{
			for (int x = 0; x < Size; x++)
			{
				VertexPositionColor bl({ x, grid[x + y * Size], y }, Color::Brown);
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

		_buffer2 = IVertexBuffer::CreateVertexBuffer(vertexDataNew.data(), vertexDataNew.size());
		_buffer2->SetVertexData(vertexDataNew.data(), vertexDataNew.size());

		_buffer = IVertexBuffer::CreateVertexBuffer(vertexDataNew.data(), 3);
		_shader = IShader::Load("BasicShader-vs.glsl", "BasicShader-fs.glsl");
		_camera = std::unique_ptr<DefaultCamera>(new DefaultCamera);
	}

	float RandomFloat(float a, float b) {
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = b - a;
		float r = random * diff;
		return a + r;
	}

	virtual void PreRender() override
	{
		_camera->Update();
		_shader->SetParameter("MVP", _camera->GetProjection() * _camera->GetView());
		if (Input::IsMouseButtonPressed(MouseButton::Right))
		{
			static const VertexPosition vertexData[] = {
				VertexPosition({ 0.5f, -0.5f, 0 }),
				VertexPosition({ 0.1f, -0.5f, 0 }),
				VertexPosition({ 0, 0, 0.0f }) };

			_buffer2->SetVertexData(vertexData, 3);
		}

		this->GetGraphicsDevice()->Clear(Color::RoyalBlue);
		if (Input::IsMouseButtonPressed(MouseButton::Left) || true)
		{
			_shader->ApplyShader();
			
			_buffer->Bind(); // GraphicsDevice.SetVertexBuffer?
			this->GetGraphicsDevice()->DrawPrimitives(PrimitiveType::TriangleList, 0, _buffer->GetVertexCount());

			_buffer2->Bind();
			this->GetGraphicsDevice()->DrawPrimitives(PrimitiveType::TriangleList, 0, _buffer2->GetVertexCount());
		}

		if (Input::GetScrollWheelDelta() != 0)
		{
			Logger::LogMessage(Input::GetScrollWheelDelta());
		}
	}

private:
	std::unique_ptr<IShader> _shader;
	std::unique_ptr<IVertexBuffer> _buffer;
	std::unique_ptr<IVertexBuffer> _buffer2;
	std::unique_ptr<DefaultCamera> _camera;
};

int main()
{
	MyGame game;
	game.Run();

	/*Engine engine;
	engine.SetClearColor(Color::Red);
	engine.GetWindow().SetTitle("My Game");
	engine.GetGraphicsDevice().SetResolution(1920, 1080); */

	return 1;
}