#include <Graphics\OpenGL\DepthState.h>

#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\OGL-Helper.h>

bool OGL::OGLDepthState::IsDepthTestEnabled() const
{
	return _isDepthTestEnabled;
}

void OGL::OGLDepthState::SetDepthTestEnabled(bool isEnabled)
{
	if (_isDepthTestEnabled == isEnabled)
	{
		return;
	}

	_isDepthTestEnabled = isEnabled;
	glEnableOrDisable(GL_DEPTH_TEST, _isDepthTestEnabled);
}

bool OGL::OGLDepthState::IsDepthWriteEnabled() const
{
	return _depthWriteEnabled;
}

void OGL::OGLDepthState::SetDepthWriteEnabled(bool isEnabled)
{
	if (_depthWriteEnabled == isEnabled)
	{
		return;
	}

	_depthWriteEnabled = isEnabled;
	glDepthMask(isEnabled);
}

CompareFunction OGL::OGLDepthState::GetDepthFunction() const
{
	return _depthCompareFunction;
}

void OGL::OGLDepthState::SetDepthFunction(CompareFunction compareFunction)
{
	if (_depthCompareFunction == compareFunction)
	{
		return;
	}

	_depthCompareFunction = compareFunction;
	glDepthFunc(OGL::CompareFunctionToGLenum(compareFunction));
}