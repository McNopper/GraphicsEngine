/*
 * GlTfBin.cpp
 *
 *  Created on: 21.06.2014
 *      Author: nopper
 */

#include "GlTfBin.h"

using namespace std;

GlTfBin::GlTfBin() : data(), counter(0)
{
}

GlTfBin::~GlTfBin()
{
}

void GlTfBin::addData(const std::uint8_t* data, const size_t length)
{
	for (size_t i = 0; i < length; i++)
	{
		this->data.push_back(data[i]);
	}

	counter++;
}

size_t GlTfBin::getLength() const
{
	return data.size();
}

size_t GlTfBin::getCounter() const
{
	return counter;
}

const uint8_t* GlTfBin::getData() const
{
	return &data[0];
}

void GlTfBin::reset()
{
	data.clear();

	counter = 0;
}
