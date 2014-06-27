/*
 * LinearInterpolator.cpp
 *
 *  Created on: 31.08.2012
 *      Author: nopper
 */

#include "../../layer0/stl/Helper.h"

#include "LinearInterpolator.h"

using namespace std;

const LinearInterpolator LinearInterpolator::interpolator = LinearInterpolator();

LinearInterpolator::LinearInterpolator() :
		Interpolator("LINEAR", 1)
{
}

LinearInterpolator::~LinearInterpolator()
{
}

float LinearInterpolator::interpolate(const map<float, float>& table,
		float time) const
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

	float startTime = walker->first;
	float startValue = walker->second;

	float stopTime = startTime;
	float stopValue = startValue;

	walker++;
	if (walker != table.end())
	{
		stopTime = walker->first;
		stopValue = walker->second;
	}

	float delta = stopTime - startTime;

	if (delta == 0.0f)
	{
		return startValue;
	}

	return startValue + (stopValue - startValue) * (time - startTime) / delta;
}
