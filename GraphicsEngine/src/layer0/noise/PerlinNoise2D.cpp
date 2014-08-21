/*
 * PerlinNoise2D.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise2D.h"

using namespace std;

PerlinNoise2D::PerlinNoise2D(int32_t width, int32_t height, int32_t seed, float frequency, float amplitude, float persistence, int32_t octaves) :
		PerlinNoise(seed, frequency, amplitude, persistence, octaves), width(width), height(height)
{
	if (persistence <= 0.0f)
	{
		return;
	}

	GLUStgaimage image;

	if (!glusPerlinCreateNoise2D(&image, width, height, seed, frequency, amplitude, persistence, octaves))
	{
		return;
	}

	data = image.data;
	dataSize = width * height;
}

PerlinNoise2D::~PerlinNoise2D()
{
}

int32_t PerlinNoise2D::getWidth() const
{
	return width;
}

int32_t PerlinNoise2D::getHeight() const
{
	return height;
}
