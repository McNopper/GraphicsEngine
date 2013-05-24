/*
 * PerlinNoise.h
 *
 *  Created on: 17.04.2013
 *      Author: nopper
 */

#ifndef PERLINNOISE_H_
#define PERLINNOISE_H_

#include "../../UsedLibs.h"

class PerlinNoise
{
	protected:

		boost::uint8_t* data;
		boost::int32_t dataSize;

		boost::int32_t seed;

		float frequency;

		float amplitude;

		float persistence;

		boost::int32_t octaves;

	public:

		PerlinNoise(boost::int32_t seed, float frequency, float amplitude, float persistence, boost::int32_t octaves);
		PerlinNoise(const PerlinNoise& other);
		virtual ~PerlinNoise();

		PerlinNoise& operator = (const PerlinNoise& other);

		void freeData();

		const boost::uint8_t* getData() const;

		boost::int32_t getDataSize() const;

};

#endif /* PERLINNOISE_H_ */
