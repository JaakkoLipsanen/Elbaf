#include "PostProcess.h"
#include "PostProcessRenderer.h"
#include <Graphics/ShaderSource.h>
#include <Graphics/IShader.h>
#include <Graphics/IVertexBuffer.h>


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
	_shader->Bind();
	_shader->SetTextureSampler("TextureSampler", 0);
	this->LoadContent();
}

void PostProcess::ProcessInner(RenderTarget& source, RenderTarget& destination)
{
	_shader->Bind();
	source.BindTextureToSampler(0);

	this->GetFullscreenQuadBuffer().Bind();
	this->Process(source, destination);
}

// default implementation == draw full screen quad with the shader applied
void PostProcess::Process(RenderTarget& source, RenderTarget& destination)
{
	this->GetFullscreenQuadBuffer().Bind();
	_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, this->GetFullscreenQuadBuffer().GetVertexCount());
}
