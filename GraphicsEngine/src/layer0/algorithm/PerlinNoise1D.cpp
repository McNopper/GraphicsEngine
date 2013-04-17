/*
 * PerlinNoise1D.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise1D.h"

PerlinNoise1D::PerlinNoise1D(int32_t width, int32_t seed, float frequencyStart, float frequencyFactor, float amplitudeStart, float amplitudeFactor, int32_t octaves) :
		PerlinNoise(seed, frequencyStart, frequencyFactor, amplitudeStart, amplitudeFactor, octaves), width(width)
{
	data = new float[width];

	if (!data)
	{
		return;
	}

	dataSize = width;

	int32_t index;

	float frequency;
	float amplitude;

	for (int32_t x = 0; x < width; x++)
	{
		index = x;

		data[index] = 0.0f;

		frequency = frequencyStart;
		amplitude = amplitudeStart;

		for (int32_t i = 0; i < octaves; i++)
		{
			data[index] += getPerlinNoiseValue((float)x * frequency + (float)seed) * amplitude;

			frequency *= frequencyFactor;
			amplitude *= amplitudeFactor;
		}

		if (index == 0 || data[index] < minValue)
		{
			minValue = data[index];
		}

		if (index == 0 || data[index] > maxValue)
		{
			maxValue = data[index];
		}
	}
}

PerlinNoise1D::~PerlinNoise1D()
{
}

float PerlinNoise1D::getNoiseValue(int32_t x) const
{
	return getRandomValue(x);
}

float PerlinNoise1D::getSmoothNoiseValue(int32_t x) const
{
	float result = getNoiseValue(x) / 2.0f;

	result += (getNoiseValue(x - 1) + getNoiseValue(x + 1)) / 4.0f;

	return result;
}

float PerlinNoise1D::getPerlinNoiseValue(float x) const
{
	float floorX = floorf(x);
	float fractX = x - floorX;
	float ceilX = floorX + 1.0f;

	return getInterpolatedValue(getSmoothNoiseValue((int32_t)floorX), getSmoothNoiseValue((int32_t)ceilX), fractX);
}

int32_t PerlinNoise1D::getWidth() const
{
	return width;
}
