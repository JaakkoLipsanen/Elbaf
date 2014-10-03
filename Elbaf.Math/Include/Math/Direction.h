#pragma once
#include <Math/Vector.h>
#include <Math/Alignment.h>
#include <Math/Sign.h>

enum class HorizontalDirection
{
	Left = -1,
	Right = 1,
};

enum class VerticalDirection
{
	Up = 1,		// Up == 1 is a bit questionable, since for example in XNA 2D, the more up you go, the lower the y-value is.. so... yeah :P 
	Down = -1
};

enum class Direction2D
{
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3,
};

enum class Direction3D
{
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3,
	Forward = 4,
	Backward = 5,
};

namespace DirectionHelper
{
	/* DIRECTION2D */
	static Vector2i ToUnitVector(const Direction2D& direction)
	{
		switch (direction)
		{
		case Direction2D::Up:
			return Vector2i::UnitY;

		case Direction2D::Down:
			return -Vector2i::UnitY;

		case Direction2D::Right:
			return Vector2i::UnitX;

		case Direction2D::Left:
			return -Vector2i::UnitX;

		default:
			throw std::exception("Invalid value");
		}
	}

	static Direction2D Opposite(const Direction2D& direction)
	{
		switch (direction)
		{
		case Direction2D::Up:
			return Direction2D::Down;

		case Direction2D::Down:
			return Direction2D::Up;

		case Direction2D::Left:
			return Direction2D::Right;

		case Direction2D::Right:
			return Direction2D::Left;

		default:
			throw std::exception("Invalid value");
		}

		// return static_cast<Direction2D>(static_cast<int>(direction)+2);
	}

	static Direction2D RotateRight(const Direction2D& direction)
	{
		return static_cast<Direction2D>((static_cast<int>(direction)+1) % 4);
	}

	static Direction2D RotateLeft(const Direction2D& direction)
	{
		int value = static_cast<int>(direction)-1;
		return static_cast<Direction2D>((value == -1) ? 3 : value);
	}

	static Axis ToAxis(const Direction2D& direction)
	{
		return (direction == Direction2D::Left || direction == Direction2D::Right) ? Axis::Horizontal : Axis::Vertical;
	}

	/* DIRECTION3D */
	static Vector3i ToUnitVector(const Direction3D& direction)
	{
		switch (direction)
		{
		case Direction3D::Up:
			return Vector3i::UnitY;

		case Direction3D::Down:
			return -Vector3i::UnitY;

		case Direction3D::Right:
			return Vector3i::UnitX;

		case Direction3D::Left:
			return -Vector3i::UnitX;

		case Direction3D::Forward:
			return Vector3i::UnitZ;

		case Direction3D::Backward:
			return -Vector3i::UnitZ;

		default:
			throw std::exception("Invalid value");
		}
	}

	static Direction3D Opposite(const Direction3D& direction)
	{
		switch (direction)
		{
		case Direction3D::Up:
			return Direction3D::Down;

		case Direction3D::Down:
			return Direction3D::Up;

		case Direction3D::Right:
			return Direction3D::Left;

		case Direction3D::Left:
			return Direction3D::Right;

		case Direction3D::Forward:
			return Direction3D::Backward;

		case Direction3D::Backward:
			return Direction3D::Forward;

		default:
			throw std::exception("Invalid value");
		}
	}
}