#pragma once

enum class CullMode;
enum class CullFace;

class ICullState
{
public:
	ICullState() = default;
	virtual ~ICullState() = default;

	virtual CullMode GetCullMode() const = 0;
	virtual void SetCullMode(CullMode cullMode) = 0;

	virtual CullFace GetCullFace() const = 0;
	virtual void SetCullFace(CullFace cullFace) = 0;

	virtual bool IsCullingEnabled() const = 0;
	virtual void SetCullingEnabled(bool enabled) = 0;
};