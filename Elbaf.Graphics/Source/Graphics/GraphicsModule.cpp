#include <Graphics\GraphicsModule.h>

#include <Graphics\CompareFunction.h>
#include <Graphics\GraphicsContext.h>
#include <Graphics\IGraphicsDevice.h>
#include <Graphics\DepthState.h>
#include <Graphics\BlendState.h>
#include <Graphics\CullState.h>

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

	auto& depthState = context.GetDepthState();
	depthState.SetDepthTestEnabled(true);
	depthState.SetDepthFunction(CompareFunction::Less);

	auto& cullState = context.GetCullState();
	cullState.SetCullingEnabled(true);
	cullState.SetCullFace(CullFace::Back);
	cullState.SetCullMode(CullMode::CounterClockwise);

	auto& blendState = context.GetBlendState();
	blendState.SetBlendEnabled(true);
	blendState.SetSourceBlend(BlendFactor::SourceAlpha);
	blendState.SetDestinationBlend(BlendFactor::OneMinusSourceAlpha);
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

std::unique_ptr<const IMonitor> GraphicsModule::GetPrimaryMonitor() const
{
	return _graphicsDevice->GetPrimaryMonitor();
}

std::vector<std::unique_ptr<const IMonitor>> GraphicsModule::GetAllMonitors() const
{
	return _graphicsDevice->GetAllMonitors();
}

IGameWindow& GraphicsModule::GetGameWindow() const
{
	return _graphicsDevice->GetGameWindow();
}

GraphicsContext& GraphicsModule::GetGraphicsContext() const
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