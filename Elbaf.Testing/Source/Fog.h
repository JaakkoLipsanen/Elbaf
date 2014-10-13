#pragma once
#include "PostProcess.h"
#include <Graphics/ShaderSource.h>

class FogPostProcess : public PostProcess
{

public:
	explicit FogPostProcess(IGraphicsContext& graphicsContext)
		: PostProcess(graphicsContext)
	{
	}

protected:
	virtual ShaderSource CreateShader(std::string const& defaultVertexShader) override
	{
		static const std::string FogFragmentShader = R"XXX(
			#version 330 core

			in vec2 fragmentUV;
			layout(location = 0) out vec4 color;

			uniform sampler2D TextureSampler;
			void main() {
				color = vec4(1, 1, 0, 1); // texture2D(TextureSampler, fragmentUV);
		
			})XXX";

		return  ShaderSource::FromSource(defaultVertexShader, FogFragmentShader);
	}
};