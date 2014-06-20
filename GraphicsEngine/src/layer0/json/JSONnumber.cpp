/*
 * JSONnumber.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#include "JSONnumber.h"

using namespace std;

JSONnumber::JSONnumber() : JSONvalue(), isFloat(true)
{
	assert(sizeof(float) == sizeof(int32_t));

	jsonNumber = true;

	this->value.floatValue = 0.0f;
}

JSONnumber::JSONnumber(const string& value, bool isFloat) : JSONvalue(), isFloat(isFloat)
{
	assert(sizeof(float) == sizeof(int32_t));

	jsonNumber = true;

	if (isFloat)
	{
		this->value.floatValue = static_cast<float>(atof(value.c_str()));
	}
	else
	{
		this->value.integerValue = atoi(value.c_str());
	}
}

JSONnumber::JSONnumber(float value) : JSONvalue(), isFloat(true)
{
	assert(sizeof(float) == sizeof(int32_t));

	jsonNumber = true;

	this->value.floatValue = value;
}

JSONnumber::JSONnumber(int32_t value) : JSONvalue(), isFloat(false)
{
	assert(sizeof(float) == sizeof(int32_t));

	jsonNumber = true;

	this->value.integerValue = value;
}

JSONnumber::~JSONnumber()
{
}

float JSONnumber::getFloatValue() const
{
	if (!isFloatValue())
	{
		return static_cast<float>(value.integerValue);
	}

	return value.floatValue;
}

void JSONnumber::setFloatValue(float value)
{
	isFloat = true;

	this->value.floatValue = value;
}

int32_t JSONnumber::getIntegerValue() const
{
	if (isFloatValue())
	{
		return static_cast<int32_t>(value.floatValue);
	}

	return value.integerValue;
}

void JSONnumber::setIntegerValue(int32_t value)
{
	isFloat = false;

	this->value.integerValue = value;
}

bool JSONnumber::isFloatValue() const
{
	return isFloat;
}
