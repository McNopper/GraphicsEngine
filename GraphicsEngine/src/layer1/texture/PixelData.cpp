/*
 * PixelData.cpp
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#include "PixelData.h"

using namespace std;

PixelData::PixelData() :
		width(0), height(0), format(GL_RGB), type(GL_UNSIGNED_BYTE), pixels(nullptr), sizeOfData(0)
{
}

PixelData::PixelData(int32_t width, int32_t height, GLenum format, GLenum type, const uint8_t* pixels, uint32_t sizeOfData) :
		width(width), height(height), format(format), type(type), pixels(nullptr), sizeOfData(0)
{
	if (pixels && sizeOfData > 0)
	{
		this->pixels = new uint8_t[sizeOfData];

		if (this->pixels)
		{
			memcpy(this->pixels, pixels, sizeOfData);

			this->sizeOfData = sizeOfData;
		}
	}
}

PixelData::PixelData(const PixelData& other)
{
	setPixels(other);
}

PixelData::~PixelData()
{
	freePixels();
}

PixelData& PixelData::operator =(const PixelData& other)
{
	setPixels(other);

	return *this;
}

void PixelData::setPixels(const PixelData& other)
{
	if (this != &other)
	{
		freePixels();

		width = other.width;
		height = other.height;
		format = other.format;
		type = other.type;
		if (other.sizeOfData > 0)
		{
			pixels = new uint8_t[other.sizeOfData];
			if (pixels)
			{
				memcpy(pixels, other.pixels, other.sizeOfData);

				sizeOfData = other.sizeOfData;
			}
		}
	}
}

void PixelData::freePixels()
{
	if (pixels)
	{
		delete[] pixels;

		pixels = nullptr;

		sizeOfData = 0;
	}
}

std::int32_t PixelData::getWidth() const
{
	return width;
}

std::int32_t PixelData::getHeight() const
{
	return height;
}

GLenum PixelData::getFormat() const
{
	return format;
}

GLenum PixelData::getType() const
{
	return type;
}

std::uint8_t* PixelData::getPixels() const
{
	return pixels;
}

std::uint32_t PixelData::getSizeOfData() const
{
	return sizeOfData;
}
