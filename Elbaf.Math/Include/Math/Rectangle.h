#pragma once

#include <Math/Vector.h>
#include <Math/Size.h>

struct Rectangle
{
	int X;
	int Y;
	int Width; // no check for Width/Height is smaller than zero
	int Height;

	Rectangle(int x, int y, int width, int height);

	int Left() const;
	int Right() const;
	int Bottom() const;
	int Top() const;

	int MinX() const;
	int MaxX() const;
	int MinY() const;
	int MaxY() const;

	Vector2i TopLeft() const;
	Vector2i TopRight() const;
	Vector2i BottomLeft() const;
	Vector2i BottomRight() const;

	Vector2f Center() const;
	Size Size() const;

	// offsets the rectangle by given amount
	void Offset(int xAmount, int yAmount);
	Rectangle AsOffsetted(int xAmount, int yAmount) const;

	// inflates the rectangle by given amount
	void Inflate(int amount);
	void Inflate(int horizontalAmount, int verticalAmount);
	Rectangle AsInflated(int horizontalAmount, int verticalAmount) const;

	bool Contains(int x, int y) const;
	bool Contains(const Vector2i& point) const;
	bool Contains(const Rectangle& other) const;

	bool Intersects(const Rectangle& rectangle) const;

	static const Rectangle Empty;
	static const Rectangle MinMax;
};
