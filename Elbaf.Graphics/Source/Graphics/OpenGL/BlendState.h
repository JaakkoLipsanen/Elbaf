#pragma once
#include <Graphics\IBlendState.h>
#include <Graphics\IGraphicsContext.h>
#include <Core\Color.h>

namespace OGL
{
	class BlendState : public IBlendState
	{
	public:
		virtual bool IsBlendEnabled() const override;
		virtual void SetBlendEnabled(bool enabled) override;
		virtual BlendFactor GetSourceColorBlend() const override;
		virtual void SetSourceColorBlend(BlendFactor blendFactor) override;
		virtual BlendFactor GetDestinationColorBlend() const override;
		virtual void SetDestinationColorBlend(BlendFactor blendFactor) override;
		virtual BlendFactor GetSourceAlphaBlend() const override;
		virtual void SetSourceAlphaBlend(BlendFactor blendFactor) override;
		virtual BlendFactor GetDestinationAlphaBlend() const override;
		virtual void SetDestinationAlphaBlend(BlendFactor blendFactor) override;
		virtual BlendFunction GetColorBlendFunction() const override;
		virtual void SetColorBlendFunction(BlendFunction function) override;
		virtual BlendFunction GetAlphaBlendFunction() const override;
		virtual void SetAlphaBlendFunction(BlendFunction function) override;
		virtual Color GetBlendColor() const override;
		virtual void SetBlendColor(Color const& color) override;
		virtual bool IsActive() const override;

		virtual void SetSourceBlend(BlendFactor blendFactor) override;
		virtual void SetDestinationBlend(BlendFactor blendFactor) override;

	private:
		BlendFactor _sourceColorBlend = BlendFactor::One;
		BlendFactor _destinationColorBlend = BlendFactor::Zero;
		BlendFactor _sourceAlphaBlend = BlendFactor::One;
		BlendFactor _destinationAlphaBlend = BlendFactor::Zero;
		BlendFunction _colorBlendFunction = BlendFunction::Add;
		BlendFunction _alphaBlendFunction = BlendFunction::Add;
		Color _blendColor = Color::Transparent;
		bool _isEnabled = false;

		// these could be static methods inside the cpp
		void UpdateBlendFactors();
		void UpdateBlendFunctions();
	};
}