#include <Math/Rectangle.h>
#include <Diagnostics/Ensure.h>
#include <climits>

const Rectangle Rectangle::Empty = Rectangle(0, 0, 0, 0);
const Rectangle Rectangle::MinMax = Rectangle(INT32_MIN / 2, INT32_MIN / 2, INT32_MAX, INT32_MAX);

Rectangle::Rectangle(int x, int y, int width, int height) : X(x), Y(y)
{
	Ensure::True(width >= 0);
	Ensure::True(height >= 0);
	this->Width = width;
	this->Height = height;
}

Vector2f Rectangle::Center() const
{
	return Vector2f(this->X + (this->Width / 2.0f), this->Y + (this->Height / 2.0f));
}

Size Rectangle::Size() const
{
	return ::Size(this->Width, this->Height);
}

void Rectangle::Offset(int xAmount, int yAmount)
{
	this->X += xAmount;
	this->Y += yAmount;
}

Rectangle Rectangle::AsOffsetted(int xAmount, int yAmount) const
{
	return Rectangle(this->X + xAmount, this->Y + yAmount, this->Width, this->Height);
}

void Rectangle::Inflate(int amount)
{
	this->Inflate(amount, amount);
}

void Rectangle::Inflate(int horizontalAmount, int verticalAmount)
{
	this->X -= horizontalAmount;
	this->Y -= verticalAmount;
	this->Width += horizontalAmount * 2;
	this->Height += verticalAmount * 2;
}

Rectangle Rectangle::AsInflated(int horizontalAmount, int verticalAmount)  const
{
	Rectangle copy = *this;
	copy.Inflate(horizontalAmount, verticalAmount);
	return copy;
}

bool Rectangle::Contains(int x, int y) const
{
	return x >= this->X &&
		y >= this->Y &&
		x <= this->X + this->Width &&
		y <= this->Y + this->Height;
}

bool Rectangle::Contains(const Vector2i& point) const
{
	return this->Contains(point.X, point.Y);
}

bool Rectangle::Contains(const Rectangle& other) const
{
	return other.X >= this->X &&
		other.Y >= this->Y &&
		(other.X + other.Width) <= (this->X + this->Width) &&
		(other.Y + other.Height) <= (this->Y + this->Height);
}

bool Rectangle::Intersects(Rectangle const& other) const
{
	return
		(other.X < (this->X + this->Width)) &&
		(other.Y < (this->Y + this->Height)) &&
		((other.X + other.Width) > this->X) &&
		((other.Y + other.Height) > this->Y);
}