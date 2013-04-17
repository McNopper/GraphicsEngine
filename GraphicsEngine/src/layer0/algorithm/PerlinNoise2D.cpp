/*
 * PerlinNoise2D.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise2D.h"

using namespace boost;

PerlinNoise2D::PerlinNoise2D(int32_t width, int32_t height, int32_t seed, float frequencyStart, float frequencyFactor, float amplitudeStart, float amplitudeFactor, int32_t octaves) :
		PerlinNoise(seed, frequencyStart, frequencyFactor, amplitudeStart, amplitudeFactor, octaves), width(width), height(height)
{
	data = new float[width * height];

	if (!data)
	{
		return;
	}

	dataSize = width * height;

	int32_t index;

	float frequency;
	float amplitude;

	for (int32_t y = 0; y < height; y++)
	{
		for (int32_t x = 0; x < width; x++)
		{
			index = y * width + x;

			data[index] = 0.0f;

			frequency = frequencyStart;
			amplitude = amplitudeStart;

			for (int32_t i = 0; i < octaves; i++)
			{
				data[index] += getPerlinNoiseValue((float)x * frequency + (float)seed, (float)y * frequency + (float)seed) * amplitude;

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
}

PerlinNoise2D::~PerlinNoise2D()
{
}

float PerlinNoise2D::getNoiseValue(int32_t x, int32_t y) const
{
	return getRandomValue(x + y * 57);
}

float PerlinNoise2D::getSmoothNoiseValue(int32_t x, int32_t y) const
{
	float result = getNoiseValue(x, y) / 4.0f;

	result += (getNoiseValue(x - 1, y) + getNoiseValue(x + 1, y) + getNoiseValue(x, y - 1) + getNoiseValue(x, y + 1)) / 8.0f;

	result += (getNoiseValue(x - 1, y - 1) + getNoiseValue(x + 1, y - 1) + getNoiseValue(x - 1, y + 1) + getNoiseValue(x + 1, y + 1)) / 16.0f;

	return result;
}

float PerlinNoise2D::getPerlinNoiseValue(float x, float y) const
{
	float floorX = floorf(x);
	float floorY = floorf(y);
	float fractX = x - floorX;
	float fractY = y - floorY;
	float ceilX = floorX + 1.0f;
	float ceilY = floorY + 1.0f;

	float v0 = getInterpolatedValue(getSmoothNoiseValue((int32_t)floorX, (int32_t)floorY), getSmoothNoiseValue((int32_t)ceilX, (int32_t)floorY), fractX);
	float v1 = getInterpolatedValue(getSmoothNoiseValue((int32_t)floorX, (int32_t)ceilY), getSmoothNoiseValue((int32_t)ceilX, (int32_t)ceilY), fractX);

	return getInterpolatedValue(v0, v1, fractY);
}

int32_t PerlinNoise2D::getWidth() const
{
	return width;
}

int32_t PerlinNoise2D::getHeight() const
{
	return height;
}
