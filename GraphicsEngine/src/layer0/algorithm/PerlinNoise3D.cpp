/*
 * PerlinNoise3D.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise3D.h"

PerlinNoise3D::PerlinNoise3D(int32_t width, int32_t height, int32_t depth, int32_t seed, float frequencyStart, float frequencyFactor, float amplitudeStart, float amplitudeFactor, int32_t octaves) :
		PerlinNoise(seed, frequencyStart, frequencyFactor, amplitudeStart, amplitudeFactor, octaves), width(width), height(height), depth(depth)
{
	data = new float[width * height * depth];

	if (!data)
	{
		return;
	}

	dataSize = width * height * depth;

	int32_t index;

	float frequency;
	float amplitude;

	for (int32_t z = 0; z < depth; z++)
	{
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
					data[index] += getPerlinNoiseValue((float)x * frequency + (float)seed, (float)y * frequency + (float)seed, (float)z * frequency + (float)seed) * amplitude;

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
}

PerlinNoise3D::~PerlinNoise3D()
{
}

float PerlinNoise3D::getNoiseValue(int32_t x, int32_t y, int32_t z) const
{
	return getRandomValue(x + y * 57 + z * 127);
}

float PerlinNoise3D::getSmoothNoiseValue(int32_t x, int32_t y, int32_t z) const
{
	float result = getNoiseValue(x, y, z) / 8.0f;
	result += (getNoiseValue(x - 1, y, z) + getNoiseValue(x + 1, y, z) + getNoiseValue(x, y - 1, z) + getNoiseValue(x, y + 1, z)) / 16.0f;
	result += (getNoiseValue(x - 1, y - 1, z) + getNoiseValue(x + 1, y - 1, z) + getNoiseValue(x - 1, y + 1, z) + getNoiseValue(x + 1, y + 1, z)) / 32.0f;

	result += getNoiseValue(x, y, z - 1) / 16.0f;
	result += (getNoiseValue(x - 1, y, z - 1) + getNoiseValue(x + 1, y, z - 1) + getNoiseValue(x, y - 1, z - 1) + getNoiseValue(x, y + 1, z - 1)) / 32.0f;
	result += (getNoiseValue(x - 1, y - 1, z - 1) + getNoiseValue(x + 1, y - 1, z - 1) + getNoiseValue(x - 1, y + 1, z - 1) + getNoiseValue(x + 1, y + 1, z - 1)) / 64.0f;

	result += getNoiseValue(x, y, z + 1) / 16.0f;
	result += (getNoiseValue(x - 1, y, z + 1) + getNoiseValue(x + 1, y, z + 1) + getNoiseValue(x, y - 1, z + 1) + getNoiseValue(x, y + 1, z + 1)) / 32.0f;
	result += (getNoiseValue(x - 1, y - 1, z + 1) + getNoiseValue(x + 1, y - 1, z + 1) + getNoiseValue(x - 1, y + 1, z + 1) + getNoiseValue(x + 1, y + 1, z + 1)) / 64.0f;

	return result;
}

float PerlinNoise3D::getPerlinNoiseValue(float x, float y, float z) const
{
	float floorX = floorf(x);
	float floorY = floorf(y);
	float floorZ = floorf(z);
	float fractX = x - floorX;
	float fractY = y - floorY;
	float fractZ = z - floorZ;
	float ceilX = floorX + 1.0f;
	float ceilY = floorY + 1.0f;
	float ceilZ = floorZ + 1.0f;

	float v0 = getInterpolatedValue(getSmoothNoiseValue((int32_t)floorX, (int32_t)floorY, (int32_t)floorZ), getSmoothNoiseValue((int32_t)ceilX, (int32_t)floorY, (int32_t)floorZ), fractX);
	float v1 = getInterpolatedValue(getSmoothNoiseValue((int32_t)floorX, (int32_t)ceilY, (int32_t)floorZ), getSmoothNoiseValue((int32_t)ceilX, (int32_t)ceilY, (int32_t)floorZ), fractX);

	float v01 = getInterpolatedValue(v0, v1, fractY);

	float v2 = getInterpolatedValue(getSmoothNoiseValue((int32_t)floorX, (int32_t)floorY, (int32_t)ceilZ), getSmoothNoiseValue((int32_t)ceilX, (int32_t)floorY, (int32_t)ceilZ), fractX);
	float v3 = getInterpolatedValue(getSmoothNoiseValue((int32_t)floorX, (int32_t)ceilY, (int32_t)ceilZ), getSmoothNoiseValue((int32_t)ceilX, (int32_t)ceilY, (int32_t)ceilZ), fractX);

	float v23 = getInterpolatedValue(v2, v3, fractY);

	return getInterpolatedValue(v01, v23, fractZ);
}

int32_t PerlinNoise3D::getWidth() const
{
	return width;
}

int32_t PerlinNoise3D::getHeight() const
{
	return height;
}

int32_t PerlinNoise3D::getDepth() const
{
	return depth;
}
