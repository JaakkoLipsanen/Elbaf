#include "Renderer.h"
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
#include <Post Processing/DepthOfField.h>
#include <Post Processing/ColorAdjust.h>
#include <Engine/Time.h>
#include <Post Processing/SSAO.h>
#include <glm/gtc/matrix_transform.inl>

Matrix4x4 GetShadowMVP();
Renderer::Renderer(IGraphicsContext& graphicsContext)
	: _graphicsContext(graphicsContext), _postProcessRenderer(graphicsContext), _directionalLight(Vector::Normalize(Vector3f(0.2f, -1.f, -0.5f)))
{
	_terrainShader = graphicsContext.CreateShader(ShaderSource::FromFiles("Shaders/TerrainShader-vs.glsl", "Shaders/TerrainShader-fs.glsl"));
	_normalShader = graphicsContext.CreateShader(ShaderSource::FromFiles("Shaders/DefaultShader-vs.glsl", "Shaders/DefaultShader-fs.glsl"));
	_depthPassShader = graphicsContext.CreateShader(ShaderSource::FromFiles("Shaders/DepthPass-vs.glsl", "Shaders/DepthPass-fs.glsl"));

	_terrainShader->Bind();
	_terrainShader->SetParameter("LightDirection", Vector::Normalize(Vector3f(0, -1, -0)));

	_normalShader->Bind(); 
	_normalShader->SetTextureSampler("TextureSampler", 0);
	_normalShader->SetParameter("AmbientLightAmount", 0.15f);
	_normalShader->SetParameter("LightCount", 2);
	_normalShader->SetParameter("Lights[0].Direction", _directionalLight.Direction);
	_normalShader->SetParameter("Lights[0].Power", 0.7f);
	_normalShader->SetParameter("Lights[1].Direction", Vector::Normalize(Vector3f(-0.3f, 0.4f, 0.2f)));
	_normalShader->SetParameter("Lights[1].Power", 0.8f);

	_postProcessRenderer.AddPostProcess(std::make_shared<ColorAdjustPostProcess>(_graphicsContext));
	_postProcessRenderer.AddPostProcess(std::make_shared<FogPostProcess>(_graphicsContext));
	_postProcessRenderer.AddPostProcess(std::make_shared<DepthOfFieldPostProcess>(_graphicsContext));
	_postProcessRenderer.AddPostProcess(std::make_shared<VignettePostProcess>(_graphicsContext));
	_postProcessRenderer.AddPostProcess(std::make_shared<PixelizerPostProcess>(_graphicsContext))->SetEnabled(false);
	_postProcessRenderer.AddPostProcess(std::make_shared<GaussianBlurPostProcess>(_graphicsContext))->SetEnabled(false); 

	//_postProcessRenderer.AddPostProcess(std::make_shared<SSAO>(_graphicsContext));

	_directionalLightShadowMap = RenderTarget::Create(1024, 1024, DepthBufferFormat::Depth32, {});

	_directionalLightShadowMap->BindRenderTarget();
	_directionalLightShadowMap->BindDepthTexture();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL); // doesnt change anything
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE); // this does !!
}

Renderer::~Renderer() = default; 
void Renderer::AddObject(std::shared_ptr<const RenderObject> renderObject)
{
	_renderObjects.push_back(renderObject);
}

void Renderer::SetCamera(ICamera* camera)
{
	_camera = camera;
}

void Renderer::PostUpdate()
{
	_postProcessRenderer.Update();

	if (Input::IsNewKeyPress(KeyCode::Tab))
	{
		auto dof = _postProcessRenderer.Get<DepthOfFieldPostProcess>();
		dof->SetEnabled(!dof->IsEnabled());
	}
	else if (Input::IsNewKeyPress(KeyCode::CapsLock))
	{
		auto dof = _postProcessRenderer.Get<ColorAdjustPostProcess>();
		dof->SetEnabled(!dof->IsEnabled());
	}
}

void Renderer::Render()
{
	this->RenderShadowMap();

	_frameVertexCount = 0;
	_postProcessRenderer.BeginRender();

	// sorting every frame is pretty wasteful.. also std::sort should be fine, but I guess there could be some artifacts/glitches without stable sort..?
	std::stable_sort(_renderObjects.begin(), _renderObjects.end(), [](const std::shared_ptr<const RenderObject>& left, const std::shared_ptr<const RenderObject>& right) { return left->RenderOrder < right->RenderOrder; });
	this->RenderScene();

	_postProcessRenderer.Render(_camera);

	/* TEMPORARY; DEBUG RENDER SHADOW MAP TO LOWER-LEFT PART OF THE SCREEN */
	/*glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 512, 512);

	_postProcessRenderer.DrawFullscreen(*_directionalLightShadowMap);
	glViewport(0, 0, 1920, 1080);*/
}

void Renderer::RenderScene()
{
	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
		);

	auto shadowMVP = biasMatrix * GetShadowMVP();

	glViewport(0, 0, 1920, 1080);
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
		shader.SetParameter("ShadowMVP", shadowMVP * Matrix::Translate(renderObject->Position) * Matrix::Scale(renderObject->Scale));
		shader.SetParameter("Tint", renderObject->Material->Tint.ToVector3f());

		_directionalLightShadowMap->BindDepthTextureToSampler(1);
		shader.SetTextureSampler("ShadowMap", 1);

		renderObject->Material->Texture->BindToSampler(0);
		renderObject->Mesh->VertexBuffer->Bind();

		_frameVertexCount += renderObject->Mesh->VertexBuffer->GetVertexCount();
		_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, renderObject->Mesh->VertexBuffer->GetVertexCount());
	}
}

IShader& Renderer::GetShader(MaterialType materialType)
{
	return (materialType == MaterialType::Terrain) ? *_terrainShader : *_normalShader;
}

void Renderer::RenderShadowMap()
{
	_directionalLightShadowMap->BindRenderTarget();
	glViewport(0, 0, 1024, 1024);

	_graphicsContext.GetDepthState().SetDepthTestEnabled(true);
	_graphicsContext.GetDepthState().SetDepthWriteEnabled(true); //
	_graphicsContext.GetCullState().SetCullingEnabled(true);

	_graphicsContext.Clear(Color::White);

	auto shadowMVP = GetShadowMVP();
	_depthPassShader->Bind();
	for (auto& renderObject : _renderObjects)
	{
		renderObject->Material->Texture->BindToSampler(0);
		renderObject->Mesh->VertexBuffer->Bind();

		_depthPassShader->SetParameter("MVP", shadowMVP  * Matrix::Translate(renderObject->Position) * Matrix::Scale(renderObject->Scale));
		_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, renderObject->Mesh->VertexBuffer->GetVertexCount());
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Matrix4x4 GetShadowMVP()
{
	glm::vec3 lightInvDir = glm::vec3(0.5f, 2, 2);

	// Compute the MVP matrix from the light's point of view
	glm::mat4 depthProjectionMatrix = glm::ortho<float>(-1000, 1000, -1000, 1000, -1000, 2000);
	glm::mat4 depthViewMatrix = glm::lookAt(lightInvDir * 400, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

	glm::mat4 depthModelMatrix = glm::mat4(1.0);
	return depthProjectionMatrix * depthViewMatrix * depthModelMatrix;
}