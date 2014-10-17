#pragma once
#include "PostProcess.h"
#include <Graphics/ShaderSource.h>
#include <Graphics/Shader.h>
#include <Engine/Screen.h>
#include <Engine/ICamera.h>

class DepthOfFieldPostProcess : public PostProcess
{
protected:
	virtual ShaderSource CreateShader(std::string const& defaultVertexShader) override
	{
		static const std::string BlurFragmentShader = R"XXX(
			#version 330 core

			in vec2 fragmentUV;
			layout(location = 0) out vec4 color;

			uniform sampler2D TextureSampler;
			uniform sampler2D DepthSampler; // depth reconstruction 

			uniform int SampleRadius = 0;
			uniform int SampleCount = 0;
			uniform vec2 PixelSize;

			// depth reconstruction 
			uniform float zNear;
			uniform float zFar;

			uniform vec3 CameraPosition;
			uniform vec3 CameraDirection;
			uniform vec2 NearPlaneSize;

			vec4 CalculateBlur(vec2 sampleAreaSize)
			{
				vec4 result = vec4(0, 0, 0, 0);
				vec2 stepSize = sampleAreaSize / SampleCount;
				for(int j = -SampleCount; j <= SampleCount; j++)
				{
					for(int i = -SampleCount; i <= SampleCount; i++)
					{
						result += texture2D(TextureSampler, fragmentUV + vec2(i, j) * stepSize);
					}
				}

				result /= float((SampleCount * 2 + 1) * (SampleCount * 2 + 1));
				return result;
			}

			float CalculatePixelDepthFromCamera()
			{
				float depthBufferZ =  texture2D(DepthSampler, fragmentUV).r;
				if(depthBufferZ == 1)
				{
					depthBufferZ = min(texture2D(DepthSampler, fragmentUV  + vec2(-SampleCount, SampleCount) * PixelSize * SampleRadius).r,
								   min(texture2D(DepthSampler, fragmentUV  + vec2(-SampleCount, -SampleCount) * PixelSize * SampleRadius).r,
								   min(texture2D(DepthSampler, fragmentUV  + vec2(SampleCount, SampleCount) * PixelSize * SampleRadius).r, 
									   texture2D(DepthSampler, fragmentUV  + vec2(SampleCount, -SampleCount) * PixelSize * SampleRadius).r)));
				}

				//float depthBufferZ =  texture2D(DepthSampler, fragmentUV).r;
				//if(depthBufferZ == 1) return 0;

				depthBufferZ = 2.0 * depthBufferZ - 1.0; // [-1, 1] -> [0, 1]
				float pixelZ = 2.0 * zNear * zFar / (zFar + zNear - depthBufferZ * (zFar - zNear)); // [zNear, zFar-zNear] // todo: concerns here. is it really [zNear, zFar-zNear]? 
				float normalizedPixelZ = (pixelZ-zNear) / (zFar-zNear); // [0, 1]					// that could cause some (minor) bugs/glitches. im pretty sure it's [zNear, zFar-zNear] though :P

				vec3 nearPlaneCenter = CameraPosition + CameraDirection * zNear; // center of camera's near plane
				vec3 rightVector = normalize(cross(CameraDirection, vec3(0, 1, 0))); // the near planes "right" vector
				vec3 upVector = normalize(cross(rightVector, CameraDirection)); // the near planes "up" vector

				vec2 pixelOffset = vec2(fragmentUV.x - 0.5, fragmentUV.y - 0.5); // UV [0, 1] -> [-0.5, 0.5]
				vec3 rightValue = pixelOffset.x * NearPlaneSize.x * rightVector; // pixels horizontal position in the near plane
				vec3 upValue = pixelOffset.y * NearPlaneSize.y * upVector; // pixels vertical position in the near plane

				vec3 pixelPositionInNearPlane = nearPlaneCenter + rightValue + upValue; // pixels final position in the near plane

				// calculate the ratio of "length from camera to current pixel position in near plane" to "length from camear to center of near plane"
				// this information is used to multiply the depth buffer's z value later (distance from near to far plane is longer on the sides; the 'distance multiplier' is the ratio that is calculated here
				vec3 nearPlaneToCamera = pixelPositionInNearPlane - CameraPosition;
				float zLengthMultiplier = length(nearPlaneToCamera) / zNear;

				// calculate the final position of the pixel in the world
				vec3 pixelPositionInWorld = pixelPositionInNearPlane + normalize(pixelPositionInNearPlane - CameraPosition) * pixelZ * zLengthMultiplier;

				return distance(pixelPositionInWorld, CameraPosition);
			}

			void main() {
				float depth = CalculatePixelDepthFromCamera();
				
				const float BlurStart = 1000;
				const float BlurEnd = 2000;

				float blurValue = mix(0, 1, (depth - BlurStart) / (BlurEnd - BlurStart));
				blurValue = max(0, blurValue);
				blurValue = min(2, blurValue);

				color = CalculateBlur(PixelSize * blurValue * SampleRadius);
					
			})XXX";

		return ShaderSource::FromSource(defaultVertexShader, BlurFragmentShader);
	}

	void Process(RenderTarget& source, RenderTarget& destination, RenderTarget& originalSceneRT, ICamera const* renderCamera) override
	{
		this->GetShader().Bind();
		this->GetShader().SetTextureSampler("TextureSampler", 0);
		this->GetShader().SetTextureSampler("DepthSampler", 1);
		this->GetShader().SetParameter("SampleRadius", 4);
		this->GetShader().SetParameter("SampleCount", 3);
		this->GetShader().SetParameter("PixelSize", Vector2f::One / Vector2f(Vector2i(Screen::GetSize())));

		source.BindColorTextureToSampler(0, 0);

		// bind depth texture to sampler 1
		originalSceneRT.BindDepthTextureToSampler(1);


		this->GetShader().SetParameter("zNear", renderCamera->GetNearZ());
		this->GetShader().SetParameter("zFar", renderCamera->GetFarZ());
		this->GetShader().SetParameter("CameraPosition", renderCamera->GetPosition());
		this->GetShader().SetParameter("CameraDirection", renderCamera->GetDirection());

		PostProcess::Process(source, destination, originalSceneRT, renderCamera);
	}

public:
	explicit DepthOfFieldPostProcess(GraphicsContext& graphicsContext)
		: PostProcess(graphicsContext)
	{
	}
};