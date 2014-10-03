#pragma once

namespace FlaiMath
{
	const float Pi = 3.14159265358979323846264338327950288419716939937510582097494459230781640f;
	const float TwoPi = FlaiMath::Pi * 2;
	const float HalfPi = FlaiMath::Pi / 2;
	const float QuarterPi = FlaiMath::Pi / 4;

	template<typename T>
	T Clamp(const T& value, const T& min, const T& max)
	{
		return value < min ? min : (value > max ? max : value);
	}


	template<typename T>
	T Scale(const T& input, const T& oldMin, const T& oldMax, const T& newMin, const T& newMax)
	{
		return newMin + ((newMax - newMin) * (input - oldMin)) / (oldMax - oldMin);
	}

	// not sure if works
	template<typename T, class TIterator>
	void Scale(TIterator begin, TIterator end, const T& oldMin, const T& oldMax, const T& newMin, const T& newMax)
	{
		while (begin != end)
		{
			*(begin) = newMin + ((newMax - newMin) * (*(begin) - oldMin)) / (oldMax - oldMin);
			++begin;
		}
	}

	template<typename T>
	T Abs(const T& value)
	{
		return (value >= 0) ? value : -value;
	}

	template<typename T>
	int64 Floor(const T& value)
	{
		return static_cast<int64>(value);
	}

	template<typename T>
	int32 Floor(const T& value)
	{
		return static_cast<int>(value);
	}

	template<typename T>
	T Modulus(const T& left, const T& right)
	{
		return left % right;
	}

	template<>
	inline float Modulus<float>(const float& left, const float& right)
	{
		return std::fmodf(left, right);
	}

	template<>
	inline double Modulus<double>(const double& left, const double& right)
	{
		return std::fmod(left, right);
	}

	template<typename T>
	T RealModulus(const T& left, const T& right)
	{
		return (left - right * FlaiMath::Floor(left / right));
	}

	inline float GetVectorAngle(Vector2f vector)
	{
		return std::atan2(vector.y, vector.x);
	}

	inline Vector2f AngleToVector(float radians)
	{
		Vector2f result = Vector2f(std::cos(radians), std::sin(radians));
		return Vector::Normalize(result);
	}

	template<typename T>
	T Max(const T& value1, const T& value2)
	{
		return (value1 > value2) ? value1 : value2;
	}

	template<typename T>
	T Max(const T& value1, const T& value2, const T& value3)
	{
		return FlaiMath::Max(value1, FlaiMath::Max(value2, value3));
	}

	template<typename T>
	T Max(const T& value1, const T& value2, const T& value3, const T& value4)
	{
		return FlaiMath::Max(value1, FlaiMath::Max(value2, FlaiMath::Max(value3, value4)));
	}

	template<typename T>
	T Min(const T& value1, const T& value2)
	{
		return (value1 > value2) ? value2 : value1;
	}

	template<typename T>
	T Min(const T& value1, const T& value2, const T& value3)
	{
		return FlaiMath::Min(value1, FlaiMath::Min(value2, value3));
	}

	template<typename T>
	T Min(const T& value1, const T& value2, const T& value3, const T& value4)
	{
		return FlaiMath::Min(value1, FlaiMath::Min(value2, FlaiMath::Min(value3, value4)));
	}
}