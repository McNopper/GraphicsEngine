/*
 * GlTfBufferView.h
 *
 *  Created on: 04.07.2014
 *      Author: nopper
 */

#ifndef GLTFBUFFERVIEW_H_
#define GLTFBUFFERVIEW_H_

#include "../../UsedLibs.h"

class GlTfBufferView
{

private:

	const std::uint8_t* buffer;

	std::int32_t byteOffset;

	std::int32_t byteLength;

	GLenum target;

public:

	GlTfBufferView(const std::uint8_t* buffer, std::int32_t byteOffset, std::int32_t byteLength, GLenum target);

	virtual ~GlTfBufferView();

	const std::uint8_t* getData() const;

	const std::uint8_t* getBuffer() const;
	std::int32_t getByteLength() const;
	std::int32_t getByteOffset() const;
	GLenum getTarget() const;

};

typedef std::shared_ptr<GlTfBufferView> GlTfBufferViewSP;

#endif /* GLTFBUFFERVIEW_H_ */
