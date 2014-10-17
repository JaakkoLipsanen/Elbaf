#include <Content/ContentModule.h>
#include <Diagnostics/Logger.h>
#include <Content/PNG-Loader.h>
#include <Core/IEngine.h>
#include <Graphics/GraphicsModule.h>
#include <Content/FontLoader.h>
#include <Graphics/GraphicsContext.h>

struct ContentModule::Data
{
	FontLoader FontLoader;
};

ContentModule::ContentModule(IEngine& engine)
	: IModule(engine)
{
}
ContentModule::~ContentModule() = default;

void ContentModule::Initialize()
{
	_pData.reset(new Data());
}
void ContentModule::Terminate() { }

std::unique_ptr<Image> ContentModule::LoadImage(std::string const& filePath)
{
	TextureFormat textureFormat;
	void* data = nullptr;
	int width, height;
	if (!Content::ReadPNG(filePath, &width, &height, &textureFormat, &data)) // todo: check file extension for other types?
	{
		Logger::LogError("Error loading texture (" + filePath + "): Could not load the texture");
		free(data); // free the data, in case anything was allocated into it (lets hope that it wasn't already freed :P )
		return std::unique_ptr<Image>(nullptr);
	}

	return std::unique_ptr<Image>(new Image(data, width, height, textureFormat));
}

std::unique_ptr<Texture2D> ContentModule::LoadTexture(std::string const& filePath)
{
	return _engine.GetInstance().GetModule<GraphicsModule>().GetGraphicsContext().CreateTexture2D(*this->LoadImage(filePath).get());
}

std::unique_ptr<Font> ContentModule::LoadFont(GraphicsContext& graphicsContext, std::string const& fontPath, int fontSize)
{
	return _pData->FontLoader.LoadFont(graphicsContext, fontPath, fontSize);
}