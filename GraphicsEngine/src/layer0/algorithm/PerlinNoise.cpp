/*
 * PerlinNoise.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise.h"

using namespace boost;

PerlinNoise::PerlinNoise(int32_t seed, float frequency, float amplitude, float persistence, int32_t octaves) :
		data(nullptr), dataSize(0), seed(seed), frequency(frequency), amplitude(amplitude), persistence(persistence), octaves(octaves)
{
}

PerlinNoise::PerlinNoise(const PerlinNoise& other) :
		data(nullptr), dataSize(0), seed(other.seed), frequency(other.frequency), amplitude(other.amplitude), persistence(other.persistence), octaves(other.octaves)
{
	data = new float[other.dataSize];

	if (!data)
	{
		return;
	}

	memcpy(data, other.data, other.dataSize * sizeof(float));

	dataSize = other.dataSize;
}

PerlinNoise::~PerlinNoise()
{
	freeData();
}

PerlinNoise& PerlinNoise::operator =(const PerlinNoise& other)
{
	if (this != &other)
	{
		freeData();

		seed = other.seed;

		frequency = other.frequency;

		amplitude = other.amplitude;

		persistence = other.persistence;

		octaves = other.octaves;

		data = new float[other.dataSize];

		if (!data)
		{
			return *this;
		}

		memcpy(data, other.data, other.dataSize * sizeof(float));

		dataSize = other.dataSize;
	}

	return *this;
}

void PerlinNoise::freeData()
{
	if (data)
	{
		delete[] data;

		data = nullptr;

		dataSize = 0;
	}
}

float PerlinNoise::getInterpolatedValue(float value0, float value1, float t) const
{
	float ft;

	ft = (1.0f - cosf(t * GLUS_PI)) / 2.0f;

	return value0 * (1.0f - ft) + value1 * ft;
}

const float* PerlinNoise::getData() const
{
	return data;
}

boost::int32_t PerlinNoise::getDataSize() const
{
	return dataSize;
}
