/*
 * LinearInterpolator.h
 *
 *  Created on: 31.08.2012
 *      Author: nopper
 */

#ifndef LINEARINTERPOLATOR_H_
#define LINEARINTERPOLATOR_H_

#include "Interpolator.h"

class LinearInterpolator : public Interpolator
{

private:

	LinearInterpolator();

	virtual ~LinearInterpolator();

public:

	static const LinearInterpolator interpolator;

	virtual float interpolate(const std::map<float, float>& table, float time) const;

};

#endif /* LINEARINTERPOLATOR_H_ */
