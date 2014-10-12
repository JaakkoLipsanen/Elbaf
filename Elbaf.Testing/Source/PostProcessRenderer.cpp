#include "PostProcessRenderer.h"
#include "PostProcess.h"
#include <Graphics/IVertexBuffer.h>
#include <Graphics/ShaderSource.h>
#include <Graphics/IShader.h>
#include <Graphics/IDepthState.h>
#include <Graphics/ICullState.h>
#include <Core/Array.h>

PostProcessRenderer::PostProcessRenderer(IGraphicsContext& graphicsContext)
	: _graphicsContext(graphicsContext), _quadVertexBuffer(graphicsContext.CreateVertexBuffer(BufferType::Static))
{
	static const VertexPositionTexture quadVertices[]
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

void PostProcessRenderer::AddPostProcess(std::shared_ptr<PostProcess> postProcess)
{
	_postProcesses.push_back(postProcess);
	postProcess->Initialize(*this);
}

void PostProcessRenderer::BeginRender()
{
	_currentRenderTarget->BindRenderTarget();
	glViewport(0, 0, 1920, 1080);
}

void PostProcessRenderer::Render()
{	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	for (auto& postProcess : _postProcesses)
	{
		_backgroundRenderTarget->BindRenderTarget();

		_currentRenderTarget->BindTextureToSampler(0);
		postProcess->ProcessInner(*_currentRenderTarget, *_backgroundRenderTarget);

		_currentRenderTarget.swap(_backgroundRenderTarget);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	_graphicsContext.Clear(Color::Red);

	_passthroughShader->Bind();
	_currentRenderTarget->BindTextureToSampler(0);
	_passthroughShader->SetTextureSampler("TextureSampler", 0);
	_quadVertexBuffer->Bind();

	_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, _quadVertexBuffer->GetVertexCount());
}