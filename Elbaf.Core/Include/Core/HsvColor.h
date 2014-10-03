#pragma once

struct Color;
struct HsvColor
{
	const float H;
	const float S;
	const float V;

	HsvColor(float h, float s, float v);

	static HsvColor FromRgb(const Color& color);
	Color ToRgb() const;
};