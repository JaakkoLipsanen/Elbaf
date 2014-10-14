#pragma once

// MEH!! Average returns float which sucks and CreateCentered doesnt work properly with int (CreateCentered(3, 1) == 2.5-3.5, but with int it's 3, 3......)
#include <Diagnostics/Ensure.h>

template<typename T>
struct Range
{
	// ... if these are const, then assigment operator is not possible, but if these are not const then either state can be changed to invalid (Min > Max) or I have to make Min() and Max() methods..
	T Min;
	T Max;

	Range(const T& min, const T& max);
	float Average() const; // MEH. okay for int and float but for others no..
	T Length() const;
	bool Contains(T value) const;
	Range<T> AsInflated(float amount) const;

	bool Intersects(const Range<T>& other) const;

	bool operator==(const Range<T>& other) const;
	bool operator!=(const Range<T>& other) const;

	static Range<T> CreateCentered(T center, T length);
};

template <typename T>
T Range<T>::Length() const
{
	return this->Max - this->Min;
}

template <typename T>
bool Range<T>::Contains(T value) const
{
	return value >= this->Min && value <= this->Max;
}

template <typename T>
Range<T> Range<T>::AsInflated(float amount) const
{
	return Range<T>(this->Min - amount, this->Max + amount);
}

template <typename T>
bool Range<T>::Intersects(Range<T> const& other) const
{
	return (other.Min < this->Max && this->Max < other.Max) || (other.Min < this->Min && this->Min < other.Max) || (this->Min < other.Min && other.Min < this->Max) || (this->Min == other.Min && this->Max == other.Max);
}

template <typename T>
Range<T> Range<T>::CreateCentered(T center, T length)
{
	return Range<T>(center - length / 2, center + length / 2);
}

template <typename T>
Range<T>::Range(T const& min, T const& max)
	: Min(min), Max(max)
{
	Ensure::True(max >= min, "Maximum cannot be smaller than minimum");
}

template <typename T>
float Range<T>::Average() const
{
	return static_cast<float>(Min + Max) / 2.0f;
}

template <typename T>
bool Range<T>::operator==(Range<T> const& other) const
{
	return this->Min == other.Min && this->Max == other.Max;
}

template <typename T>
bool Range<T>::operator!=(Range<T> const& other) const
{
	return !(*this == other);
}