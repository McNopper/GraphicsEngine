/*
 * PerlinNoise3D.cpp
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#include "PerlinNoise3D.h"

PerlinNoise3D::PerlinNoise3D(int32_t width, int32_t height, int32_t depth, int32_t seed, float frequency, float amplitude, float persistence, int32_t octaves) :
		PerlinNoise(seed, frequency, amplitude, persistence, octaves), width(width), height(height), depth(depth)
{
	if (persistence <= 0.0f)
	{
		return;
	}

	GLUStgaimage image;

	if (!glusPerlinCreateNoise3D(&image, width, height, depth, seed, frequency, amplitude, persistence, octaves))
	{
		return;
	}

	data = image.data;
	dataSize = width * height * depth;
}

PerlinNoise3D::~PerlinNoise3D()
{
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
