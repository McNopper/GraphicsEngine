/*
 * JSONfalse.h
 *
 *  Created on: Jun 16, 2014
 *      Author: nopper
 */

#ifndef JSONFALSE_H_
#define JSONFALSE_H_

#include "JSONvalue.h"

class JSONfalse : public JSONvalue
{

public:

	JSONfalse();
	virtual ~JSONfalse();

};

typedef std::shared_ptr<JSONfalse> JSONfalseSP;

#endif /* JSONFALSE_H_ */
