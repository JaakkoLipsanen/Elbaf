#include <Graphics\GraphicsModule.h>

#include <Graphics\CompareFunction.h>
#include <Graphics\IGraphicsContext.h>
#include <Graphics\IGraphicsDevice.h>

static IGraphicsDevice* CreateGraphicsDevice();
GraphicsModule::GraphicsModule(IEngine& engine, const WindowDescription& windowDescription) : IModule(engine)
{
	_graphicsDevice = std::unique_ptr<IGraphicsDevice>(CreateGraphicsDevice());
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

void GraphicsModule::RunMessagePump()
{
	_graphicsDevice->RunMessagePump();
}

void GraphicsModule::EndFrame()
{
	_graphicsDevice->EndFrame();
}

void GraphicsModule::Terminate()
{
	_graphicsDevice->Terminate();
}

IGameWindow& GraphicsModule::GetGameWindow() const
{
	return _graphicsDevice->GetGameWindow();
}

IGraphicsContext& GraphicsModule::GetGraphicsDevice() const
{
	return _graphicsDevice->GetContext();
}

#if OPENGL
#include <Graphics\OpenGL\GraphicsDevice.h>
static IGraphicsDevice* CreateGraphicsDevice()
{
	return new OGL::GraphicsDevice;
}
#endif