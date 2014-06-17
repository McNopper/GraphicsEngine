/*
 * JSONobject.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#include "JSONobject.h"

using namespace std;

JSONobject::JSONobject() : JSONvalue(), allKeyValues()
{
	jsonObject = true;
}

JSONobject::~JSONobject()
{
}

void JSONobject::addKeyValue(const JSONstringSP& key, const JSONvalueSP& value)
{
	allKeyValues[key] = value;
}

bool JSONobject::hasKey(const JSONstringSP& key) const
{
	return allKeyValues.find(key) != allKeyValues.end();
}

JSONvalueSP JSONobject::getValue(const JSONstringSP& key) const
{
	return allKeyValues.at(key);
}

const map<JSONstringSP, JSONvalueSP>& JSONobject::getAllKeyValues() const
{
	return allKeyValues;
}

size_t JSONobject::size() const
{
	return allKeyValues.size();
}
