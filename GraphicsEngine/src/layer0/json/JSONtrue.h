/*
 * JSONtrue.h
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#ifndef JSONTRUE_H_
#define JSONTRUE_H_

#include "JSONvalue.h"

class JSONtrue : public JSONvalue
{

public:

	JSONtrue();
	virtual ~JSONtrue();

};

typedef std::shared_ptr<JSONtrue> JSONtrueSP;

#endif /* JSONTRUE_H_ */
