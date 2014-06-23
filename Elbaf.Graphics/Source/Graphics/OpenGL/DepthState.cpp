#include <Graphics\OpenGL\DepthState.h>

#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\OGL-Helper.h>

bool OGL::DepthState::IsDepthTestEnabled() const
{
	return _isDepthTestEnabled;
}

void OGL::DepthState::SetDepthTestEnabled(bool isEnabled)
{
	if (_isDepthTestEnabled == isEnabled)
	{
		return;
	}

	_isDepthTestEnabled = isEnabled;
	glEnableOrDisable(GL_DEPTH_TEST, _isDepthTestEnabled);
}

bool OGL::DepthState::IsDepthWriteEnabled() const
{
	return _depthWriteEnabled;
}

void OGL::DepthState::SetDepthWriteEnabled(bool isEnabled)
{
	if (_depthWriteEnabled == isEnabled)
	{
		return;
	}

	_depthWriteEnabled = isEnabled;
	glDepthMask(isEnabled);
}

CompareFunction OGL::DepthState::GetDepthFunction() const
{
	return _depthCompareFunction;
}

void OGL::DepthState::SetDepthFunction(CompareFunction compareFunction)
{
	if (_depthCompareFunction == compareFunction)
	{
		return;
	}

	_depthCompareFunction = compareFunction;
	glDepthFunc(OGL::CompareFunctionToGLenum(compareFunction));
}