#pragma once

enum class BlendFactor
{
	Zero,
	One,
	SourceColor,
	OneMinusSourceColor,
	DestinationColor,
	OneMinusDestinationColor,
	SourceAlpha,
	OneMinusSourceAlpha,
	DestinationAlpha,
	OneMinusDestinationAlpha,

	ConstantColor,
	OneMinusConstantColor,
	ConstantAlpha,
	OneMinusConstantAlpha,
	SourceAlphaSaturate
};

enum class BlendFunction
{
	Add,
	Substract,
	ReverseSubstract,
	Min,
	Max
};

struct Color;
class BlendState
{
public:
	BlendState() = default;
	virtual ~BlendState() = default;

	virtual bool IsBlendEnabled() const = 0;
	virtual void SetBlendEnabled(bool enabled) = 0;

	virtual BlendFactor GetSourceColorBlend() const = 0;
	virtual void SetSourceColorBlend(BlendFactor blendFactor) = 0;

	virtual BlendFactor GetDestinationColorBlend() const = 0;
	virtual void SetDestinationColorBlend(BlendFactor blendFactor) = 0;

	virtual BlendFactor GetSourceAlphaBlend() const = 0;
	virtual void SetSourceAlphaBlend(BlendFactor blendFactor) = 0;

	virtual BlendFactor GetDestinationAlphaBlend() const = 0;
	virtual void SetDestinationAlphaBlend(BlendFactor blendFactor) = 0;

	virtual void SetSourceBlend(BlendFactor blendFactor) = 0;
	virtual void SetDestinationBlend(BlendFactor blendFactor) = 0;

	virtual BlendFunction GetColorBlendFunction() const = 0;
	virtual void SetColorBlendFunction(BlendFunction function) = 0;

	virtual BlendFunction GetAlphaBlendFunction() const = 0;
	virtual void SetAlphaBlendFunction(BlendFunction function) = 0;

	virtual Color GetBlendColor() const = 0;
	virtual void SetBlendColor(const Color& color) = 0;
};