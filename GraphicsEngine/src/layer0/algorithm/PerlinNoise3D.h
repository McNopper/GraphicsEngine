/*
 * PerlinNoise3D.h
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#ifndef PERLINNOISE3D_H_
#define PERLINNOISE3D_H_

#include "PerlinNoise.h"

class PerlinNoise3D : public PerlinNoise
{

	private:

		boost::int32_t width;
		boost::int32_t height;
		boost::int32_t depth;

		boost::uint32_t* data3D;

		float getNoiseValue(boost::int32_t x, boost::int32_t y, boost::int32_t z, boost::int32_t amplitude) const;

	public:

		PerlinNoise3D(boost::int32_t width, boost::int32_t height, boost::int32_t depth, boost::int32_t seed, float frequency, float amplitude, float persistence, boost::int32_t octaves);
		virtual ~PerlinNoise3D();

		boost::int32_t getWidth() const;

		boost::int32_t getHeight() const;

		boost::int32_t getDepth() const;

};

#endif /* PERLINNOISE3D_H_ */
