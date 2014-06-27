/*
 * ConstantInterpolator.cpp
 *
 *  Created on: 31.08.2012
 *      Author: nopper
 */

#include "../../layer0/stl/Helper.h"

#include "ConstantInterpolator.h"

using namespace std;

const ConstantInterpolator ConstantInterpolator::interpolator = ConstantInterpolator();

ConstantInterpolator::ConstantInterpolator() :
		Interpolator("CONSTANT", 0)
{
}

ConstantInterpolator::~ConstantInterpolator()
{
}

float ConstantInterpolator::interpolate(const map<float, float>& table, float time) const
{
	if (table.size() == 0)
	{
		return 0.0f;
	}

	auto walker = less_equal_bound<float, float>(table, time);

	if (walker == table.end())
	{
		return table.begin()->second;
	}

	return walker->second;
}
