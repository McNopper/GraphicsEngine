/*
 * GaussFilter.cpp
 *
 *  Created on: 19.12.2012
 *      Author: nopper
 */

#include "GaussFilter.h"

using namespace std;

GaussFilter::GaussFilter(int32_t pixel, float sigma) :
		pixel(pixel), sigma(sigma), values(nullptr)
{
	if (pixel < 0)
	{
		return;
	}

	values = new float[getValuesSize()];

	if (!values)
	{
		return;
	}

	float sqrSigma = sigma*sigma;

	float x;

	float sum = 0.0f;

	for (int32_t i = -pixel; i <= pixel; i++)
	{
		x = static_cast<float>(i);

		values[i+pixel] = 1.0f/sqrtf( 2.0f*GLUS_PI*sqrSigma ) * expf( -(x*x)/(2.0f*sqrSigma) );

		sum += values[i+pixel];
	}

	// Normalize
	for (int32_t i = -pixel; i <= pixel; i++)
	{
		values[i+pixel] /= sum;
	}
}

GaussFilter::GaussFilter(const GaussFilter& other) :
	pixel(other.getPixel()), sigma(other.getSigma()), values(nullptr)
{
	values = new float[other.getValuesSize()];

	if (!values)
	{
		return;
	}

	memcpy(values, other.getValues(), other.getValuesSize() * sizeof(float));
}

GaussFilter::~GaussFilter()
{
	if (values)
	{
		delete[] values;

		values = nullptr;
	}
}

GaussFilter& GaussFilter::operator =(const GaussFilter& other)
{
	if (this != &other)
	{
		pixel = other.getPixel();
		sigma = other.getSigma();

		if (values)
		{
			delete[] values;

			values = nullptr;
		}

		values = new float[other.getValuesSize()];

		if (!values)
		{
			return *this;
		}

		memcpy(values, other.getValues(), other.getValuesSize() * sizeof(float));
	}

	return *this;
}

int32_t GaussFilter::getPixel() const
{
	return pixel;
}

float GaussFilter::getSigma() const
{
	return sigma;
}

const float* GaussFilter::getValues() const
{
	return values;
}

const void* GaussFilter::getVoidValues() const
{
	return static_cast<const void*>(values);
}

int32_t GaussFilter::getValuesSize() const
{
	return 1 + pixel*2;
}
