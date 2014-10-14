#pragma once
#include "PostProcess.h"
#include <Graphics/ShaderSource.h>
#include <Engine/Screen.h>

class PixelizerPostProcess : public PostProcess
{

public:
	explicit PixelizerPostProcess(IGraphicsContext& graphicsContext)
		: PostProcess(graphicsContext), _pixelSize(4)
	{
	}

	float GetPixelSize() const { return _pixelSize; }
	void SetPixelSize(float pixelSize) { Ensure::True(pixelSize > 0); _pixelSize = pixelSize; }


protected:
	virtual ShaderSource CreateShader(std::string const& defaultVertexShader) override
	{
		static const std::string PixelizerFragmentShader = R"XXX(
			#version 330 core

			in vec2 fragmentUV;
			layout(location = 0) out vec4 color;

			uniform sampler2D TextureSampler;
			uniform vec2 PixelSize;
			void main() {	
				vec2 mul = fragmentUV / PixelSize;
				mul -= fract(mul);
				mul *= PixelSize;			
				color = texture2D(TextureSampler, mul);
			})XXX";

		return ShaderSource::FromSource(defaultVertexShader, PixelizerFragmentShader);
	}

	void Process(RenderTarget& source, RenderTarget& destination, RenderTarget& originalSceneRT, ICamera const* renderCamera) override
	{
		this->GetShader().Bind();

		auto pixelSize = Vector2f::One / static_cast<Vector2f>(static_cast<Vector2i>(Screen::GetSize())) * _pixelSize;
		this->GetShader().SetParameter("PixelSize", pixelSize);

		// call base "Process"
		PostProcess::Process(source, destination, originalSceneRT, renderCamera);
	}

private:
	float _pixelSize;
};