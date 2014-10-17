#pragma once
#include <memory>
#include <Math\Size.h>

struct Image;
class ITexture
{
public:
	
	virtual void Bind() = 0;
	virtual void BindToSampler(unsigned int samplerIndex) = 0;
	virtual ~ITexture() { }

	// TextureFormat?
	// void SetData?
	// bool HasMipMaps?
	// void GenerateMipMaps?

	// void Dispose()? if I do this, then "IGraphicsResource" would be useful (has Dispose and maybe IsDisposed)
};

class Texture2D : public ITexture
{
public:
	Size GetSize() const;
	virtual int GetWidth() const = 0;
	virtual int GetHeight() const = 0;

	virtual ~Texture2D() override { }
};