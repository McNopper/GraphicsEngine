/*
 * PerlinNoise2D.h
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#ifndef PERLINNOISE2D_H_
#define PERLINNOISE2D_H_

#include "PerlinNoise.h"

class PerlinNoise2D : public PerlinNoise
{
	private:

		boost::int32_t width;
		boost::int32_t height;

	public:

		PerlinNoise2D(boost::int32_t width, boost::int32_t height, boost::int32_t seed, float frequency, float amplitude, float persistence, boost::int32_t octaves);
		virtual ~PerlinNoise2D();

		boost::int32_t getWidth() const;

		boost::int32_t getHeight() const;

};

#endif /* PERLINNOISE2D_H_ */
