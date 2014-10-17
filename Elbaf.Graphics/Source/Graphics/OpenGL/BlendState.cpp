#include <Graphics\OpenGL\BlendState.h>
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\OGL-Helper.h>
#include <Core\Color.h>

bool OGL::OGLBlendState::IsBlendEnabled() const
{
	return _isEnabled;
}

void OGL::OGLBlendState::SetBlendEnabled(bool enabled)
{
	if (_isEnabled == enabled)
	{
		return;
	}

	_isEnabled = enabled;
	glEnableOrDisable(GL_BLEND, enabled);
}

BlendFactor OGL::OGLBlendState::GetSourceColorBlend() const
{
	return _sourceColorBlend;
}

void OGL::OGLBlendState::SetSourceColorBlend(BlendFactor blendFactor)
{
	if (_sourceColorBlend == blendFactor)
	{
		return;
	}

	_sourceColorBlend = blendFactor;
	this->UpdateBlendFactors();
}

BlendFactor OGL::OGLBlendState::GetDestinationColorBlend() const
{
	return _destinationColorBlend;
}

void OGL::OGLBlendState::SetDestinationColorBlend(BlendFactor blendFactor)
{
	if (_destinationColorBlend == blendFactor)
	{
		return;
	}

	_destinationColorBlend = blendFactor;
	this->UpdateBlendFactors();
}

BlendFactor OGL::OGLBlendState::GetSourceAlphaBlend() const
{
	return _sourceAlphaBlend;
}

void OGL::OGLBlendState::SetSourceAlphaBlend(BlendFactor blendFactor)
{
	if (_sourceAlphaBlend == blendFactor)
	{
		return;
	}

	_sourceAlphaBlend = blendFactor;
	this->UpdateBlendFactors();
}

BlendFactor OGL::OGLBlendState::GetDestinationAlphaBlend() const
{
	return _destinationAlphaBlend;
}

void OGL::OGLBlendState::SetDestinationAlphaBlend(BlendFactor blendFactor)
{
	if (_destinationAlphaBlend == blendFactor)
	{
		return;
	}

	_destinationAlphaBlend = blendFactor;
	this->UpdateBlendFactors();
}

BlendFunction OGL::OGLBlendState::GetColorBlendFunction() const
{
	return _colorBlendFunction;
}


void OGL::OGLBlendState::SetColorBlendFunction(BlendFunction function)
{
	if (_colorBlendFunction == function)
	{
		return;
	}

	_colorBlendFunction = function;
	this->UpdateBlendFunctions();
}

BlendFunction OGL::OGLBlendState::GetAlphaBlendFunction() const
{
	return _alphaBlendFunction;
}

void OGL::OGLBlendState::SetAlphaBlendFunction(BlendFunction function)
{
	if (_alphaBlendFunction == function)
	{
		return;
	}

	_alphaBlendFunction = function;
	this->UpdateBlendFunctions();
}

Color OGL::OGLBlendState::GetBlendColor() const
{
	return _blendColor;
}

void OGL::OGLBlendState::SetBlendColor(Color const& color)
{
	if (_blendColor == color)
	{
		return;
	}

	_blendColor = color;

	Vector4f v = color.ToVector4f();
	glBlendColor(v.x, v.y, v.z, v.w);
}

void OGL::OGLBlendState::UpdateBlendFactors()
{
	glBlendFuncSeparate(OGL::BlendFactorToGLenum(_sourceColorBlend), OGL::BlendFactorToGLenum(_destinationColorBlend), OGL::BlendFactorToGLenum(_sourceAlphaBlend), OGL::BlendFactorToGLenum(_destinationAlphaBlend));
}

void OGL::OGLBlendState::UpdateBlendFunctions()
{
	glBlendEquationSeparate(OGL::BlendFunctionToGLenum(_colorBlendFunction), OGL::BlendFunctionToGLenum(_alphaBlendFunction));
}

void OGL::OGLBlendState::SetSourceBlend(BlendFactor blendFactor)
{
	if (_sourceColorBlend == blendFactor && _sourceAlphaBlend == blendFactor)
	{
		return;
	}

	_sourceColorBlend = blendFactor;
	_sourceAlphaBlend = blendFactor;
	this->UpdateBlendFactors();
}

void OGL::OGLBlendState::SetDestinationBlend(BlendFactor blendFactor)
{
	if (_destinationColorBlend == blendFactor && _destinationAlphaBlend == blendFactor)
	{
		return;
	}

	_destinationColorBlend = blendFactor;
	_destinationAlphaBlend = blendFactor;
	this->UpdateBlendFactors();
}