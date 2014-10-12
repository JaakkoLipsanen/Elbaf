#pragma once
#include "PostProcess.h"
#include <Graphics/ShaderSource.h>
class VignettePostProcess : public PostProcess
{
protected:
	virtual ShaderSource CreateShader(std::string const& defaultVertexShader) override
	{
		static const std::string VignetteFragmentShader = R"XXX(
			#version 330 core

			in vec2 fragmentUV;
			layout(location = 0) out vec4 color;

			uniform sampler2D TextureSampler;
			void main() {
				color = texture2D(TextureSampler, fragmentUV);

				float distanceFromCenter = length(fragmentUV - vec2(0.5f, 0.5));
				float normalized = max(0, distanceFromCenter - 0.25f);
				normalized = pow(normalized, 2);

				color.rgb *= 1 - normalized * 4f;
		
			})XXX";

		return ShaderSource::FromSource(defaultVertexShader, VignetteFragmentShader);
	}

public:
	explicit VignettePostProcess(IGraphicsContext& graphicsContext)
		: PostProcess(graphicsContext)
	{
	}
};