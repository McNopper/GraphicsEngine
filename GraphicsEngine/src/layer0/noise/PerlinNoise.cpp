/*
 * PerlinNoise.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise.h"

using namespace std;

PerlinNoise::PerlinNoise(int32_t seed, float frequency, float amplitude, float persistence, int32_t octaves) :
		data(nullptr), dataSize(0), seed(seed), frequency(frequency), amplitude(amplitude), persistence(persistence), octaves(octaves)
{
}

PerlinNoise::PerlinNoise(const PerlinNoise& other) :
		data(nullptr), dataSize(0), seed(other.seed), frequency(other.frequency), amplitude(other.amplitude), persistence(other.persistence), octaves(other.octaves)
{
	data = new uint8_t[other.dataSize];

	if (!data)
	{
		return;
	}

	memcpy(data, other.data, other.dataSize * sizeof(uint8_t));

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

		data = new uint8_t[other.dataSize];

		if (!data)
		{
			return *this;
		}

		memcpy(data, other.data, other.dataSize * sizeof(uint8_t));

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

const uint8_t* PerlinNoise::getData() const
{
	return data;
}

std::int32_t PerlinNoise::getDataSize() const
{
	return dataSize;
}
