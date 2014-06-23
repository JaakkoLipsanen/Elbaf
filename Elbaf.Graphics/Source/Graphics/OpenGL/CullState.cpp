#include <Graphics\OpenGL\CullState.h>

#include <Graphics\IGraphicsContext.h>
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\OGL-Helper.h>

CullMode CullState::GetCullMode() const
{
	return _cullMode;
}

void CullState::SetCullMode(CullMode cullMode)
{
	if (_cullMode != cullMode)
	{
		_cullMode = cullMode;
		glFrontFace((_cullMode == CullMode::Clockwise ? GL_CW : GL_CCW));
	}
}

CullFace CullState::GetCullFace() const
{
	return _cullFace;
}

void CullState::SetCullFace(CullFace cullFace)
{
	if (_cullFace != cullFace)
	{
		_cullFace = cullFace;
		glCullFace(OGL::CullFaceToGLenum(cullFace));
	}
}

bool CullState::IsCullingEnabled() const
{
	return _isCullingEnabled;
}

void CullState::SetCullingEnabled(bool enabled)
{
	if (_isCullingEnabled != enabled)
	{
		glEnableOrDisable(GL_CULL_FACE, enabled);
		_isCullingEnabled = enabled;
	}
}