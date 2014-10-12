#pragma once
#include <Core/Global.h>
#include "TestRenderer.h"
#include <Core/Color.h>
#include <Graphics/VertexFormats.h>
#include <Graphics/IVertexBuffer.h>
#include "NoiseGen.h"
#include <Core/Array.h>

class Skybox
{
public:

	Skybox(IGraphicsContext& graphicsContext) :
		_graphicsContext(graphicsContext)
	{
	}

	std::shared_ptr<Mesh> Mesh;
	void Generate()
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

		std::shared_ptr<IVertexBuffer> x(_graphicsContext.CreateVertexBuffer(BufferType::Static).release());
		this->Mesh.reset(new ::Mesh(x));
		this->Mesh->VertexBuffer->SetVertexData(skyboxVertexData, Array::Length(skyboxVertexData));
	}

private:
	IGraphicsContext& _graphicsContext;
};