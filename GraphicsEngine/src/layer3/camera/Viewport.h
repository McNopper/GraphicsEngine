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

	boost::int32_t x;
	boost::int32_t y;
	boost::int32_t width;
	boost::int32_t height;

public:

	Viewport();
	Viewport(boost::int32_t x, boost::int32_t y, boost::int32_t width, boost::int32_t height);
	Viewport(const Viewport& other);
	virtual ~Viewport();

	void setViewport(boost::int32_t x, boost::int32_t y, boost::int32_t width, boost::int32_t height);

	void use() const;

	boost::int32_t getX() const;
	boost::int32_t getY() const;
	boost::int32_t getWidth() const;
	boost::int32_t getHeight() const;

};

typedef boost::shared_ptr<Viewport> ViewportSP;

#endif /* VIEWPORT_H_ */
