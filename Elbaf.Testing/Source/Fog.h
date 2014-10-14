#pragma once
#include "PostProcess.h"
#include <Graphics/ShaderSource.h>
#include <Input/Input.h>
#include <Input/KeyCode.h>
#include <Math/Range.h>
#include "DefaultCamera.h"
#include <Diagnostics/Logger.h>
#include <Math/FlaiMath.h>

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

			uniform vec3 CameraPosition;
			uniform vec3 CameraDirection;
			uniform vec2 NearPlaneSize;

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

				float pixelDistanceFromCamera = distance(pixelPositionInWorld, CameraPosition);
				float fogValue = clamp((pixelDistanceFromCamera - FogStart) / (FogEnd-FogStart), 0, 1);
				color = mix(color, FogColor, fogValue);
			})XXX";

		return  ShaderSource::FromSource(defaultVertexShader, FogFragmentShader);
	}

	virtual void LoadContent() override
	{
		this->GetShader().Bind();
		this->GetShader().SetTextureSampler("TextureSampler", 0);
		this->GetShader().SetTextureSampler("DepthSampler", 1);

		this->SetFogColor(Color(255, 255, 255, 255));
		this->SetFogRange(Range<float>(350, 450));
		this->SetUseColor(false);
	}

	virtual void Update() override
	{
		this->GetShader().Bind();
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
		this->GetShader().SetParameter("zFar", renderCamera->GetFarZ());
		this->GetShader().SetParameter("CameraPosition", renderCamera->GetPosition());
		this->GetShader().SetParameter("CameraDirection", renderCamera->GetDirection());

		struct Frustum
		{
			// todo: make const
			Vector3f NearTopLeft;
			Vector3f NearTopRight;
			Vector3f NearBottomLeft;
			Vector3f NearBottomRight;

			Vector3f FarTopLeft;
			Vector3f FarTTopRight;
			Vector3f FarTBottomLeft;
			Vector3f FarTBottomRight;

			static Frustum Create(const DefaultCamera camera)
			{
				float nearPlaneHeight = 2 * tan(camera.GetVerticalFieldOfView() / 2.0f) * camera.GetNearZ();
				float nearPlaneWidth = nearPlaneHeight * camera.GetAspectRatio();

				float farPlaneHeight = 2 * tan(camera.GetVerticalFieldOfView() / 2.0) * camera.GetFarZ();
				float farPlaneWidth = farPlaneHeight * camera.GetAspectRatio();

				Vector3f centerNear = camera.GetPosition() + camera.GetDirection() * camera.GetNearZ();
				Vector3f centerFar = camera.GetPosition() + camera.GetDirection() * camera.GetFarZ();

				return Frustum();

			}
		};

		//Logger::LogMessage(renderCamera->GetDirection());
		auto cam = dynamic_cast<const DefaultCamera*>(renderCamera);

		float height = 2 * cam->GetNearZ() * tan(FlaiMath::ToRadians(cam->GetVerticalFieldOfView() / 2));
		this->GetShader().SetParameter("NearPlaneSize", Vector2f(height * 16.0f / 9.0f, height));
		_graphicsContext.DrawPrimitives(PrimitiveType::TriangleList, 0, this->GetFullscreenQuadBuffer().GetVertexCount());
	}

private:
	bool _useColor;
	Range<float> _fogRange;
	Color _fogColor;
};