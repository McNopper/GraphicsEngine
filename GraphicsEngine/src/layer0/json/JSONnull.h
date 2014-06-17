/*
 * JSONnull.h
 *
 *  Created on: Jun 16, 2014
 *      Author: B48616
 */

#ifndef JSONNULL_H_
#define JSONNULL_H_

#include "JSONvalue.h"

class JSONnull : public JSONvalue
{

public:

	JSONnull();
	virtual ~JSONnull();

};

typedef std::shared_ptr<JSONnull> JSONnullSP;

#endif /* JSONNULL_H_ */
