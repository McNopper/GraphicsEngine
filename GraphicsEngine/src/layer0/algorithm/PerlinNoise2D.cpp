/*
 * PerlinNoise2D.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise2D.h"

using namespace boost;

PerlinNoise2D::PerlinNoise2D(int32_t width, int32_t height, int32_t seed, float frequency, float amplitude, float persistence, int32_t octaves) :
		PerlinNoise(seed, frequency, amplitude, persistence, octaves), width(width), height(height), data2D(nullptr)
{
	if (persistence <= 0.0f)
	{
		return;
	}

	data = new float[width * height];

	if (!data)
	{
		return;
	}

	for (int32_t i = 0; i < width * height; i++)
	{
		data[i] = 0.0f;
	}

	dataSize = width * height;

	//

	data2D = new uint32_t[width * height];

	if (!data2D)
	{
		return;
	}

	srand(seed);
	for (int32_t i = 0; i < width * height; i++)
	{
		data2D[i] = static_cast<uint32_t>(rand());
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
		int32_t waveLenghtY = height / static_cast<int32_t>(currentFrequency);

		if (waveLenghtX < 1)
		{
			waveLenghtX = 1;
		}
		if (waveLenghtY < 1)
		{
			waveLenghtY = 1;
		}

		// Render per wavelength
		for (int32_t y = 0; y < height; y += waveLenghtY)
		{
			for (int32_t x = 0; x < width; x += waveLenghtX)
			{
				float p[4];

				int32_t xRandom = x / waveLenghtX;
				int32_t yRandom = y / waveLenghtY;

				// Get random values from adjacent points
				p[0] = getNoiseValue(xRandom, yRandom, static_cast<int32_t>(currentAmplitude));
				p[1] = getNoiseValue(xRandom + 1, yRandom, static_cast<int32_t>(currentAmplitude));
				p[2] = getNoiseValue(xRandom, yRandom + 1, static_cast<int32_t>(currentAmplitude));
				p[3] = getNoiseValue(xRandom + 1, yRandom + 1, static_cast<int32_t>(currentAmplitude));

				// Sample the points in the wavelength area
				for (int32_t yInner = 0; yInner < waveLenghtY && y + yInner < height; yInner++)
				{
					for (int32_t xInner = 0; xInner < waveLenghtX && x + xInner < width; xInner++)
					{
						int32_t index = (y + yInner) * width + x + xInner;

						float x0 = getInterpolatedValue(p[0], p[1], static_cast<float>(xInner) / static_cast<float>(waveLenghtX));
						float x1 = getInterpolatedValue(p[2], p[3], static_cast<float>(xInner) / static_cast<float>(waveLenghtX));

						data[index] += getInterpolatedValue(x0, x1, static_cast<float>(yInner) / static_cast<float>(waveLenghtY));
					}
				}
			}
		}

		frequencyFactor *= 2.0f;
		amplitudeFactor *= 1.0f / persistence;
	}

	delete[] data2D;
	data2D = nullptr;
}

PerlinNoise2D::~PerlinNoise2D()
{
}

float PerlinNoise2D::getNoiseValue(int32_t x, int32_t y, int32_t amplitude) const
{
	if (!data2D)
	{
		return 0.0f;
	}

	x = x % width;
	y = y % height;

	if (x < 0)
	{
		x = width + x;
	}
	if (y < 0)
	{
		y = height + y;
	}

	return static_cast<float>(data2D[x + y * width] % amplitude);
}

int32_t PerlinNoise2D::getWidth() const
{
	return width;
}

int32_t PerlinNoise2D::getHeight() const
{
	return height;
}
