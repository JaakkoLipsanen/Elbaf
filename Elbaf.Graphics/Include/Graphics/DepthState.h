#pragma once

enum class CompareFunction;

// add something else here  than just depth? like.... stencil :( ??
class DepthState
{
public:
	DepthState() = default;
	virtual ~DepthState() = default;

	virtual bool IsDepthTestEnabled() const = 0;
	virtual void SetDepthTestEnabled(bool isEnabled) = 0;

	virtual bool IsDepthWriteEnabled() const = 0;
	virtual void SetDepthWriteEnabled(bool isEnabled) = 0;

	virtual CompareFunction GetDepthFunction() const = 0;
	virtual void SetDepthFunction(CompareFunction compareFunction) = 0;

	// depth bias and all sort of other stuff
};