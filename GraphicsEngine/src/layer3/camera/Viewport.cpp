/*
 * Viewport.cpp
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#include "Viewport.h"

using namespace std;

Viewport::Viewport()
{
	setViewport(0, 0, 1, 1);
}

Viewport::Viewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	setViewport(x, y, width, height);
}

Viewport::Viewport(const Viewport& other)
{
	setViewport(other.getX(), other.getY(), other.getWidth(), other.getHeight());
}

Viewport::~Viewport()
{
}

void Viewport::setViewport(int32_t x, int32_t y, int32_t width, int32_t height)
{
	if (width < 1)
	{
		width = 1;
	}

	if (height < 1)
	{
		height = 1;
	}

	this->x = x;
	this->y = x;
	this->width = width;
	this->height = height;
}

void Viewport::use() const
{
	glViewport(x, y, width, height);
}

int32_t Viewport::getX() const
{
    return x;
}

int32_t Viewport::getY() const
{
    return y;
}

int32_t Viewport::getWidth() const
{
    return width;
}

int32_t Viewport::getHeight() const
{
    return height;
}
