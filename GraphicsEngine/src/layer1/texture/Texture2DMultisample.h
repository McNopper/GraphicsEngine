/*
 * Texture2DMultisample.h
 *
 *  Created on: 04.02.2013
 *      Author: nopper
 */

#ifndef TEXTURE2DMULTISAMPLE_H_
#define TEXTURE2DMULTISAMPLE_H_

#include "Texture.h"

class Texture2DMultisample : public Texture
{

protected:

	std::int32_t samples;

	bool fixedsamplelocations;

	virtual void changingSize();

public:
	Texture2DMultisample(const std::string& identifier, std::int32_t samples, GLint internalFormat, std::int32_t width, std::int32_t height, bool fixedsamplelocations = false);
	virtual ~Texture2DMultisample();

	virtual bool init();

};

typedef std::shared_ptr<Texture2DMultisample> Texture2DMultisampleSP;

#endif /* TEXTURE2DMULTISAMPLE_H_ */
