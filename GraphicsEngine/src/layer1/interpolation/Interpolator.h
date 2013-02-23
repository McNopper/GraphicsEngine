/*
 * Interpolator.h
 *
 *  Created on: 31.08.2012
 *      Author: nopper
 */

#ifndef INTERPOLATOR_H_
#define INTERPOLATOR_H_

#include "../../UsedLibs.h"

class Interpolator
{

protected:

	Interpolator()
	{

	}

	virtual ~Interpolator()
	{

	}

public:

	virtual float interpolate(const std::map<float, float>& table, float time) const = 0;

};

#endif /* INTERPOLATOR_H_ */
