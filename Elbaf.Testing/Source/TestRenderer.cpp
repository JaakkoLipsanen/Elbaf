#include "TestRenderer.h"
#include <Core/Color.h>
#include <Graphics/IVertexBuffer.h>
#include <Graphics/ITexture.h>
#include <Graphics/IShader.h>
#include <Graphics/IDepthState.h>
#include <Graphics/ICullState.h>
#include <Graphics/ShaderSource.h>
#include <algorithm>

#include <Graphics/OpenGL/OGL.h>
#include <Graphics/OpenGL/OGL-Helper.h>
#include <Graphics/VertexFormats.h>
#include "RenderTarget.h"
#include "Vignette.h"
#include "Fog.h"

TestRenderer::TestRenderer(IGraphicsContext& graphicsContext)
	: _graphicsContext(graphicsContext), _postProcessRenderer(graphicsContext)
{
	_shader = graphicsContext.CreateShader(ShaderSource::FromFiles("BasicShader-vs.glsl", "BasicShader-fs.glsl"));
	_postProcessRenderer.AddPostProcess(std::make_shared<FogPostProcess>(_graphicsContext));
	//_postProcessRenderer.AddPostProcess(std::make_shared<VignettePostProcess>(_graphicsContext));
}

TestRenderer::~TestRenderer() = default;
void TestRenderer::AddObject(std::shared_ptr<const RenderObject> renderObject)
{
	_renderObjects.push_back(renderObject);
}

void TestRenderer::SetCamera(ICamera* camera)
{
	_camera = camera;
}

void TestRenderer::PostUpdate()
{
	_postProcessRenderer.Update();
}

void TestRenderer::Render()
{
	_postProcessRenderer.BeginRender();

	// sorting every frame is pretty wasteful.. also std::sort should be fine, but I guess there could be some artifacts/glitches without stable sort..?
	std::stable_sort(_renderObjects.begin(), _renderObjects.end(), [](const std::shared_ptr<const RenderObject>& left, const std::shared_ptr<const RenderObject>& right) { return left->RenderOrder < right->RenderOrder; });
	this->RenderScene();
	
	_postProcessRenderer.Render(_camera);
}

void TestRenderer::RenderScene()
{
	_graphicsContext.Clear(Color::White);
	auto projectionXview = _camera->GetProjection() * _camera->GetView();
	for (auto& renderObject : _renderObjects)
	{
		_graphicsContext.GetDepthState().SetDepthTestEnabled(renderObject->UseDepth);
		_graphicsContext.GetDepthState().SetDepthWriteEnabled(renderObject->UseDepth); //
		_graphicsContext.GetCullState().SetCullingEnabled(renderObject->UseCulling);

		_shader->Bind();
		_shader->SetParameter("MVP", projectionXview * Matrix::Translate(renderObject->Position) * Matrix::Scale(renderObject->Scale));
		_shader->SetParameter("Tint", renderObject->Material->Tint.ToVector3f());

		renderObject->Material->Texture->BindToSampler(0);
		renderObject->Mesh->VertexBuffer->Bind();

		_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, renderObject->Mesh->VertexBuffer->GetVertexCount());
	}
}