/*
 * PerlinNoise.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise.h"

using namespace boost;

PerlinNoise::PerlinNoise(int32_t seed, float frequencyStart, float frequencyFactor, float amplitudeStart, float amplitudeFactor, int32_t octaves) :
		data(nullptr), dataSize(0), seed(seed), frequencyStart(frequencyStart), frequencyFactor(frequencyFactor), amplitudeStart(amplitudeStart), amplitudeFactor(amplitudeFactor), octaves(octaves), minValue(0.0f), maxValue(0.0f)
{
}

PerlinNoise::PerlinNoise(const PerlinNoise& other) :
		data(nullptr), dataSize(0), seed(other.seed), frequencyStart(other.frequencyStart), frequencyFactor(other.frequencyFactor), amplitudeStart(other.amplitudeStart), amplitudeFactor(other.amplitudeFactor), octaves(other.octaves), minValue(other.minValue), maxValue(other.maxValue)
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

		frequencyStart = other.frequencyStart;
		frequencyFactor = other.frequencyFactor;

		amplitudeStart = other.amplitudeStart;
		amplitudeFactor = other.amplitudeFactor;

		octaves = other.octaves;

		minValue = other.minValue;
		maxValue = other.maxValue;

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

float PerlinNoise::getRandomValue(int32_t n) const
{
	n = (n << 13) ^ n;
	return (1.0f - (float)((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
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

float PerlinNoise::getMinValue() const
{
	return minValue;
}

float PerlinNoise::getMaxValue() const
{
	return maxValue;
}
