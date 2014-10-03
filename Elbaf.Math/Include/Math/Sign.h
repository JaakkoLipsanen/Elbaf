#pragma once

enum class Sign
{
	Zero = 0,
	Negative = -1,
	Positive = 1,
};

namespace SignHelper
{
	static Sign Opposite(const Sign& sign)
	{
		switch (sign)
		{
		case Sign::Negative:
			return Sign::Positive;

		case Sign::Positive:
			return Sign::Negative;

		default:
			return sign;
		}
	}

	static int ToInt(const Sign& sign)
	{
		return static_cast<int>(sign);
	}
}