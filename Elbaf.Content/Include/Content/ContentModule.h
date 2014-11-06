#pragma once
#include <Core/IModule.h>
#include <memory>
#include <string>
#include <Graphics/Image.h>
#include <Graphics/Texture.h>
#include <Graphics/Font.h>
#include <Graphics/GraphicsContext.h>

// todo: ContentManager
class ContentModule : public IModule
{
public:
	explicit ContentModule(IEngine& engine);
	~ContentModule();

	virtual void Initialize() override;
	virtual void Terminate() override;

 // ContentManager& GetDefaultManager() { .. }

	// move to ContentManager
	std::unique_ptr<Image> LoadImage(const std::string& filePath);
	std::unique_ptr<Texture2D> LoadTexture(const std::string& filePath); // todo: additional parameters?
	std::unique_ptr<Font> LoadFont(GraphicsContext& graphicsContext, const std::string& fontPath, int fontSize);

private:
	struct Data;
	std::unique_ptr<Data> _pData;
};