#include "PostProcess.h"
#include "PostProcessRenderer.h"
#include <Graphics/ShaderSource.h>
#include <Graphics/Shader.h>
#include <Graphics/VertexBuffer.h>
#include <Engine/ICamera.h>
#include <Graphics/RenderTarget.h>

static const std::string DefaultVertexShader = R"XXX(
	#version 330 core

	layout(location = 0) in vec3 vertexPosition;
	layout(location = 2) in vec2 vertexUV;
	out vec2 fragmentUV;

	void main(){
		gl_Position =  vec4(vertexPosition, 1);
		fragmentUV = vertexUV;
	})XXX";


VertexBuffer& PostProcess::GetFullscreenQuadBuffer()
{
	return *_parentRenderer->_quadVertexBuffer;
}

Shader& PostProcess::GetShader()
{
	return *_shader;
}

void PostProcess::Initialize(PostProcessRenderer& parentRenderer)
{
	_parentRenderer = &parentRenderer;

	// not sure about the best order of CreateShader and LoadContent...?
	auto shaderSource = this->CreateShader(DefaultVertexShader);
	_shader = _graphicsContext.CreateShader(shaderSource);

	this->LoadContent();
}

void PostProcess::ProcessInner(RenderTarget& source, RenderTarget& destination, RenderTarget& originalSceneRT, const ICamera* renderCamera)
{
	_shader->Bind();
	_graphicsContext.BindRenderTarget(&destination);
	source.GetColorTexture(0).BindToSampler(0);
	_shader->SetTextureSampler("TextureSampler", 0);

	this->GetFullscreenQuadBuffer().Bind();
	this->Process(source, destination, originalSceneRT, renderCamera);
}

// default implementation == draw full screen quad with the shader applied
void PostProcess::Process(RenderTarget& source, RenderTarget& destination, RenderTarget& originalSceneRT, const ICamera* renderCamera)
{
	this->GetFullscreenQuadBuffer().Bind();
	_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, this->GetFullscreenQuadBuffer().GetVertexCount());
}
