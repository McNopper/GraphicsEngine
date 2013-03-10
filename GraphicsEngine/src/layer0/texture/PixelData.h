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

	boost::int32_t width;
	boost::int32_t height;
	GLenum format;
	GLenum type;
	boost::uint8_t* pixels;
	boost::uint32_t sizeOfData;

public:

	PixelData();
	PixelData(boost::int32_t width, boost::int32_t height, GLenum format, GLenum type, const boost::uint8_t* pixels, boost::uint32_t sizeOfData);
	PixelData(const PixelData& other);
	~PixelData();

	PixelData& operator =(const PixelData& other);

	void setPixels(const PixelData& other);
	void freePixels();

	boost::int32_t getWidth() const;
	boost::int32_t getHeight() const;
	GLenum getFormat() const;
	GLenum getType() const;
	boost::uint8_t* getPixels() const;
	boost::uint32_t getSizeOfData() const;

};

typedef boost::shared_ptr<PixelData> PixelDataSP;

#endif /* PIXELDATA_H_ */
