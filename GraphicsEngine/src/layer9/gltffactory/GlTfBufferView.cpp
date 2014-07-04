/*
 * GlTfBufferView.cpp
 *
 *  Created on: 04.07.2014
 *      Author: nopper
 */

#include "GlTfBufferView.h"

using namespace std;

GlTfBufferView::GlTfBufferView(const uint8_t* buffer, int32_t byteOffset, int32_t byteLength, GLenum target) :
		buffer(buffer), byteOffset(byteOffset), byteLength(byteLength), target(target)
{
}

GlTfBufferView::~GlTfBufferView()
{
}

const uint8_t* GlTfBufferView::getData() const
{
	return &buffer[byteOffset];
}

const uint8_t* GlTfBufferView::getBuffer() const
{
	return buffer;
}

int32_t GlTfBufferView::getByteLength() const
{
	return byteLength;
}

int32_t GlTfBufferView::getByteOffset() const
{
	return byteOffset;
}

GLenum GlTfBufferView::getTarget() const
{
	return target;
}
