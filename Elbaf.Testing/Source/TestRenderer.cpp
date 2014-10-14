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
#include "Post Processing/Vignette.h"
#include "Post Processing/Fog.h"
#include "Post Processing/Pixelizer.h"
#include <Post Processing/GaussianBlur.h>

TestRenderer::TestRenderer(IGraphicsContext& graphicsContext)
	: _graphicsContext(graphicsContext), _postProcessRenderer(graphicsContext)
{
	_terrainShader = graphicsContext.CreateShader(ShaderSource::FromFiles("Shaders/TerrainShader-vs.glsl", "Shaders/TerrainShader-fs.glsl"));
	_normalShader = graphicsContext.CreateShader(ShaderSource::FromFiles("Shaders/DefaultShader-vs.glsl", "Shaders/DefaultShader-fs.glsl"));

	_terrainShader->Bind();
	_terrainShader->SetParameter("LightDirection", Vector::Normalize(Vector3f(0, -1, -0)));

	_normalShader->Bind(); 
	_normalShader->SetTextureSampler("TextureSampler", 0);
	_normalShader->SetParameter("AmbientLightAmount", 0.15f);
	_normalShader->SetParameter("LightCount", 2);
	_normalShader->SetParameter("Lights[0].Direction", Vector::Normalize(Vector3f(0.2f, -1, -0.5f)));
	_normalShader->SetParameter("Lights[0].Power", 0.7f);
	_normalShader->SetParameter("Lights[1].Direction", Vector::Normalize(Vector3f(-0.3f, 0.4f, 0.2f)));
	_normalShader->SetParameter("Lights[1].Power", 0.8f);

	_postProcessRenderer.AddPostProcess(std::make_shared<FogPostProcess>(_graphicsContext));
	_postProcessRenderer.AddPostProcess(std::make_shared<VignettePostProcess>(_graphicsContext));
	_postProcessRenderer.AddPostProcess(std::make_shared<PixelizerPostProcess>(_graphicsContext))->SetEnabled(false);
	_postProcessRenderer.AddPostProcess(std::make_shared<GaussianBlurPostProcess>(_graphicsContext));
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

		auto& shader = this->GetShader(renderObject->Material->MaterialType);
		shader.Bind();
		shader.SetParameter("MVP", projectionXview * Matrix::Translate(renderObject->Position) * Matrix::Scale(renderObject->Scale));
		shader.SetParameter("Tint", renderObject->Material->Tint.ToVector3f());

		renderObject->Material->Texture->BindToSampler(0);
		renderObject->Mesh->VertexBuffer->Bind();

		_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, renderObject->Mesh->VertexBuffer->GetVertexCount());
	}
}

IShader& TestRenderer::GetShader(MaterialType materialType)
{
	return (materialType == MaterialType::Terrain) ? *_terrainShader : *_normalShader;
}