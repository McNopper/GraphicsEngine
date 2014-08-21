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

	GLUStgaimage image;

	if (!glusPerlinCreateNoise1D(&image, width, seed, frequency, amplitude, persistence, octaves))
	{
		return;
	}

	data = image.data;
	dataSize = width;
}

PerlinNoise1D::~PerlinNoise1D()
{
}

int32_t PerlinNoise1D::getWidth() const
{
	return width;
}
