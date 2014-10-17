#pragma once
#include <Graphics/IGraphicsContext.h>
#include <Math/Vector.h>
#include <Math/FlaiMath.h>
#include <Engine/Time.h>
#include <Renderer.h>
#include <Graphics/IVertexBuffer.h>
#include <Core/Array.h>
#include <Core/Global.h>

class FloatingCube
{
public:
	explicit FloatingCube(IGraphicsContext& graphicsContext, Vector3f position, Vector3f scale) :
		_graphicsContext(graphicsContext), _initialPosition(position), _position(position), _scale(scale), _timeOffset(Global::Random.NextFloat(0, 1000)), _floatingSpeedMultiplier(Global::Random.NextFloat(0.5f, 1.1f)), _floatingScaleMultiplier(Global::Random.NextFloat(0.8f, 1.2f))
	{	
	}

	void Update()
	{
		// floating cube floats up and down in a sin "curve"
		_position = _initialPosition + Vector3f::UnitY * FlaiMath::Sin(_timeOffset + Time::GetTotalTime() * _floatingSpeedMultiplier) * _scale.Y * 0.5f * _floatingScaleMultiplier;
		_renderObject->Position = _position;
	}

	void SetRenderHandle(std::shared_ptr<RenderObject> renderObject)
	{
		_renderObject = renderObject;
		_renderObject->Scale = _scale;
		_renderObject->Position = _position;
	}

	static std::shared_ptr<Mesh> CreateMesh(IGraphicsContext& graphicsContext)
	{
		typedef VertexPositionColorNormal Vertex;

		Color baseColor = Color::White;
		static const VertexPositionColorTextureNormal cubeVertexData[] = {
			// front
			VertexPositionColorTextureNormal({ -1.0f, -1.0f, -1.0f }, baseColor, Vector2f(0, 1), Vector3f::UnitZ), // BL
			VertexPositionColorTextureNormal({ -1.0f, 1.0f, -1.0f }, baseColor, Vector2f(0, 2), Vector3f::UnitZ), // TL
			VertexPositionColorTextureNormal({ 1, -1, -1.0f }, baseColor, Vector2f(1, 1), Vector3f::UnitZ), // BR

			VertexPositionColorTextureNormal({ -1.0f, 1.0f, -1.0f }, baseColor, Vector2f(0, 2), Vector3f::UnitZ), // TL
			VertexPositionColorTextureNormal({ 1.0f, 1.0f, -1.0f }, baseColor, Vector2f(1, 2), Vector3f::UnitZ), // TR
			VertexPositionColorTextureNormal({ 1, -1, -1.0f }, baseColor, Vector2f(1, 1), Vector3f::UnitZ), // BR

			// back
			VertexPositionColorTextureNormal({ 1.0f, -1.0f, 1 }, baseColor, Vector2f(2, 1), -Vector3f::UnitZ), // BL
			VertexPositionColorTextureNormal({ 1.0f, 1.0f, 1 }, baseColor, Vector2f(2, 2), -Vector3f::UnitZ), // TL
			VertexPositionColorTextureNormal({ -1, -1, 1 }, baseColor, Vector2f(3, 1), -Vector3f::UnitZ), // BR

			VertexPositionColorTextureNormal({ 1.0f, 1.0f, 1 }, baseColor, Vector2f(2, 2), -Vector3f::UnitZ), // TL
			VertexPositionColorTextureNormal({ -1, 1, 1 }, baseColor, Vector2f(3, 2), -Vector3f::UnitZ), // TR
			VertexPositionColorTextureNormal({ -1, -1, 1 }, baseColor, Vector2f(3, 1), -Vector3f::UnitZ), // BR

			// left
			VertexPositionColorTextureNormal({ 1.0f, -1.0f, -1 }, baseColor, Vector2f(1, 1), -Vector3f::UnitX), // BL
			VertexPositionColorTextureNormal({ 1.0f, 1.0f, -1 }, baseColor, Vector2f(1, 2), -Vector3f::UnitX), // TL
			VertexPositionColorTextureNormal({ 1.0f, -1, 1 }, baseColor, Vector2f(2, 1), -Vector3f::UnitX), // BR

			VertexPositionColorTextureNormal({ 1.0f, 1.0f, -1 }, baseColor, Vector2f(1, 2), -Vector3f::UnitX), // TL
			VertexPositionColorTextureNormal({ 1.0f, 1, 1 }, baseColor, Vector2f(2, 2), -Vector3f::UnitX), // TR
			VertexPositionColorTextureNormal({ 1.0f, -1, 1 }, baseColor, Vector2f(2, 1), -Vector3f::UnitX), // BR

			// right
			VertexPositionColorTextureNormal({ -1.0f, 1.0f, -1 }, baseColor, Vector2f(4, 2), Vector3f::UnitX), // TL
			VertexPositionColorTextureNormal({ -1.0f, -1.0f, -1 }, baseColor, Vector2f(4, 1), Vector3f::UnitX), // BL
			VertexPositionColorTextureNormal({ -1.0f, -1, 1 }, baseColor, Vector2f(3, 1), Vector3f::UnitX), // BR

			VertexPositionColorTextureNormal({ -1.0f, 1, 1 }, baseColor, Vector2f(3, 2), Vector3f::UnitX), // TR
			VertexPositionColorTextureNormal({ -1.0f, 1.0f, -1 }, baseColor, Vector2f(4, 2), Vector3f::UnitX), // TL
			VertexPositionColorTextureNormal({ -1.0f, -1, 1 }, baseColor, Vector2f(3, 1), Vector3f::UnitX), // BR

			// top
			VertexPositionColorTextureNormal({ -1.0f, 1.0f, -1 }, baseColor, Vector2f(1, 3), Vector3f::UnitY), // BL
			VertexPositionColorTextureNormal({ -1.0f, 1.0f, 1 }, baseColor, Vector2f(2, 3), Vector3f::UnitY), // TR
			VertexPositionColorTextureNormal({ 1.0f, 1, -1 }, baseColor, Vector2f(1, 2), Vector3f::UnitY), // BR

			VertexPositionColorTextureNormal({ -1.0f, 1.0f, 1 }, Color::White, Vector2f(2, 3), Vector3f::UnitY), // TR
			VertexPositionColorTextureNormal({ 1.0f, 1, 1 }, baseColor, Vector2f(2, 2), Vector3f::UnitY), // TR
			VertexPositionColorTextureNormal({ 1.0f, 1, -1 }, baseColor, Vector2f(1, 2), Vector3f::UnitY), // BR

			// bottom
			VertexPositionColorTextureNormal({ -1.0f, -1.0f, 1 }, baseColor, Vector2f(2, 0), -Vector3f::UnitY), // TR
			VertexPositionColorTextureNormal({ -1.0f, -1.0f, -1 }, baseColor, Vector2f(1, 0), -Vector3f::UnitY), // BL
			VertexPositionColorTextureNormal({ 1.0f, -1, -1 }, baseColor, Vector2f(1, 1), -Vector3f::UnitY), // BR

			VertexPositionColorTextureNormal({ 1.0f, -1, 1 }, baseColor, Vector2f(2, 1), -Vector3f::UnitY), // TR
			VertexPositionColorTextureNormal({ -1.0f, -1.0f, 1 }, baseColor, Vector2f(2, 0), -Vector3f::UnitY), // TR
			VertexPositionColorTextureNormal({ 1.0f, -1, -1 }, baseColor, Vector2f(1, 1), -Vector3f::UnitY), // BR
		};


		std::shared_ptr<IVertexBuffer> vertexBuffer(graphicsContext.CreateVertexBuffer(BufferType::Static).release());
		vertexBuffer->SetVertexData(cubeVertexData, Array::Length(cubeVertexData));

		return std::make_shared<Mesh>(vertexBuffer);
	}

private:
	IGraphicsContext& _graphicsContext;
	Vector3f _initialPosition;
	Vector3f _position;
	Vector3f _scale;
	float _timeOffset;
	float _floatingSpeedMultiplier;
	float _floatingScaleMultiplier;
	std::shared_ptr<RenderObject> _renderObject;
};