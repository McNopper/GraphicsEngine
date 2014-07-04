/*
 * GlTfAccessor.h
 *
 *  Created on: 04.07.2014
 *      Author: nopper
 */

#ifndef GLTFACCESSOR_H_
#define GLTFACCESSOR_H_

#include "../../UsedLibs.h"

#include "GlTfBufferView.h"

class GlTfAccessor
{

private:

	GlTfBufferViewSP bufferView;
	std::int32_t byteOffset;
	std::int32_t byteStride;
	GLenum componentType;
	std::int32_t count;
	std::string type;

public:

	GlTfAccessor(GlTfBufferViewSP bufferView, std::int32_t byteOffset, std::int32_t byteStride, GLenum componentType, std::int32_t count, std::string type);
	virtual ~GlTfAccessor();

	const GlTfBufferViewSP& getBufferView() const;
	std::int32_t getByteOffset() const;
	std::int32_t getByteStride() const;
	GLenum getComponentType() const;
	std::int32_t getCount() const;
	const std::string& getType() const;

	std::int32_t getNumberComponents() const;

	const std::uint8_t* getData() const;

};

typedef std::shared_ptr<GlTfAccessor> GlTfAccessorSP;

#endif /* GLTFACCESSOR_H_ */
