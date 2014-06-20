/*
 * JSONnumber.h
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#ifndef JSONNUMBER_H_
#define JSONNUMBER_H_

#include "JSONvalue.h"

class JSONnumber : public JSONvalue
{

private:

	bool isFloat;

	union Value
	{
		float floatValue;
		std::int32_t integerValue;
	} value;

public:

	JSONnumber();
	JSONnumber(const std::string& value, bool isFloat);
	JSONnumber(float value);
	JSONnumber(std::int32_t value);
	virtual ~JSONnumber();

	float getFloatValue() const;
	void setFloatValue(float value);

	std::int32_t getIntegerValue() const;
	void setIntegerValue(std::int32_t integerValue);

	bool isFloatValue() const;

};

typedef std::shared_ptr<JSONnumber> JSONnumberSP;

#endif /* JSONNUMBER_H_ */
