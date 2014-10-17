#include <Content/Content.h>
#include <Content/ContentModule.h>
#include <Core/IEngine.h>

ContentModule& GetContentModule()
{
	return IEngine::GetInstance().GetModule<ContentModule>();
}

std::unique_ptr<Image> Content::LoadImage(std::string const& filePath)
{
	return GetContentModule().LoadImage(filePath);
}

std::unique_ptr<Texture2D> Content::LoadTexture(std::string const& filePath)
{
	return GetContentModule().LoadTexture(filePath);
}

std::unique_ptr<Font> Content::LoadFont(GraphicsContext& graphicsContext, std::string const& fontPath, int fontSize)
{
	return GetContentModule().LoadFont(graphicsContext, fontPath, fontSize);
}