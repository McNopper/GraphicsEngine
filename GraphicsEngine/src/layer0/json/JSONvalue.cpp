/*
 * JSONvalue.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#include "JSONvalue.h"

using namespace std;

JSONvalue::JSONvalue() :
jsonObject(false), jsonArray(false), jsonNumber(false), jsonString(false), jsonTrue(false), jsonFalse(false), jsonNull(false)
{
}

JSONvalue::~JSONvalue()
{
}

bool JSONvalue::isJsonObject() const
{
	return jsonObject;
}

bool JSONvalue::isJsonArray() const
{
	return jsonArray;
}

bool JSONvalue::isJsonNumber() const
{
	return jsonNumber;
}

bool JSONvalue::isJsonString() const
{
	return jsonString;
}

bool JSONvalue::isJsonTrue() const
{
	return jsonTrue;
}

bool JSONvalue::isJsonFalse() const
{
	return jsonFalse;
}

bool JSONvalue::isJsonNull() const
{
	return jsonNull;
}
