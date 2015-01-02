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

			uniform float Radius = 1;
			uniform float Softness = 0.45;
			uniform float Opacity = 0.5;

			in vec2 fragmentUV;
			layout(location = 0) out vec4 color;

			uniform sampler2D TextureSampler;
			void main() {
				color = texture2D(TextureSampler, fragmentUV);

				float distanceFromCenter = length(fragmentUV - vec2(0.5f, 0.5)) * 1.41;
				float vignette = smoothstep(Radius, Radius - Softness, distanceFromCenter);

				color.rgb = mix(color.rgb, color.rgb * vignette, Opacity);
		
			})XXX";

		return ShaderSource::FromSource(defaultVertexShader, VignetteFragmentShader);
	}

public:
	explicit VignettePostProcess(GraphicsContext& graphicsContext)
		: PostProcess(graphicsContext)
	{
	}
};