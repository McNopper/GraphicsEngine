/*
 * CubicInterpolator.cpp
 *
 *  Created on: 31.08.2012
 *      Author: nopper
 */

#include "../../layer0/stl/Helper.h"
#include "LinearInterpolator.h"

#include "CubicInterpolator.h"

using namespace std;

const CubicInterpolator CubicInterpolator::interpolator = CubicInterpolator();

CubicInterpolator::CubicInterpolator() :
		Interpolator("CUBIC", 2)
{
}

CubicInterpolator::~CubicInterpolator()
{
}

/**
 * see http://paulbourke.net/miscellaneous/interpolation/
 */
float CubicInterpolator::interpolate(const map<float, float>& table, float time) const
{
	if (table.size() < 4)
	{
		return LinearInterpolator::interpolator.interpolate(table, time);
	}

	auto walker = less_equal_bound<float, float>(table, time);

	// If nothing was found, return starting value
	if (walker == table.end())
	{
		return table.begin()->second;
	}
	else if (walker == table.begin())
	{
		return LinearInterpolator::interpolator.interpolate(table, time);
	}

	float startTime = walker->first;
	float startValue = walker->second;

	walker--;
	float prevStartValue = walker->second;

	walker++;
	walker++;
	if (walker == table.end())
	{
		return startValue;
	}
	float stopTime = walker->first;
	float stopValue = walker->second;

	walker++;
	if (walker == table.end())
	{
		return LinearInterpolator::interpolator.interpolate(table, time);
	}
	float postStopValue = walker->second;

	float delta = stopTime - startTime;

	if (delta == 0.0f)
	{
		return startValue;
	}

	float x = (time - startTime) / delta;

	float a0, a1, a2, a3;

	a0 = postStopValue - stopValue - prevStartValue + startValue;
	a1 = prevStartValue - startValue - a0;
	a2 = stopValue - prevStartValue;
	a3 = startValue;

	return (a0 * x * x * x + a1 * x * x + a2 * x + a3);
}
