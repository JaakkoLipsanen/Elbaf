#include <Graphics\OpenGL\BlendState.h>
#include <Graphics\OpenGL\OGL.h>
#include <Graphics\OpenGL\OGL-Helper.h>
#include <Core\Color.h>

bool OGL::BlendState::IsBlendEnabled() const
{
	return _isEnabled;
}

void OGL::BlendState::SetBlendEnabled(bool enabled)
{
	if (_isEnabled == enabled)
	{
		return;
	}

	_isEnabled = enabled;
	glEnableOrDisable(GL_BLEND, enabled);
}

BlendFactor OGL::BlendState::GetSourceColorBlend() const
{
	return _sourceColorBlend;
}

void OGL::BlendState::SetSourceColorBlend(BlendFactor blendFactor)
{
	if (_sourceColorBlend == blendFactor)
	{
		return;
	}

	_sourceColorBlend = blendFactor;
	this->UpdateBlendFactors();
}

BlendFactor OGL::BlendState::GetDestinationColorBlend() const
{
	return _destinationColorBlend;
}

void OGL::BlendState::SetDestinationColorBlend(BlendFactor blendFactor)
{
	if (_destinationColorBlend == blendFactor)
	{
		return;
	}

	_destinationColorBlend = blendFactor;
	this->UpdateBlendFactors();
}

BlendFactor OGL::BlendState::GetSourceAlphaBlend() const
{
	return _sourceAlphaBlend;
}

void OGL::BlendState::SetSourceAlphaBlend(BlendFactor blendFactor)
{
	if (_sourceAlphaBlend == blendFactor)
	{
		return;
	}

	_sourceAlphaBlend = blendFactor;
	this->UpdateBlendFactors();
}

BlendFactor OGL::BlendState::GetDestinationAlphaBlend() const
{
	return _destinationAlphaBlend;
}

void OGL::BlendState::SetDestinationAlphaBlend(BlendFactor blendFactor)
{
	if (_destinationAlphaBlend == blendFactor)
	{
		return;
	}

	_destinationAlphaBlend = blendFactor;
	this->UpdateBlendFactors();
}

BlendFunction OGL::BlendState::GetColorBlendFunction() const
{
	return _colorBlendFunction;
}


void OGL::BlendState::SetColorBlendFunction(BlendFunction function)
{
	if (_colorBlendFunction == function)
	{
		return;
	}

	_colorBlendFunction = function;
	this->UpdateBlendFunctions();
}

BlendFunction OGL::BlendState::GetAlphaBlendFunction() const
{
	return _alphaBlendFunction;
}

void OGL::BlendState::SetAlphaBlendFunction(BlendFunction function)
{
	if (_alphaBlendFunction == function)
	{
		return;
	}

	_alphaBlendFunction = function;
	this->UpdateBlendFunctions();
}

Color OGL::BlendState::GetBlendColor() const
{
	return _blendColor;
}

void OGL::BlendState::SetBlendColor(Color const& color)
{
	if (_blendColor == color)
	{
		return;
	}

	_blendColor = color;

	Vector4f v = color.ToVector4f();
	glBlendColor(v.x, v.y, v.z, v.w);
}

bool OGL::BlendState::IsActive() const
{
	return true;
}

void OGL::BlendState::UpdateBlendFactors()
{
	glBlendFuncSeparate(OGL::BlendFactorToGLenum(_sourceColorBlend), OGL::BlendFactorToGLenum(_destinationColorBlend), OGL::BlendFactorToGLenum(_sourceAlphaBlend), OGL::BlendFactorToGLenum(_destinationAlphaBlend));
}

void OGL::BlendState::UpdateBlendFunctions()
{
	glBlendEquationSeparate(OGL::BlendFunctionToGLenum(_colorBlendFunction), OGL::BlendFunctionToGLenum(_alphaBlendFunction));
}

void OGL::BlendState::SetSourceBlend(BlendFactor blendFactor)
{
	if (_sourceColorBlend == blendFactor && _sourceAlphaBlend == blendFactor)
	{
		return;
	}

	_sourceColorBlend = blendFactor;
	_sourceAlphaBlend = blendFactor;
	this->UpdateBlendFactors();
}

void OGL::BlendState::SetDestinationBlend(BlendFactor blendFactor)
{
	if (_destinationColorBlend == blendFactor && _destinationAlphaBlend == blendFactor)
	{
		return;
	}

	_destinationColorBlend = blendFactor;
	_destinationAlphaBlend = blendFactor;
	this->UpdateBlendFactors();
}