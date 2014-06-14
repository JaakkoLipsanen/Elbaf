#include <iostream>
#include <Math\Fundamental.h>
#include <Core\IGameWindow.h>
#include <Core\Color.h>
#include <Engine\Game.h>
#include <Graphics\IGraphicsDevice.h>
#include <Core\Diagnostics\Logger.h>
#include <Input\Input.h>
#include <Engine\TimeModule.h>
#include <Engine\Time.h>

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "ShaderLoader.h"
#include "Engine\Screen.h"
#include "Input\Mouse.h"

struct Shader
{
	void ApplyShader()
	{
		glUseProgram(_programID);
	}

	static std::unique_ptr<Shader> Load(const std::string& vertexFilePath, const std::string& fragmentFilePath)
	{
		GLuint programID = LoadShaders(vertexFilePath, fragmentFilePath);
		return std::unique_ptr<Shader>(new Shader(programID));
	}

	virtual ~Shader()
	{
		glDeleteProgram(_programID);
	}
	
private:
	Shader(GLuint id) : _programID(id) { }
	GLuint _programID;
};

struct VertexPosition
{
	Vector3f Position;
	VertexPosition(Vector3f position) : Position(position)
	{}
};

struct VertexBuffer
{
	// todo: need to  figure out a way to describe vertex data... probably can just copy the xna way?
	template<typename Vertex>
	static std::unique_ptr<VertexBuffer> CreateVertexBuffer(const Vertex* vertexData, int vertexCount)
	{
		GLuint vertexArrayID;
		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);
		
		GLuint vertexBufferID;
		glGenBuffers(1, &vertexBufferID);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertexData, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0, // attribute 0
			3, // size (pos = 3)
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			reinterpret_cast<void*>(offsetof(Vertex, Position)));

		// glDisableVertexAttribArray(0) ?
		glBindVertexArray(0); // "reset" vertex array to 'nothing'. I dont think this is necessary, remove it after testing a bit
		return std::unique_ptr<VertexBuffer>(new VertexBuffer(vertexArrayID, vertexBufferID));
	}

	void Bind()
	{
		glBindVertexArray(_vertexArrayID);
	}

	virtual ~VertexBuffer()
	{
		glDeleteBuffers(1, &_vertexBufferID);
		glDeleteVertexArrays(1, &_vertexArrayID);
	}

private:
	VertexBuffer(GLuint vertexArrayID, GLuint vertexBufferID) : _vertexArrayID(vertexArrayID), _vertexBufferID(vertexBufferID) { }
	GLuint _vertexArrayID;
	GLuint _vertexBufferID;
};


class MyGame : public Game
{
public:
	
	virtual std::unique_ptr<Scene> CreateDefaultScene() override
	{
		return std::unique_ptr<Scene>(nullptr);
	}

	std::unique_ptr<VertexBuffer> _buffer;
	virtual void Initialize() override
	{
		Logger::LogMessage(Screen::GetSize());
		Mouse::SetCursorVisibility(CursorVisibility::Visible);
		Mouse::SetPosition({ Screen::GetWidth() / 2, Screen::GetHeight() / 2 });
		this->GetGraphicsDevice()->SetCullMode(CullMode::Clockwise);

		static const VertexPosition vertexData[] = { 
			VertexPosition({ -1, -1, 0 }),
			VertexPosition({ 1, -1, 0 }), 
			VertexPosition({ 0, 0, 0.0f }) };

		_buffer = VertexBuffer::CreateVertexBuffer<VertexPosition>(vertexData, 3);
		_shader = Shader::Load("BasicShader-vs.glsl", "BasicShader-fs.glsl");
	}

	virtual void PreRender() override
	{
		this->GetGraphicsDevice()->Clear(Color::RoyalBlue);
		if (Input::IsMouseButtonPressed(MouseButton::Left) || true)
		{
			_shader->ApplyShader();
			_buffer->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);

			auto x = this->GetGraphicsDevice();

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
	std::unique_ptr<Shader> _shader;
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