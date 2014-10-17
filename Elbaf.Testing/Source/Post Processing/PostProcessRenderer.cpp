#include "PostProcessRenderer.h"
#include "PostProcess.h"
#include <Graphics/VertexBuffer.h>
#include <Graphics/ShaderSource.h>
#include <Graphics/Shader.h>
#include <Graphics/DepthState.h>
#include <Graphics/CullState.h>
#include <Core/Array.h>
#include <Graphics/ClearOptions.h>
#include <Engine/ICamera.h>
#include "Vignette.h"

PostProcessRenderer::PostProcessRenderer(GraphicsContext& graphicsContext)
	: _graphicsContext(graphicsContext), _quadVertexBuffer(graphicsContext.CreateVertexBuffer(BufferType::Static))
{
	static const VertexPositionTexture quadVertices[6]
	{
		VertexPositionTexture(Vector3f(-1, 1, 0), Vector2f::UnitY),
		VertexPositionTexture(Vector3f(-1, -1, 0), Vector2f::Zero),
		VertexPositionTexture(Vector3f(1, -1, 0), Vector2f::UnitX),

		VertexPositionTexture(Vector3f(-1, 1, 0), Vector2f::UnitY),
		VertexPositionTexture(Vector3f(1, -1, 0), Vector2f::UnitX),
		VertexPositionTexture(Vector3f(1, 1, 0), Vector2f::One),
	};

	_quadVertexBuffer->SetVertexData(quadVertices, Array::Length(quadVertices));
	_currentRenderTarget = RenderTarget::Create(1920, 1080, DepthBufferFormat::Depth24Stencil8);
	_backgroundRenderTarget = RenderTarget::Create(1920, 1080, DepthBufferFormat::Depth24Stencil8);

	static const std::string VertexShader = R"XXX(
		#version 330 core

		layout(location = 0) in vec3 vertexPosition;
		layout(location = 2) in vec2 vertexUV;
		out vec2 fragmentUV;

		void main(){
			gl_Position =  vec4(vertexPosition, 1);
			fragmentUV = vertexUV;
		})XXX";

	static const std::string FragmentShader = R"XXX(
		#version 330 core

		in vec2 fragmentUV;
		out vec4 color;

		uniform sampler2D TextureSampler;
		void main() {
			color = texture2D(TextureSampler, fragmentUV);
		})XXX";

	_passthroughShader = graphicsContext.CreateShader(ShaderSource::FromSource(VertexShader, FragmentShader));
}

void PostProcessRenderer::Update()
{
	for (auto& postProcess : _postProcesses)
	{
		postProcess->Update();
	}
}

std::shared_ptr<PostProcess> PostProcessRenderer::AddPostProcess(std::shared_ptr<PostProcess> postProcess)
{
	_postProcesses.push_back(postProcess);
	postProcess->Initialize(*this);

	return postProcess;
}

void PostProcessRenderer::BeginRender()
{
	_currentRenderTarget->BindRenderTarget();
	glViewport(0, 0, 1920, 1080);
}

void PostProcessRenderer::Render(const ICamera* renderCamera)
{	
	RenderTarget& originalSceneRenderTarget = *_currentRenderTarget;
	_graphicsContext.GetDepthState().SetDepthTestEnabled(false);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	for (auto& postProcess : _postProcesses)
	{
		if (!postProcess->IsEnabled())
		{
			continue;
		}

		_backgroundRenderTarget->BindRenderTarget();
		_graphicsContext.Clear(ClearOptions::Color, Color::White);

		_currentRenderTarget->BindColorTextureToSampler(0, 0);
		postProcess->ProcessInner(*_currentRenderTarget, *_backgroundRenderTarget, originalSceneRenderTarget, renderCamera);

		_currentRenderTarget.swap(_backgroundRenderTarget);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	_graphicsContext.Clear(Color::Red);

	_passthroughShader->Bind();
	_currentRenderTarget->BindColorTextureToSampler(0, 0);
	_passthroughShader->SetTextureSampler("TextureSampler", 0);
	_quadVertexBuffer->Bind();

	_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, _quadVertexBuffer->GetVertexCount());
}

// TODO: REMOVE
void PostProcessRenderer::DrawFullscreen(RenderTarget& renderTarget)
{
	_passthroughShader->Bind();
	renderTarget.BindDepthTextureToSampler(0);
	_passthroughShader->SetTextureSampler("TextureSampler", 0);
	_quadVertexBuffer->Bind();

	_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, _quadVertexBuffer->GetVertexCount());
}