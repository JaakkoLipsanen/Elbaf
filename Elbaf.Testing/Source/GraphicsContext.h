#pragma once
#include <Graphics\ITexture.h>
#include <Graphics\IVertexBuffer.h>
#include <Graphics\IShader.h>

class GraphicsContext
{
	std::shared_ptr<ITexture2D> CreateTexture(std::unique_ptr<Image> textureData);
	std::shared_ptr<IVertexBuffer> CreateVertexBuffer();

	std::shared_ptr<IShader> CreateShader();
};


/*

- GraphicsModule
	- GraphicsDevice
		- GraphicsContext
*/