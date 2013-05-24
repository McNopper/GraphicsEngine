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

	boost::int32_t pixel;

	float sigma;

	float* values;

public:
	GaussFilter(boost::int32_t pixel, float sigma);
	GaussFilter(const GaussFilter& other);
	virtual ~GaussFilter();

	GaussFilter& operator =(const GaussFilter& other);

	boost::int32_t getPixel() const;

	float getSigma() const;

	const float* getValues() const;

	const void* getVoidValues() const;

	boost::int32_t getValuesSize() const;

};

#endif /* GAUSSFILTER_H_ */
