/*
 * CubicInterpolator.h
 *
 *  Created on: 31.08.2012
 *      Author: nopper
 */

#ifndef CUBICINTERPOLATOR_H_
#define CUBICINTERPOLATOR_H_

#include "Interpolator.h"

class CubicInterpolator : public Interpolator
{

private:

	CubicInterpolator();
	virtual ~CubicInterpolator();

public:

	static const CubicInterpolator interpolator;

	virtual float interpolate(const std::map<float, float>& table, float time) const;

};

#endif /* CUBICINTERPOLATOR_H_ */
