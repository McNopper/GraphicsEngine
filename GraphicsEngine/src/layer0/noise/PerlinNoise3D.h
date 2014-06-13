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

		std::int32_t width;
		std::int32_t height;
		std::int32_t depth;

	public:

		PerlinNoise3D(std::int32_t width, std::int32_t height, std::int32_t depth, std::int32_t seed, float frequency, float amplitude, float persistence, std::int32_t octaves);
		virtual ~PerlinNoise3D();

		std::int32_t getWidth() const;

		std::int32_t getHeight() const;

		std::int32_t getDepth() const;

};

#endif /* PERLINNOISE3D_H_ */
