#include "TestRenderer.h"
#include <Core/Color.h>
#include <Graphics/IVertexBuffer.h>
#include <Graphics/ITexture.h>
#include <Graphics/IShader.h>
#include <Graphics/IDepthState.h>
#include <Graphics/ICullState.h>
#include <Graphics/ShaderSource.h>
#include <algorithm>

TestRenderer::TestRenderer(IGraphicsContext& graphicsContext)
	: _graphicsContext(graphicsContext)
{
	_shader = graphicsContext.CreateShader(ShaderSource::FromFiles("BasicShader-vs.glsl", "BasicShader-fs.glsl"));
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
}

void TestRenderer::Render()
{
	// sorting every frame is pretty wasteful.. also std::sort should be fine, but I guess there could be some artifacts/glitches without stable sort..?
	std::stable_sort(_renderObjects.begin(), _renderObjects.end(), [](const std::shared_ptr<const RenderObject>& left, const std::shared_ptr<const RenderObject>& right) { return left->RenderOrder < right->RenderOrder; });
	_graphicsContext.Clear(Color::DodgerBlue);
	this->RenderScene();
}

void TestRenderer::RenderScene()
{
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