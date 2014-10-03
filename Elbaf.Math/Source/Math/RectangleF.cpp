#include <Math/RectangleF.h>


const RectangleF RectangleF::Empty = RectangleF(0, 0, 0, 0);
const RectangleF RectangleF::MinMax = RectangleF(FLT_MIN / 2, FLT_MIN / 2, FLT_MAX, FLT_MAX);

inline RectangleF::RectangleF(float x, float y, float width, float height) : X(x), Y(y)
{
	Ensure::True(width >= 0);
	Ensure::True(height >= 0);
	this->Width = width;
	this->Height = height;
}

inline Vector2f RectangleF::Center() const
{
	return Vector2f(this->X + (this->Width / 2.0f), this->Y + (this->Height / 2.0f));
}

inline ::SizeF RectangleF::Size() const
{
	return ::SizeF(this->Width, this->Height);
}

inline void RectangleF::Offset(float xAmount, float yAmount)
{
	this->X += xAmount;
	this->Y += yAmount;
}

inline RectangleF RectangleF::AsOffsetted(float xAmount, float yAmount) const
{
	return RectangleF(this->X + xAmount, this->Y + yAmount, this->Width, this->Height);
}

inline void RectangleF::Inflate(float amount)
{
	this->Inflate(amount, amount);
}

inline void RectangleF::Inflate(float horizontalAmount, int verticalAmount)
{
	this->X -= horizontalAmount;
	this->Y -= verticalAmount;
	this->Width += horizontalAmount * 2;
	this->Height += verticalAmount * 2;
}

inline RectangleF RectangleF::AsInflated(float horizontalAmount, float verticalAmount)  const
{
	RectangleF copy = *this;
	copy.Inflate(horizontalAmount, verticalAmount);
	return copy;
}

inline bool RectangleF::Contains(float x, float y) const
{
	return x >= this->X &&
		y >= this->Y &&
		x <= this->X + this->Width &&
		y <= this->Y + this->Height;
}

inline bool RectangleF::Contains(const Vector2f& point) const
{
	return this->Contains(point.X, point.Y);
}

inline bool RectangleF::Contains(const RectangleF& other) const
{
	return other.X >= this->X &&
		other.Y >= this->Y &&
		(other.X + other.Width) <= (this->X + this->Width) &&
		(other.Y + other.Height) <= (this->Y + this->Height);
}

inline bool RectangleF::Intersects(RectangleF const& other) const
{
	return
		(other.X < (this->X + this->Width)) &&
		(other.Y < (this->Y + this->Height)) &&
		((other.X + other.Width) > this->X) &&
		((other.Y + other.Height) > this->Y);
}

inline RectangleF RectangleF::CreateCentered(const Vector2f& center, float size)
{
	return RectangleF::CreateCentered(center, { size, size });
}

inline RectangleF RectangleF::CreateCentered(const Vector2f& center, const SizeF& size)
{
	return RectangleF(center.X - size.Width / 2.0f, center.Y - size.Height / 2.0f, size.Width, size.Height);
}
