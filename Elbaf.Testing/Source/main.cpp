#include <iostream>
#include <Engine\Game.h>
#include <Graphics\IVertexBuffer.h>
#include <Core\Diagnostics\Logger.h>
#include <Engine\Screen.h>
#include <Input\Mouse.h>
#include <Graphics\IGraphicsDevice.h>
#include <Graphics\VertexFormats.h>
#include <Graphics\IShader.h>
#include <Input\Input.h>
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\PrimitiveType.h>
#include <glm\gtc\matrix_transform.hpp>
#include <Engine\Time.h>

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
		Mouse::SetCursorVisibility(CursorVisibility::Visible);
		Mouse::SetPosition({ Screen::GetWidth() / 2, Screen::GetHeight() / 2 });
		this->GetGraphicsDevice()->SetCullMode(CullMode::Clockwise);

		static const VertexPosition vertexData[] = {
			VertexPosition({ 0.5f, -0.5f, 0 }),
			VertexPosition({ 0.1f, -0.5f, 0 }),
			VertexPosition({ 0, 0, 0.0f }) };

		static const VertexPositionColor vertexData2[] = {
			VertexPositionColor({ -1.0f, 0.0f, 0 }, Color::Red),
			VertexPositionColor({ 0, 1.0f, 0 }, Color::Green),
			VertexPositionColor({ 1, 0, 0.0f }, Color::Blue) };


		_buffer = IVertexBuffer::CreateVertexBuffer(vertexData, 3);
		_buffer2 = IVertexBuffer::CreateVertexBuffer<VertexPositionColor>(vertexData2, 3);
		_shader = IShader::Load("BasicShader-vs.glsl", "BasicShader-fs.glsl");

		// better name for "ApplyShader"? Bind? BindShader? Use? UseShader? SetActive?
		_shader->ApplyShader();
		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		//auto Projection =  Matrix::CreateOrtographic(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);

		// Or, for an ortho camera :
		auto Projection = Matrix::CreatePerspective(50 + Time::GetTotalTime() * 10.0f, 16.0f / 9, 0.1f, 100);

		// Camera matrix
		Matrix4x4 View = Matrix::CreateLookAt(
			Vector3f(4, 3, 3),
			Vector3f::Zero,
			Vector3f::UnitY);

		auto Model = Matrix4x4::Identity;
		auto MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

		_shader->SetValue("MVP", MVP);
	}

	virtual void PreRender() override
	{
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

		if (Input::IsNewMouseButtonPress(MouseButton::Right))
		{
			this->GetGraphicsDevice()->ChangeResolution({ 1920, 1080 });
		}
	}

private:
	GLuint _vertexArrayID;
	GLuint _vertexBufferID;
	std::unique_ptr<IShader> _shader;
	std::unique_ptr<IVertexBuffer> _buffer;
	std::unique_ptr<IVertexBuffer> _buffer2;
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