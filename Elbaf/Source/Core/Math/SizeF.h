#pragma once
struct SizeF
{
	const float Width;
	const float Height;

	SizeF(float width, float height);
	float GetAspectRatio();
};