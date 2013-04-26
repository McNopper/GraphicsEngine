/*
 * PerlinNoise1D.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise1D.h"

PerlinNoise1D::PerlinNoise1D(int32_t width, int32_t seed, float frequency, float amplitude, float persistence, int32_t octaves) :
		PerlinNoise(seed, frequency, amplitude, persistence, octaves), width(width)
{
	if (persistence <= 0.0f)
	{
		return;
	}

	data = new float[width];

	if (!data)
	{
		return;
	}

	for (int32_t i = 0; i < width; i++)
	{
		data[i] = 0.0f;
	}

	dataSize = width;

	//

	data1D = new uint32_t[width];

	if (!data1D)
	{
		return;
	}

	srand(seed);
	for (int32_t i = 0; i < width; i++)
	{
		data1D[i] = static_cast<uint32_t>(rand());
	}

	//

	float frequencyFactor = 1.0f;
	float amplitudeFactor = 1.0f / persistence;

	for (int32_t i = 0; i < octaves; i++)
	{
		float currentFrequency = frequency * frequencyFactor;
		float currentAmplitude = amplitude / (1.0f * amplitudeFactor);

		if (currentFrequency <= 1.0f)
		{
			currentFrequency = 1.0f;
		}

		int32_t waveLenghtX = width / static_cast<int32_t>(currentFrequency);

		if (waveLenghtX < 1)
		{
			waveLenghtX = 1;
		}

		// Render per wavelength
		for (int32_t x = 0; x < width; x += waveLenghtX)
		{
			float p[2];

			int32_t xRandom = x / waveLenghtX;

			// Get random values from adjacent points
			p[0] = getNoiseValue(xRandom, static_cast<int32_t>(currentAmplitude));
			p[1] = getNoiseValue(xRandom + 1, static_cast<int32_t>(currentAmplitude));

			// Sample the points in the wavelength area
			for (int32_t xInner = 0; xInner < waveLenghtX && x + xInner < width; xInner++)
			{
				int32_t index = x + xInner;

				data[index] += getInterpolatedValue(p[0], p[1], static_cast<float>(xInner) / static_cast<float>(waveLenghtX));
			}
		}

		frequencyFactor *= 2.0f;
		amplitudeFactor *= 1.0f / persistence;
	}

	delete[] data1D;
	data1D = nullptr;
}

PerlinNoise1D::~PerlinNoise1D()
{
}

float PerlinNoise1D::getNoiseValue(int32_t x, int32_t amplitude) const
{
	if (!data1D)
	{
		return 0.0f;
	}

	x = x % width;

	if (x < 0)
	{
		x = width + x;
	}

	return static_cast<float>(data1D[x] % amplitude);
}

int32_t PerlinNoise1D::getWidth() const
{
	return width;
}
