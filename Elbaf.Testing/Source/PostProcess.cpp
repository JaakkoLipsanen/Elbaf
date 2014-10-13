#include "PostProcess.h"
#include "PostProcessRenderer.h"
#include <Graphics/ShaderSource.h>
#include <Graphics/IShader.h>
#include <Graphics/IVertexBuffer.h>
#include <Engine/ICamera.h>

static const std::string DefaultVertexShader = R"XXX(
	#version 330 core

	layout(location = 0) in vec3 vertexPosition;
	layout(location = 2) in vec2 vertexUV;
	out vec2 fragmentUV;

	void main(){

	gl_Position =  vec4(vertexPosition, 1);
	fragmentUV = vertexUV;
})XXX";


IVertexBuffer& PostProcess::GetFullscreenQuadBuffer()
{
	return *_parentRenderer->_quadVertexBuffer;
}

IShader& PostProcess::GetShader()
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
	destination.BindRenderTarget();
	source.BindTextureToSampler(0);
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
