/*
 * Shape.cpp
 *
 *  Created on: 09.11.2012
 *      Author: nopper
 */

#include "Shape.h"

Shape::Shape()
{
	memset(&shape, 0, sizeof(GLUSshape));
}

Shape::Shape(const GLUSshape& shape) : shape(shape)
{
}

Shape::~Shape()
{
	glusShapeDestroyf(&shape);
}

Shape& Shape::operator =(const Shape& other)
{
	if (this == &other)
	{
		return *this;
	}

	glusShapeDestroyf(&shape);

	glusShapeCopyf(&shape, &other.shape);

	return *this;
}

const GLUSshape& Shape::getShape() const
{
	return shape;
}
