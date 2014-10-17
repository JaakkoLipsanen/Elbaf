#pragma once
#include <Graphics\DepthState.h>

namespace OGL
{
	class OGLDepthState : public DepthState
	{
	public:
		virtual bool IsDepthTestEnabled() const override;
		virtual void SetDepthTestEnabled(bool isEnabled) override;
		virtual bool IsDepthWriteEnabled() const override;
		virtual void SetDepthWriteEnabled(bool isEnabled) override;
		virtual CompareFunction GetDepthFunction() const override;
		virtual void SetDepthFunction(CompareFunction compareFunction) override;

	private:
		bool _isDepthTestEnabled = false;
		CompareFunction _depthCompareFunction = static_cast<CompareFunction>(-1);
		bool _depthWriteEnabled = true;
	};
}