#pragma once
#include "PostProcess.h"
#include <Graphics/ShaderSource.h>
#include <Input/Input.h>
#include <Input/KeyCode.h>
#include <Math/Range.h>

class FogPostProcess : public PostProcess
{

public:
	explicit FogPostProcess(IGraphicsContext& graphicsContext)
		: PostProcess(graphicsContext), _fogColor(Color::Purple), _fogRange(-1, -1) // fog color and range are set to correct values in LoadContent
	{
	}

	Color GetFogColor() const { return _fogColor; }
	void SetFogColor(const Color& color)
	{
		if (_fogColor != color)
		{
			_fogColor = color;
			this->GetShader().SetParameter("FogColor", _fogColor.ToVector4f());
		}
	}

	Range<float> GetFogRange() const { return _fogRange; }
	void SetFogRange(const Range<float>& range)
	{
		if (_fogRange != range)
		{
			_fogRange = range;
			this->GetShader().SetParameter("FogStart", range.Min);
			this->GetShader().SetParameter("FogEnd", range.Max);
		}
	}

	// "use color" == does fog use RGBA values or only A value?
	bool GetUseColor() const { return _useColor; }
	void SetUseColor(bool useColor)
	{
		if (_useColor != useColor)
		{
			_useColor = useColor;
			this->GetShader().SetParameter("UseColor", _useColor);
		}
	}

protected:
	virtual ShaderSource CreateShader(std::string const& defaultVertexShader) override
	{
		// http://stackoverflow.com/a/6657284/925777 based on this. HOWEVER, this is dependant on view angle!!!! explore this: http://cs.gmu.edu/~jchen/cs662/fog.pdf, implementation: http://isnippets.blogspot.fi/2010/10/real-time-fog-using-post-processing-in.html
		static const std::string FogFragmentShader = R"XXX(
			#version 330 core

			in vec2 fragmentUV;
			layout(location = 0) out vec4 color;

			uniform sampler2D TextureSampler;
			uniform sampler2D DepthSampler;
			uniform bool UseDepth;

			uniform float FogStart;
			uniform float FogEnd;
			uniform vec4 FogColor;

			uniform float zNear;
			uniform float zFar;

			void main() {
				color = texture2D(TextureSampler, fragmentUV);
				if(!UseDepth)
				{
					return;
				}
						
				float depthBufferZ =  texture2D(DepthSampler, fragmentUV).r;
				if(depthBufferZ == 1) // if depth is "no"/default/cleared depth (which is 1 currently in Elbaf), then dont use fog
					return;

				depthBufferZ = 2.0 * depthBufferZ - 1.0; // [-1, 1] -> [0, 1]
				float pixelZ = 2.0 * zNear * zFar / (zFar + zNear - depthBufferZ * (zFar - zNear)); // [0, (zFar-zNear)]
				float normalizedPixelZ = pixelZ / (zFar-zNear); // [0, 1]

				float fogValue = clamp((pixelZ - FogStart) / (FogEnd-FogStart), 0, 1);
				color = mix(color, FogColor, fogValue);
			})XXX";

		return  ShaderSource::FromSource(defaultVertexShader, FogFragmentShader);
	}

	virtual void LoadContent() override
	{
		this->GetShader().Bind();
		this->GetShader().SetTextureSampler("TextureSampler", 0);
		this->GetShader().SetTextureSampler("DepthSampler", 1);

		this->SetFogColor(Color(255, 255, 255, 255)); // "transparent white"
		this->SetFogRange(Range<float>(350, 450));
		this->SetUseColor(false);
	}

	virtual void Update() override
	{
		this->GetShader().SetParameter("UseDepth", !Input::IsKeyPressed(KeyCode::Space));
	}

	virtual void Process(RenderTarget& source, RenderTarget& destination, RenderTarget& originalSceneRT, const ICamera* renderCamera) override
	{
		this->GetShader().Bind();

		// bind depth texture to sampler 1
		auto x = originalSceneRT.DepthTextureID();
		glActiveTexture(OGL::SamplerIndexToGLenum(1));
		glBindTexture(GL_TEXTURE_2D, x);

		this->GetShader().SetTextureSampler("TextureSampler", 0);
		this->GetShader().SetTextureSampler("DepthSampler", 1);

		this->GetShader().SetParameter("zNear", renderCamera->GetNearZ());
		this->GetShader().SetParameter("zFar", renderCamera->GetFarZ()); // todo: these should come from camera
		_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, this->GetFullscreenQuadBuffer().GetVertexCount());
	}

private:
	bool _useColor;
	Range<float> _fogRange;
	Color _fogColor;
};