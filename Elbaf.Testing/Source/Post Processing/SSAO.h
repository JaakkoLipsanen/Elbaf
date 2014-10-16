#pragma once
#include "PostProcess.h"
#include <Graphics/ShaderSource.h>
#include <Input/Input.h>
#include <Input/KeyCode.h>
#include <Math/Range.h>
#include "DefaultCamera.h"
#include <Diagnostics/Logger.h>
#include <Math/FlaiMath.h>
#include <Graphics/IShader.h>
#include <Graphics/PrimitiveType.h>
#include <Graphics/IVertexBuffer.h>

class SSAO : public PostProcess
{
public:
	explicit SSAO(IGraphicsContext& graphicsContext)
		: PostProcess(graphicsContext)
	{
	}


protected:
	virtual ShaderSource CreateShader(std::string const& defaultVertexShader) override
	{
		// TODO: the fragment shader could be optimized A LOT. I mean, lots of stuff could be calculated just one in the CPU
		// also some stuff could be moved to vertex shader and let the hardware interpolate it (for example "pixelPositionInNearPlane"
		// partially based on this: http://cs.gmu.edu/~jchen/cs662/fog.pdf
		static const std::string FogFragmentShader = R"XXX(
			#version 330 core

			in vec2 fragmentUV;
			layout(location = 0) out vec4 color;

			uniform sampler2D TextureSampler;
			uniform sampler2D DepthSampler; // depth reconstruction 
			uniform bool UseColor;

			// depth reconstruction 
			uniform float zNear;
			uniform float zFar;

			uniform vec3 CameraPosition;
			uniform vec3 CameraDirection;
			uniform vec2 NearPlaneSize;

			
			uniform int SampleRadius = 0;
			uniform int SampleCount = 0;
			uniform vec2 PixelSize;


			float CalculatePixelDepthFromCamera(vec2 uv)
			{
				float depthBufferZ =  texture2D(DepthSampler, uv).r;
	
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
			


			float CalculateZBufferAvg(vec2 sampleAreaSize, vec2 uv)
			{
				float result = 0;
				vec2 stepSize = sampleAreaSize / SampleCount;
				for(int j = -SampleCount; j <= SampleCount; j++)
				{
					for(int i = -SampleCount; i <= SampleCount; i++)
					{
						result += CalculatePixelDepthFromCamera(uv + vec2(i, j) * stepSize);
					}
				}

				result /= float((SampleCount * 2 + 1) * (SampleCount * 2 + 1));
				return result;
			}

			
			void main() {
				color = texture2D(TextureSampler, fragmentUV);
				float distance = CalculatePixelDepthFromCamera(fragmentUV);
				distance -= CalculateZBufferAvg(PixelSize * SampleRadius, fragmentUV);
				distance = pow(abs(distance), 0.4);
				distance = min(1, distance > 2 ? distance / 8.0f : 0);
				color.rgb =  vec3(distance, distance, distance);
			})XXX";

		return ShaderSource::FromSource(defaultVertexShader, FogFragmentShader);
	}

	virtual void LoadContent() override
	{
		this->GetShader().Bind();
		this->GetShader().SetTextureSampler("TextureSampler", 0);
		this->GetShader().SetTextureSampler("DepthSampler", 1);
	}

	virtual void Process(RenderTarget& source, RenderTarget& destination, RenderTarget& originalSceneRT, const ICamera* renderCamera) override
	{
		this->GetShader().Bind();

		// bind depth texture to sampler 1
		originalSceneRT.BindDepthTextureToSampler(1);

		this->GetShader().SetTextureSampler("TextureSampler", 0);
		this->GetShader().SetTextureSampler("DepthSampler", 1);

		this->GetShader().SetParameter("zNear", renderCamera->GetNearZ());
		this->GetShader().SetParameter("zFar", renderCamera->GetFarZ());
		this->GetShader().SetParameter("CameraPosition", renderCamera->GetPosition());
		this->GetShader().SetParameter("CameraDirection", renderCamera->GetDirection());

		this->GetShader().SetParameter("SampleRadius", 12);
		this->GetShader().SetParameter("SampleCount", 3);
		this->GetShader().SetParameter("PixelSize", Vector2f::One / Vector2f(Vector2i(Screen::GetSize())));

		//Logger::LogMessage(renderCamera->GetDirection());
		auto cam = dynamic_cast<const DefaultCamera*>(renderCamera);

		float height = 2 * cam->GetNearZ() * tan(FlaiMath::ToRadians(cam->GetVerticalFieldOfView() / 2));
		this->GetShader().SetParameter("NearPlaneSize", Vector2f(height * 16.0f / 9.0f, height));
		_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, this->GetFullscreenQuadBuffer().GetVertexCount());
	}
};