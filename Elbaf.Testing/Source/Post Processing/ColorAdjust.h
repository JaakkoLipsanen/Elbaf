#pragma once
#include <Post Processing/PostProcess.h>
#include <Graphics/ShaderSource.h>

class ColorAdjustPostProcess : public PostProcess
{
public:
	explicit ColorAdjustPostProcess(GraphicsContext& graphicsContext)
		: PostProcess(graphicsContext), _hueShiftAmount(0), _saturationMultiplier(0.75f), _valueMultiplier(1), _dirty(true)
	{
	}

	float GetHueShiftAmount() const { return _hueShiftAmount; }
	void SetHueShiftAmount(float amount)
	{
		Ensure::True(amount >= 0 && amount < 360);
		if (_hueShiftAmount != amount)
		{
			_hueShiftAmount = amount;
			_dirty = true;
		}
	}

	float GetSaturationMultiplier() const { return _saturationMultiplier; }
	void SetSaturationMultiplier(float saturationMultiplier)
	{
		Ensure::True(saturationMultiplier >= 0);
		if (_saturationMultiplier != saturationMultiplier)
		{
			_saturationMultiplier = saturationMultiplier;
			_dirty = true;
		}
	}

	float GetValueMultiplier() const { return _valueMultiplier; }
	void SetValueMultiplier(float valueMultiplier)
	{
		Ensure::True(valueMultiplier >= 0);
		if (_valueMultiplier != valueMultiplier)
		{
			_valueMultiplier = valueMultiplier;
			_dirty = true;
		}
	}
protected:
	virtual ShaderSource CreateShader(std::string const& defaultVertexShader) override
	{
		static const std::string VignetteFragmentShader = R"XXX(
			#version 330 core

			in vec2 fragmentUV;
			layout(location = 0) out vec4 color;

			uniform sampler2D TextureSampler;
			uniform float HueShift = 0;
			uniform float SaturationMultiplier = 1;
			uniform float ValueMultiplier = 1;

			vec3 RgbToHsv(vec3 rgb)
			{
				float max = max(rgb.r, max(rgb.g, rgb.b));
				float min = min(rgb.r, min(rgb.g, rgb.b));
				float C = max - min;

				float hue;
				if(C == 0) hue = 0;
				else if(max == rgb.r) hue = mod((rgb.g - rgb.b) / C, 6.0f);
				else if(max == rgb.g) hue = (rgb.b - rgb.r) / C + 2;
				else  hue = (rgb.r - rgb.g) / C + 4;

				hue *= 60;
				float value = max;
				float saturation = (value == 0) ? 0 : (C / value); 

				return vec3(hue, saturation, value);
			}

			
			vec3 HsvToRgb(vec3 hsv)
			{		
				float H = hsv.r, S = hsv.g, V = hsv.b;
				float C = V * S;
				float h = H / 60.0f;
				float X = C * (1 - abs(mod(h, 2.0f) - 1));
				float m = V - C;

				switch(int(h))
				{
					case 0: return vec3(C + m, X + m, m);
					case 1: return vec3(X + m, C + m, m);
					case 2: return vec3(m, C + m, X + m);
					case 3: return vec3(m, X + m, C + m);
					case 4: return vec3(X + m, m, C + m);
					case 5: return vec3(C + m, m, X + m);
				}

				return vec3(0, 0, 0);
			}

			void main() {
				color = texture2D(TextureSampler, fragmentUV);

				vec3 hsv = RgbToHsv(color.rgb);
				hsv.r = mod(hsv.r + HueShift, 360); 
				hsv.g = min(1, hsv.g * SaturationMultiplier);
				hsv.b = min(1, hsv.b * ValueMultiplier);
				color.rgb = HsvToRgb(hsv);
		
			})XXX";

		return ShaderSource::FromSource(defaultVertexShader, VignetteFragmentShader);
	}

	virtual void Process(RenderTarget& source, RenderTarget& destination, RenderTarget& originalSceneRT, const ICamera* renderCamera) override
	{
		this->GetShader().Bind();
		if (_dirty)
		{
			this->GetShader().SetParameter("HueShift", _hueShiftAmount);
			this->GetShader().SetParameter("SaturationMultiplier", _saturationMultiplier);
			this->GetShader().SetParameter("ValueMultiplier", _valueMultiplier);
			_dirty = false;
		}

		PostProcess::Process(source, destination, originalSceneRT, renderCamera);
	}

private:
	float _hueShiftAmount;
	float _saturationMultiplier;
	float _valueMultiplier;
	bool _dirty;
};