/*
 * JSONstring.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#include "JSONstring.h"

using namespace std;

JSONstring::JSONstring(const string& value) : JSONvalue(), value(value)
{
	jsonString = true;
}

JSONstring::~JSONstring()
{
}

const std::string& JSONstring::getValue() const
{
	return value;
}

void JSONstring::setValue(const string& value)
{
	this->value = value;
}
