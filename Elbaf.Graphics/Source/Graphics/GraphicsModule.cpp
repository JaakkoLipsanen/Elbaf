#include <Graphics\GraphicsModule.h>
#include <Graphics\OpenGL\GraphicsContext.h>
#include <Diagnostics\Logger.h>
#include <Core\IGameWindow.h>
#include <Math\Size.h>
#include <Graphics\OpenGL\GameWindow.h>
#include <Diagnostics\Ensure.h>
#include <Graphics\CompareFunction.h>
#include <vector>
#include <Core\Event.h>
#include <Graphics\IGraphicsContext.h>
#include <Graphics\OpenGL\GraphicsDevice.h>
#include <Core\WindowDescription.h>


/*

this->Device->SetDepthTestEnabled(true);
this->Device->SetDepthFunction(CompareFunction::Less);
this->Device->SetCullingEnabled(true);
this->Device->SetCullFace(CullFace::Back);
this->Device->SetCullMode(CullMode::CounterClockwise);


*/
	

GraphicsModule::GraphicsModule(IEngine& engine, const WindowDescription& windowDescription) : IModule(engine)
{
	_graphicsDevice = std::unique_ptr<OGL::GraphicsDevice>(new OGL::GraphicsDevice);
	_graphicsDevice->OpenWindow(windowDescription);
}
GraphicsModule::~GraphicsModule() = default;

void GraphicsModule::Initialize()
{	
	auto& context = _graphicsDevice->GetContext();
	context.SetDepthTestEnabled(true);
	context.SetDepthFunction(CompareFunction::Less);
	context.SetCullingEnabled(true);
	context.SetCullFace(CullFace::Back);
	context.SetCullMode(CullMode::CounterClockwise);
}

void GraphicsModule::Terminate()
{
	_graphicsDevice->Terminate();
}

IGameWindow* GraphicsModule::GetGameWindow() const
{
	return &_graphicsDevice->GetGameWindow();
}

void GraphicsModule::EndFrame()
{
	_graphicsDevice->EndFrame();
}

IGraphicsContext* GraphicsModule::GetGraphicsDevice() const
{
	return &_graphicsDevice->GetContext();
}

/*

- GraphicsModule
	- GraphicsDevice
		- GraphicsContext


*/