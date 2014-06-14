/*
 * PixelData.h
 *
 *  Created on: 06.03.2013
 *      Author: nopper
 */

#ifndef PIXELDATA_H_
#define PIXELDATA_H_

#include "../../UsedLibs.h"

class PixelData
{

private:

	std::int32_t width;
	std::int32_t height;
	GLenum format;
	GLenum type;
	std::uint8_t* pixels;
	std::uint32_t sizeOfData;

public:

	PixelData();
	PixelData(std::int32_t width, std::int32_t height, GLenum format, GLenum type, const std::uint8_t* pixels, std::uint32_t sizeOfData);
	PixelData(const PixelData& other);
	~PixelData();

	PixelData& operator =(const PixelData& other);

	void setPixels(const PixelData& other);
	void freePixels();

	std::int32_t getWidth() const;
	std::int32_t getHeight() const;
	GLenum getFormat() const;
	GLenum getType() const;
	std::uint8_t* getPixels() const;
	std::uint32_t getSizeOfData() const;

};

typedef std::shared_ptr<PixelData> PixelDataSP;

// C++11 Lambda function macro for deleting arrays.
#define DELETE_ARRAY_PixelDataSP [](PixelData* p) {delete[] p;}

#endif /* PIXELDATA_H_ */
