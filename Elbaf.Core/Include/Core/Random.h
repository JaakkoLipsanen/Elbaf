#pragma once
#include <Math\Fundamental.h>
#include <memory>

class Random
{
public:
	int NextInt();
	int NextInt(int min, int max);

	float NextFloat();
	float NextFloat(float min, float max);
	bool NextBoolean();
	byte NextByte();
	byte NextByte(byte min, byte max);

	bool NextBooleanFromOdds(float odds);

	Random();
	explicit Random(unsigned long seed);
	virtual ~Random();

private:
	class Impl;
	std::unique_ptr<Impl> _pImpl;
};