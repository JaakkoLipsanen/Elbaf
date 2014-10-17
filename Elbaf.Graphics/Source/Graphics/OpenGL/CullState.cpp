#include <Graphics\OpenGL\CullState.h>

#include <Graphics\GraphicsContext.h>
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\OGL-Helper.h>

CullMode OGLCullState::GetCullMode() const
{
	return _cullMode;
}

void OGLCullState::SetCullMode(CullMode cullMode)
{
	if (_cullMode != cullMode)
	{
		_cullMode = cullMode;
		glFrontFace((_cullMode == CullMode::Clockwise ? GL_CW : GL_CCW));
	}
}

CullFace OGLCullState::GetCullFace() const
{
	return _cullFace;
}

void OGLCullState::SetCullFace(CullFace cullFace)
{
	if (_cullFace != cullFace)
	{
		_cullFace = cullFace;
		glCullFace(OGL::CullFaceToGLenum(cullFace));
	}
}

bool OGLCullState::IsCullingEnabled() const
{
	return _isCullingEnabled;
}

void OGLCullState::SetCullingEnabled(bool enabled)
{
	if (_isCullingEnabled != enabled)
	{
		glEnableOrDisable(GL_CULL_FACE, enabled);
		_isCullingEnabled = enabled;
	}
}