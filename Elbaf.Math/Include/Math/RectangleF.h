#pragma once

#include <Diagnostics/Ensure.h>
#include <Math/Vector.h>
#include <climits>
#include <Math/Size.h>
#include <Math/SizeF.h>

struct RectangleF
{
public:
	float X;
	float Y;
	float Width;
	float Height;

	RectangleF(float x, float y, float width, float height);

	Vector2f Center() const;
	SizeF Size() const;

	// offsets the RectangleF by given amount
	void Offset(float xAmount, float yAmount);
	RectangleF AsOffsetted(float xAmount, float yAmount) const;

	// inflates the RectangleF by given amount
	void Inflate(float amount);
	void Inflate(float horizontalAmount, int verticalAmount);
	RectangleF AsInflated(float horizontalAmount, float verticalAmount) const;

	bool Contains(float x, float y) const;
	bool Contains(const Vector2f& point) const;
	bool Contains(const RectangleF& other) const;

	bool Intersects(const RectangleF& RectangleF) const;

	static const RectangleF Empty;
	static const RectangleF MinMax;

	static RectangleF CreateCentered(const Vector2f& center, float size);
	static RectangleF CreateCentered(const Vector2f& center, const SizeF& size);
};