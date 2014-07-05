#include <Graphics\GraphicsModule.h>

#include <Graphics\CompareFunction.h>
#include <Graphics\IGraphicsContext.h>
#include <Graphics\IGraphicsDevice.h>
#include <Graphics\IDepthState.h>
#include <Graphics\IBlendState.h>
#include <Graphics\ICullState.h>

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

IGameWindow& GraphicsModule::GetGameWindow() const
{
	return _graphicsDevice->GetGameWindow();
}

IGraphicsContext& GraphicsModule::GetGraphicsContext() const
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