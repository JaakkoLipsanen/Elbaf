#pragma once
#include <Graphics/Texture.h>
#include <vector>

class RenderTarget
{
public:
	virtual ~RenderTarget() = default;
	virtual bool HasDepthTexture() const = 0;
	virtual int GetColorTextureCount() const = 0;

	virtual Texture2D& GetColorTexture(uint index) = 0;
	virtual Texture2D& GetDepthTexture() = 0;

	// !!! I'm pretty sure that you can make a framebuffer which has different size of channels/color textures inside it... but I dont think it's very common, so for now lets imagine that all of them have same size */
	virtual Size GetSize() const = 0;
	
protected:
	RenderTarget() = default;
};