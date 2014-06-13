/*
 * Texture.h
 *
 *  Created on: 23.11.2012
 *      Author: nopper
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "../../UsedLibs.h"

class Texture
{

protected:

	std::string identifier;

	GLenum target;

	GLint internalFormat;

	std::int32_t width;
	std::int32_t height;

	GLuint textureName;

	virtual void changingSize() = 0;

public:
	Texture(const std::string& identifier, GLenum target, GLint internalFormat, std::int32_t width, std::int32_t height);
	virtual ~Texture();

	virtual bool init() = 0;
	void destroy();

	const std::string& getIdentifier() const;

	GLenum getTarget() const;

	std::int32_t getWidth() const;
	void setWidth(std::int32_t width);
	std::int32_t getHeight() const;
	void setHeight(std::int32_t height);

	void setWidthHeight(std::int32_t width, std::int32_t height);

	GLuint getTextureName() const;

	GLint getInternalFormat() const;
	void setInternalFormat(GLint internalFormat);

};

typedef std::shared_ptr<Texture> TextureSP;

#endif /* TEXTURE_H_ */
