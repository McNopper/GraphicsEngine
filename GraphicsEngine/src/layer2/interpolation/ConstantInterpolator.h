/*
 * ConstantInterpolator.h
 *
 *  Created on: 31.08.2012
 *      Author: nopper
 */

#ifndef CONSTANTINTERPOLATOR_H_
#define CONSTANTINTERPOLATOR_H_

#include "Interpolator.h"

class ConstantInterpolator : public Interpolator
{

private:

	ConstantInterpolator();
	virtual ~ConstantInterpolator();

public:

	static const ConstantInterpolator interpolator;

	virtual float interpolate(const std::map<float, float>& table, float time) const;

};

#endif /* CONSTANTINTERPOLATOR_H_ */
