/*
 * GlTfAccessor.cpp
 *
 *  Created on: 04.07.2014
 *      Author: nopper
 */

#include "GlTfAccessor.h"

using namespace std;

GlTfAccessor::GlTfAccessor(GlTfBufferViewSP bufferView, int32_t byteOffset, int32_t byteStride, GLenum componentType, int32_t count, string type) :
		bufferView(bufferView), byteOffset(byteOffset), byteStride(byteStride), componentType(componentType), count(count), type(type)
{
}

GlTfAccessor::~GlTfAccessor()
{
}

const GlTfBufferViewSP& GlTfAccessor::getBufferView() const
{
	return bufferView;
}

int32_t GlTfAccessor::getByteOffset() const
{
	return byteOffset;
}

int32_t GlTfAccessor::getByteStride() const
{
	return byteStride;
}

GLenum GlTfAccessor::getComponentType() const
{
	return componentType;
}

int32_t GlTfAccessor::getCount() const
{
	return count;
}

const string& GlTfAccessor::getType() const
{
	return type;
}

int32_t GlTfAccessor::getNumberComponents() const
{
	if (type == "SCALAR")
	{
		return 1;
	}
	else if (type == "VEC2")
	{
		return 2;
	}
	else if (type == "VEC3")
	{
		return 3;
	}
	else if (type == "VEC4")
	{
		return 4;
	}
	else if (type == "MAT2")
	{
		return 4;
	}
	else if (type == "MAT3")
	{
		return 9;
	}
	else if (type == "MAT4")
	{
		return 16;
	}

	return 0;
}

const uint8_t* GlTfAccessor::getData() const
{
	if (bufferView.get() == nullptr)
	{
		return nullptr;
	}

	return &bufferView->getData()[byteOffset];
}
