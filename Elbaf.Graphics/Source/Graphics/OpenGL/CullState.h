#pragma once
#include <Graphics\ICullState.h>

class CullState : public ICullState
{
public:
	virtual CullMode GetCullMode() const override;
	virtual void SetCullMode(CullMode cullMode) override;
	virtual CullFace GetCullFace() const override;
	virtual void SetCullFace(CullFace cullFace) override;
	virtual bool IsCullingEnabled() const override;
	virtual void SetCullingEnabled(bool enabled) override;

private:
	CullMode _cullMode = static_cast<CullMode>(-1);
	CullFace _cullFace = static_cast<CullFace>(-1);
	bool _isCullingEnabled = false;
};