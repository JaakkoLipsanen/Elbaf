#include <iostream>

#include "DefaultCamera.h"
#include <Engine\Game.h>
#include <Diagnostics\Logger.h>
#include <Engine\Screen.h>
#include <Input\Mouse.h>
#include <Graphics\IGraphicsDevice.h>
#include <Graphics\VertexFormats.h>
#include <Graphics\IVertexBuffer.h>
#include <Graphics\IShader.h>
#include <Engine\Time.h>
#include <Input\Input.h>
#include <Graphics\OpenGL\OGL.h>
#include <Core\Random.h>
#include <algorithm>
#include <Core\Global.h>
#include "ImageLoader.h"

class ITexture
{
	static std::unique_ptr<ITexture> Load(const std::string& texturePath);
	virtual ~ITexture() { }

	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;

	Size GetSize() const { return Size(this->GetWidth(), this->GetHeight()); }

	virtual void Bind() = 0;
	// TextureFormat?
	// void SetData?
	// bool HasMipMaps?
	// void GenerateMipMaps?

	// void Dispose()? if I do this, then "IGraphicsResource" would be useful (has Dispose and maybe IsDisposed)
};

class Texture
{
public:
	static Texture* Load(const std::string& texturePath)
	{
	}


	virtual ~Texture()
	{
		glDeleteTextures(1, &_textureID);
	}

private:
	GLuint _textureID;
};

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
			VertexPositionColorTexture({ -1.0f, -1.0f, 0 }, Color::Transparent, Vector2f::Zero),
			VertexPositionColorTexture({ -1.0f, 1.0f, 0 }, Color::Transparent, Vector2f(0, 1)),
			VertexPositionColorTexture({ 1, -1, 0.0f }, Color::Transparent, Vector2f(1, 0)),
		
			VertexPositionColorTexture({ -1.0f, 1.0f, 0 }, Color::Transparent, Vector2f(0, 1)),
			VertexPositionColorTexture({ 1.0f, 1.0f, 0 }, Color::Transparent, Vector2f(1, 1)),
			VertexPositionColorTexture({ 1, -1, 0.0f }, Color::Transparent, Vector2f(1, 0)),
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

		


		_buffer3 = IVertexBuffer::CreateVertexBuffer(vertexData3, 6);
		_buffer2 = IVertexBuffer::CreateVertexBuffer(vertexDataNew.data(), vertexDataNew.size());

		_buffer = IVertexBuffer::CreateVertexBuffer(vertexDataNew.data(), 3);
		_shader = IShader::Load("BasicShader-vs.glsl", "BasicShader-fs.glsl");
		_camera = std::unique_ptr<DefaultCamera>(new DefaultCamera);

		int width, height;

		_textureID = LoadTexture("F:/Users/Jaakko/Desktop/Sanji.png", &width, &height);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _textureID);
		_shader->SetTextureSampler("TextureSampler", 0);


		Logger::MessageStream << width << " " << height << "\n";
	}
	GLuint _textureID;
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

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
			_shader->ApplyShader();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _textureID);
			_shader->SetTextureSampler("TextureSampler", 0);

			
		/*	_buffer->Bind(); // GraphicsDevice.SetVertexBuffer?
			this->GetGraphicsDevice()->DrawPrimitives(PrimitiveType::TriangleList, 0, _buffer->GetVertexCount()); */

			_buffer2->Bind();
			this->GetGraphicsDevice()->DrawPrimitives(PrimitiveType::TriangleList, 0, _buffer2->GetVertexCount()); 
		
			_shader->SetParameter("MVP", _camera->GetProjection() * _camera->GetView() * Matrix::Scale(10));
			_buffer3->Bind();
			this->GetGraphicsDevice()->DrawPrimitives(PrimitiveType::TriangleList, 0, _buffer3->GetVertexCount());
			glDisable(GL_BLEND);
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
	std::unique_ptr<IVertexBuffer> _buffer3;
	std::unique_ptr<DefaultCamera> _camera;
};

int main()
{
	MyGame game;
	game.Run();

	return 1;
}