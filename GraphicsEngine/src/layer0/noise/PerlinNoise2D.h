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

		std::int32_t width;
		std::int32_t height;

	public:

		PerlinNoise2D(std::int32_t width, std::int32_t height, std::int32_t seed, float frequency, float amplitude, float persistence, std::int32_t octaves);
		virtual ~PerlinNoise2D();

		std::int32_t getWidth() const;

		std::int32_t getHeight() const;

};

#endif /* PERLINNOISE2D_H_ */
