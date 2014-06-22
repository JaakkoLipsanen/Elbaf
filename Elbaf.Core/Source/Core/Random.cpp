#include <Core\Random.h>
#include <random>

class Random::Impl
{
	typedef std::mt19937 Engine;
public:
	Engine RandomEngine;
};

int Random::NextInt()
{
	std::uniform_int<int> distribution(INT_MIN, INT_MAX);
	return distribution(_pImpl->RandomEngine);
}

int Random::NextInt(int min, int max)
{
	std::uniform_int<int> distribution(min, max);
	return distribution(_pImpl->RandomEngine);
}

float Random::NextFloat()
{
	std::uniform_real<float> distribution;
	return distribution(_pImpl->RandomEngine);
}

float Random::NextFloat(float min, float max)
{
	std::uniform_real<float> distribution(min, max);
	return distribution(_pImpl->RandomEngine);
}

bool Random::NextBoolean()
{
	return this->NextFloat(0, 1) >= 0.5f;
}

byte Random::NextByte()
{
	std::uniform_int<byte> distribution;
	return distribution(_pImpl->RandomEngine);
}

byte Random::NextByte(byte min, byte max)
{
	std::uniform_int<byte> distribution(min, max);
	return distribution(_pImpl->RandomEngine);
}

bool Random::NextBooleanFromOdds(float odds)
{
	return this->NextFloat(0, 1) < odds;
}

Random::Random() : Random(std::random_device()()) // call the random_device '()' operator
{
}

Random::Random(unsigned long seed) : _pImpl(new Impl)
{
	_pImpl->RandomEngine.seed(seed);
}

// required: default destructor cant delete pimpl
Random::~Random() { }