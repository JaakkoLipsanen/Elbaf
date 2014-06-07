#pragma once
#include "Vector.h"

// okay this fucking sucks. I dont want this to be included, but since I'm using templates, the implementations
// have to be in the header. EXCEPT! There is the template trickery where if you know the types, you can implement them
// in the CPP. But idk...
#include <glm\detail\func_noise.hpp>

// OKAY THIS IS VERY MUCH INCOMPLETE (supports only floats)!!
// GLM supports more types but i cant come up with right template hackery right now
namespace Noise
{
	template<typename InputType>
	float Noise1D(InputType x)
	{
		return glm::noise1<float>(x);
	}

	template<typename InputType, typename GenType>
	GenType Noise1D(InputType x)
	{
		return glm::noise1<GenType>(x);
	}

	template<typename InputType>
	Vector2f Noise2D(InputType x)
	{
		return glm::noise2(x);
	}

	template<typename InputType, typename GenType>
	GenType Noise2D(InputType x)
	{
		return glm::noise2<GenType>(x);
	}

	template<typename InputType>
	Vector3f Noise3D(InputType x)
	{
		return glm::noise3(x);
	}

	template<typename InputType, typename GenType>
	GenType Noise3D(InputType x)
	{
		return glm::noise3<GenType>(x);
	}
}