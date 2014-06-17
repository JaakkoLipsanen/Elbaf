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

class MyGame : public Game
{
public:
	virtual std::unique_ptr<Scene> CreateDefaultScene() override
	{
		return std::unique_ptr<Scene>(nullptr);
	}

	virtual void Initialize() override
	{
		Logger::MessageStream << "Holy fuck? " << (Vector4f::UnitY + Vector4f::UnitX * 5) << "\n";

		auto x = Vector2i::UnitX * 2;
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
		glm::mat4 Projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);

		// Or, for an ortho camera :
		//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

		// Camera matrix
		glm::mat4 View = glm::lookAt(
			glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
			);
		// Model matrix : an identity matrix (model will be at the origin)
		glm::mat4 Model = glm::mat4(1.0f);
		// Our ModelViewProjection : multiplication of our 3 matrices
		glm::mat4 MVP = Projection * View * Model; // Remember, matrix multiplication is the other way around

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