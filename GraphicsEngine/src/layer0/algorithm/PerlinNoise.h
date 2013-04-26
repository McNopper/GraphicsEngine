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

		float* data;
		boost::int32_t dataSize;

		boost::int32_t seed;

		float frequency;

		float amplitude;

		float persistence;

		boost::int32_t octaves;

		float getInterpolatedValue(float value0, float value1, float t) const;

	public:

		PerlinNoise(boost::int32_t seed, float frequency, float amplitude, float persistence, boost::int32_t octaves);
		PerlinNoise(const PerlinNoise& other);
		virtual ~PerlinNoise();

		PerlinNoise& operator = (const PerlinNoise& other);

		void freeData();

		const float* getData() const;

		boost::int32_t getDataSize() const;

};

#endif /* PERLINNOISE_H_ */
