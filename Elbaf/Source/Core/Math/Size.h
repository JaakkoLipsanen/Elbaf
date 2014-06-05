#pragma once
struct Size
{
	const int Width;
	const int Height;

	Size(int width, int height);
	float GetAspectRatio();
};