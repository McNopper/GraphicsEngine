/*
 * JSONobject.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#include "JSONobject.h"

using namespace std;

JSONobject::JSONobject() : JSONvalue(), allKeyValues(), allKeys()
{
	jsonObject = true;
}

JSONobject::~JSONobject()
{
}

void JSONobject::addKeyValue(const JSONstringSP& key, const JSONvalueSP& value)
{
	allKeyValues[key] = value;
	allKeys.push_back(key);
}

bool JSONobject::hasKey(const JSONstringSP& key) const
{
	return allKeyValues.find(key) != allKeyValues.end();
}

JSONvalueSP JSONobject::getValue(const JSONstringSP& key) const
{
	return allKeyValues.at(key);
}

const map<JSONstringSP, JSONvalueSP, CompareJSONstringSP>& JSONobject::getAllKeyValues() const
{
	return allKeyValues;
}

const vector<JSONstringSP>& JSONobject::getAllKeys() const
{
	return allKeys;
}

size_t JSONobject::size() const
{
	return allKeyValues.size();
}
