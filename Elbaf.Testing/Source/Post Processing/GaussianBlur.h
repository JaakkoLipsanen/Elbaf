#pragma once
#include "PostProcess.h"
#include <Graphics/ShaderSource.h>
#include <Graphics/IShader.h>
#include <Engine/Screen.h>

class GaussianBlurPostProcess : public PostProcess
{
protected:
	virtual ShaderSource CreateShader(std::string const& defaultVertexShader) override
	{
		static const std::string BlurFragmentShader = R"XXX(
			#version 330 core

			in vec2 fragmentUV;
			layout(location = 0) out vec4 color;

			uniform sampler2D TextureSampler;
			uniform int SampleRadius = 0;
			uniform vec2 PixelSize;

			vec4 CalculateBlur(vec2 stepSize)
			{
				vec4 result = vec4(0, 0, 0, 0);
				for(int j = -SampleRadius; j <= SampleRadius; j++)
				{
					for(int i = -SampleRadius; i <= SampleRadius; i++)
					{
						result += texture2D(TextureSampler, fragmentUV + vec2(i, j) * stepSize);
					}
				}

				result /= float((SampleRadius * 2 + 1) * (SampleRadius * 2 + 1));
				return result;
			}

			void main() {
				color = CalculateBlur(PixelSize * 4);
		
			})XXX";

		return ShaderSource::FromSource(defaultVertexShader, BlurFragmentShader);
	}

	void Process(RenderTarget& source, RenderTarget& destination, RenderTarget& originalSceneRT, ICamera const* renderCamera) override
	{
		this->GetShader().Bind();
		this->GetShader().SetTextureSampler("TextureSampler", 0);
		this->GetShader().SetParameter("SampleRadius", 3);
		this->GetShader().SetParameter("PixelSize", Vector2f::One / Vector2f(Vector2i(Screen::GetSize())));
		source.BindColorTextureToSampler(0, 0);

		PostProcess::Process(source, destination, originalSceneRT, renderCamera);
	}

public:
	explicit GaussianBlurPostProcess(IGraphicsContext& graphicsContext)
		: PostProcess(graphicsContext)
	{
	}
};