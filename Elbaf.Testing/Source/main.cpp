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

class MyGame : public Game
{
public:

	virtual std::unique_ptr<Scene> CreateDefaultScene() override
	{
		return std::unique_ptr<Scene>(nullptr);
	}

	std::unique_ptr<IVertexBuffer> _buffer;
	std::unique_ptr<IVertexBuffer> _buffer2;
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
	}

	virtual void PreRender() override
	{
		this->GetGraphicsDevice()->Clear(Color::RoyalBlue);
		if (Input::IsMouseButtonPressed(MouseButton::Left) || true)
		{
			_shader->ApplyShader();
			_buffer->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);

			_buffer2->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);

		}

		if (Input::GetScrollWheelDelta() != 0)
		{
			Logger::LogMessage(Input::GetScrollWheelDelta());
		}


		if (Input::IsNewMouseButtonPress(MouseButton::Right))
		{
			this->GetGraphicsDevice()->ChangeResolution({ 1920, 1080 });
		}

		//Logger::LogMessage(Time::GetTotalTime());
	}

private:
	GLuint _vertexArrayID;
	GLuint _vertexBufferID;
	std::unique_ptr<IShader> _shader;
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