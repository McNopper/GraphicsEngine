/*
 * GaussFilter.h
 *
 *  Created on: 19.12.2012
 *      Author: nopper
 */

#ifndef GAUSSFILTER_H_
#define GAUSSFILTER_H_

#include "../../UsedLibs.h"

class GaussFilter
{

private:

	std::int32_t pixel;

	float sigma;

	float* values;

public:
	GaussFilter(std::int32_t pixel, float sigma);
	GaussFilter(const GaussFilter& other);
	virtual ~GaussFilter();

	GaussFilter& operator =(const GaussFilter& other);

	std::int32_t getPixel() const;

	float getSigma() const;

	const float* getValues() const;

	const void* getVoidValues() const;

	std::int32_t getValuesSize() const;

};

#endif /* GAUSSFILTER_H_ */
