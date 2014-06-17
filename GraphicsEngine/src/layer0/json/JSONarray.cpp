/*
 * JSONarray.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#include "JSONarray.h"

using namespace std;

JSONarray::JSONarray() : JSONvalue(), allValues()
{
	jsonArray = true;
}

JSONarray::~JSONarray()
{
}

void JSONarray::addValue(const JSONvalueSP& value)
{
	allValues.push_back(value);
}

JSONvalueSP JSONarray::getValueAt(std::int32_t index) const
{
	return allValues.at(index);
}

const vector<JSONvalueSP>& JSONarray::getAllValues() const
{
	return allValues;
}

size_t JSONarray::size() const
{
	return allValues.size();
}
