/*
 * PerlinNoise3D.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise3D.h"

PerlinNoise3D::PerlinNoise3D(int32_t width, int32_t height, int32_t depth, int32_t seed, float frequency, float amplitude, float persistence, int32_t octaves) :
		PerlinNoise(seed, frequency, amplitude, persistence, octaves), width(width), height(height), depth(depth), data3D(nullptr)
{
	if (persistence <= 0.0f)
	{
		return;
	}

	data = new float[width * height * depth];

	if (!data)
	{
		return;
	}

	for (int32_t i = 0; i < width * height * depth; i++)
	{
		data[i] = 0.0f;
	}

	dataSize = width * height * depth;

	//

	data3D = new uint32_t[width * height * depth];

	if (!data3D)
	{
		return;
	}

	srand(seed);
	for (int32_t i = 0; i < width * height * depth; i++)
	{
		data3D[i] = static_cast<uint32_t>(rand());
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
		int32_t waveLenghtZ = depth / static_cast<int32_t>(currentFrequency);

		if (waveLenghtX < 1)
		{
			waveLenghtX = 1;
		}
		if (waveLenghtY < 1)
		{
			waveLenghtY = 1;
		}
		if (waveLenghtZ < 1)
		{
			waveLenghtZ = 1;
		}

		// Render per wavelength
		for (int32_t z = 0; z < depth; z += waveLenghtZ)
		{
			for (int32_t y = 0; y < height; y += waveLenghtY)
			{
				for (int32_t x = 0; x < width; x += waveLenghtX)
				{
					float p[8];

					int32_t xRandom = x / waveLenghtX;
					int32_t yRandom = y / waveLenghtY;
					int32_t zRandom = z / waveLenghtZ;

					// Get random values from adjacent points
					p[0] = getNoiseValue(xRandom, yRandom, zRandom, static_cast<int32_t>(currentAmplitude));
					p[1] = getNoiseValue(xRandom + 1, yRandom, zRandom, static_cast<int32_t>(currentAmplitude));
					p[2] = getNoiseValue(xRandom, yRandom + 1, zRandom, static_cast<int32_t>(currentAmplitude));
					p[3] = getNoiseValue(xRandom + 1, yRandom + 1, zRandom, static_cast<int32_t>(currentAmplitude));
					p[4] = getNoiseValue(xRandom, yRandom, zRandom + 1, static_cast<int32_t>(currentAmplitude));
					p[5] = getNoiseValue(xRandom + 1, yRandom, zRandom + 1, static_cast<int32_t>(currentAmplitude));
					p[6] = getNoiseValue(xRandom, yRandom + 1, zRandom + 1, static_cast<int32_t>(currentAmplitude));
					p[7] = getNoiseValue(xRandom + 1, yRandom + 1, zRandom + 1, static_cast<int32_t>(currentAmplitude));

					// Sample the points in the wavelength area
					for (int32_t zInner = 0; zInner < waveLenghtZ && y + zInner < depth; zInner++)
					{
						for (int32_t yInner = 0; yInner < waveLenghtY && y + yInner < height; yInner++)
						{
							for (int32_t xInner = 0; xInner < waveLenghtX && x + xInner < width; xInner++)
							{
								int32_t index = (z + zInner) * height * width + (y + yInner) * width + x + xInner;

								float x0 = getInterpolatedValue(p[0], p[1], static_cast<float>(xInner) / static_cast<float>(waveLenghtX));
								float x1 = getInterpolatedValue(p[2], p[3], static_cast<float>(xInner) / static_cast<float>(waveLenghtX));
								float x2 = getInterpolatedValue(p[4], p[5], static_cast<float>(xInner) / static_cast<float>(waveLenghtX));
								float x3 = getInterpolatedValue(p[6], p[7], static_cast<float>(xInner) / static_cast<float>(waveLenghtX));

								float y0 = getInterpolatedValue(x0, x1, static_cast<float>(yInner) / static_cast<float>(waveLenghtY));
								float y1 = getInterpolatedValue(x2, x3, static_cast<float>(yInner) / static_cast<float>(waveLenghtY));

								data[index] += getInterpolatedValue(y0, y1, static_cast<float>(zInner) / static_cast<float>(waveLenghtZ));
							}
						}
					}
				}
			}
		}

		frequencyFactor *= 2.0f;
		amplitudeFactor *= 1.0f / persistence;
	}

	delete[] data3D;
	data3D = nullptr;
}

PerlinNoise3D::~PerlinNoise3D()
{
}

float PerlinNoise3D::getNoiseValue(int32_t x, int32_t y, int32_t z, int32_t amplitude) const
{
	if (!data3D)
	{
		return 0.0f;
	}

	x = x % width;
	y = y % height;
	z = z % depth;

	if (x < 0)
	{
		x = width + x;
	}
	if (y < 0)
	{
		y = height + y;
	}
	if (z < 0)
	{
		z = depth + z;
	}

	return static_cast<float>(data3D[x + y * width + z * height * width] % amplitude);
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
