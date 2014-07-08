/*
 * JSONarray.h
 *
 *  Created on: Jun 16, 2014
 *      Author: nopper
 */

#ifndef JSONARRAY_H_
#define JSONARRAY_H_

#include "JSONvalue.h"

class JSONarray : public JSONvalue
{

private:

	std::vector<JSONvalueSP> allValues;

public:

	JSONarray();
	virtual ~JSONarray();

	void addValue(const JSONvalueSP& value);

	JSONvalueSP getValueAt(std::int32_t index) const;

	const std::vector<JSONvalueSP>& getAllValues() const;

	size_t size() const;

};

typedef std::shared_ptr<JSONarray> JSONarraySP;

#endif /* JSONARRAY_H_ */
