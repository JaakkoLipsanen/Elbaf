#include <Core/HsvColor.h>
#include <Core/Color.h>
#include <Diagnostics/Ensure.h>
#include <Math/FlaiMath.h>

HsvColor::HsvColor(float h, float s, float v)
	: H(FlaiMath::Modulus(h, 360.0f)), S(s), V(v)
{
	Ensure::True(h >= 0 && s >= 0 && s <= 1 && v >= 0 && v <= 1);
}

HsvColor HsvColor::FromRgb(Color const& color)
{
	float R = color.R / 255.0f;
	float G = color.G / 255.0f;
	float B = color.B / 255.0f;

	float max = FlaiMath::Max(R, G, B);
	float min = FlaiMath::Min(R, G, B);

	float C = max - min;
	float tempH;
	if (C == 0)
	{
		tempH = 0;
	}
	else if (max == R)
	{
		tempH = FlaiMath::RealModulus((G - B) / C, 6.0f);
	}
	else if (max == G)
	{
		tempH = ((B - R) / C) + 2;
	}
	else
	{
		tempH = ((R - G) / C) + 4;
	}

	float H = 60 * tempH;
	float V = max;

	float S = (C == 0) ? 0 : (C / V);

	return HsvColor(H, S, V);
}

Color HsvColor::ToRgb() const
{
	float tempH = this->H / 60.0f;
	float C = this->V * this->S;
	float X = C * (1 - FlaiMath::Abs(FlaiMath::RealModulus(tempH, 2.0f) - 1));
	float m = V - C;
	switch (static_cast<int>(tempH))
	{
	case 0:
		return Color(C + m, X + m, m);
	case 1:
		return Color(X + m, C + m, m);
	case 2:
		return Color(m, C + m, X + m);
	case 3:
		return Color(m, X + m, C + m);
	case 4:
		return Color(X + m, m, C + m);
	case 5:
		return Color(C + m, m, X + m);

	default:
		return Color::Transparent;
	}
}