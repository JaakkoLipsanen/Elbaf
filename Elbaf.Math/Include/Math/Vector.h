#pragma once
#include <glm\glm.hpp>
#include <ostream>

typedef glm::vec2 Vector2f;
typedef glm::vec3 Vector3f;
typedef glm::vec4 Vector4f;

typedef glm::ivec2 Vector2i;
typedef glm::ivec3 Vector3i;
typedef glm::ivec4 Vector4i;


typedef glm::uvec2 Vector2u;
typedef glm::uvec3 Vector3u;
typedef glm::uvec4 Vector4u;

template<typename T>
using TVector2 = glm::detail::tvec2<T, glm::precision::defaultp>;

template<typename T, glm::precision P>
using TPVector2 = glm::detail::tvec2<T, P>;

template<typename T>
using TVector3 = glm::detail::tvec3<T, glm::precision::defaultp>;

template<typename T, glm::precision P>
using TPVector3 = glm::detail::tvec3<T, P>;

template<typename T>
using TVector4 = glm::detail::tvec4<T, glm::precision::defaultp>;

template<typename T, glm::precision P>
using TPVector4 = glm::detail::tvec4<T, P>;

namespace Vector
{
	template<typename VectorX>
	VectorX Abs(const VectorX& value)
	{
		TVector2<float> x;
		return glm::abs(value);
	}

	template<typename VectorX>
	VectorX Clamp(const VectorX& value, const VectorX& min, const VectorX& max)
	{
		return glm::clamp(value, min, max);
	}

	template<typename VectorX, typename Scalar>
	VectorX Lerp(const VectorX& from, const VectorX& to, const Scalar& amount)
	{
		return glm::mix(from, to, amount);
	}

	template<typename VectorX, typename Scalar>
	VectorX SmoothStep(const VectorX& from, const VectorX& to, const Scalar& amount)
	{
		return glm::smoothstep(from, to, amount);
	}

	template<typename VectorX>
	VectorX Min(const VectorX& x, const VectorX& y)
	{
		return glm::min(x, y);
	}

	template<typename VectorX>
	VectorX Max(const VectorX& x, const VectorX& y)
	{
		return glm::max(x, y);
	}

	template<typename VectorX>
	VectorX Round(const VectorX& value)
	{
		return glm::round(value);
	}

	template<typename VectorX>
	VectorX Normalize(const VectorX& value)
	{
		return glm::normalize(value);
	}

	template<typename Vector3x>
	Vector3x Cross(const Vector3x& x, const Vector3x& y)
	{
		return glm::cross(x, y);
	}

	template<typename VectorX>
	VectorX Distance(const VectorX& x, const VectorX& y)
	{
		return glm::distance(x, y);
	}

	template<typename VectorX>
	VectorX Dot(const VectorX& x, const VectorX& y)
	{
		return glm::dot(x, y);
	}

	template<typename VectorX>
	VectorX Length(const VectorX& x)
	{
		return glm::length(x);
	}
}

template<typename T, glm::precision P>
std::ostream & operator << (std::ostream & stream, TPVector2<T, P> const & vec)
{
	stream << "{ X: " << vec.x << ", Y: " << vec.y << " }";
	return stream;
}

template<typename T, glm::precision P>
std::ostream & operator << (std::ostream & stream, TPVector3<T, P> const & vec)
{
	stream << "{ X: " << vec.x << ", Y: " << vec.y << ", Z: " << vec.z << " }";
	return stream;
}

template<typename T, glm::precision P>
std::ostream & operator << (std::ostream & stream, TPVector4<T, P> const & vec)
{
	stream << "{ X: " << vec.x << ", Y: " << vec.y << ", Z: " << vec.z << ", W: " << vec.w << " }";
	return stream;
}