/*
 * Viewport.h
 *
 *  Created on: 23.04.2011
 *      Author: Norbert Nopper
 */

#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include "../../UsedLibs.h"

class Viewport
{

private:

	std::int32_t x;
	std::int32_t y;
	std::int32_t width;
	std::int32_t height;

public:

	Viewport();
	Viewport(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height);
	Viewport(const Viewport& other);
	virtual ~Viewport();

	void setViewport(std::int32_t x, std::int32_t y, std::int32_t width, std::int32_t height);

	void use() const;

	std::int32_t getX() const;
	std::int32_t getY() const;
	std::int32_t getWidth() const;
	std::int32_t getHeight() const;

};

typedef std::shared_ptr<Viewport> ViewportSP;

#endif /* VIEWPORT_H_ */
