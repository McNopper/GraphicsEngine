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

using namespace boost;

const CubicInterpolator CubicInterpolator::interpolator = CubicInterpolator();

CubicInterpolator::CubicInterpolator() :
		Interpolator()
{
}

CubicInterpolator::~CubicInterpolator()
{
}

float CubicInterpolator::interpolate(const map<float, float>& table,
		float time) const
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
	float prevStartTime = walker->first;
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
	float postStopTime = walker->first;
	float postStopValue = walker->second;

	float delta = stopTime - startTime;

	if (delta == 0.0f)
	{
		return startValue;
	}

	float time1 = (time - startTime) / delta;
	float time2 = time1 * time1;
	float time3 = time2 * time1;

	float h00 = 2.0f * time3 - 3.0f * time2 + 1;
	float h10 = time3 - 2.0f * time2 + time1;
	float h01 = -2.0f * time3 + 3.0f * time2;
	float h11 = time3 - time2;

	float p0 = startValue;
	float p1 = stopValue;
	float m0 = (stopValue - startValue) / (2.0f * stopTime - startTime);
	if (startTime - prevStartTime != 0.0f)
	{
		m0 += (startValue - prevStartValue) / (2.0f * startTime - prevStartTime);
	}
	float m1 = (stopValue - startValue) / (2.0f * stopTime - startTime);
	if (postStopTime - stopTime != 0.0f)
	{
		m1 += (postStopValue - stopValue) / (2.0f * postStopTime - stopTime);
	}

	return h00 * p0 + h10 * delta * m0 + h01 * p1 + h11 * delta * m1;
}
