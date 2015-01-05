#pragma once

#include <Math/Vector.h>
#include <Math/SizeF.h>

struct Rectangle;
struct RectangleF
{
public:
	float X;
	float Y;
	float Width;
	float Height;

	RectangleF(float x, float y, float width, float height);
	RectangleF(const Rectangle& rectangle);

	float Left() const;
	float Right() const;
	float Bottom() const;
	float Top() const;

	float MinX() const;
	float MaxX() const;
	float MinY() const;
	float MaxY() const;

	Vector2f TopLeft() const;
	Vector2f TopRight() const;
	Vector2f BottomLeft() const;
	Vector2f BottomRight() const;

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

	bool Intersects(const RectangleF& other) const;

	static const RectangleF Empty;
	static const RectangleF MinMax;

	static RectangleF CreateCentered(const Vector2f& center, float size);
	static RectangleF CreateCentered(const Vector2f& center, const SizeF& size);
};


RectangleF operator*(const RectangleF& rectangle, float multiplier);
RectangleF operator*(const RectangleF& rectangle, const Vector2f& multiplier);
RectangleF operator/(const RectangleF& rectangle, float divider);
RectangleF operator/(const RectangleF& rectangle, const Vector2f& divider);