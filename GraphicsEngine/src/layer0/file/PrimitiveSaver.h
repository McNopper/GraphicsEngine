/*
 * PrimitiveSaver.h
 *
 *  Created on: 13.03.2014
 *      Author: nopper
 */

#ifndef PRIMITIVESAVER_H_
#define PRIMITIVESAVER_H_

#include "../../UsedLibs.h"

class PrimitiveSaver
{

	static bool saveBool(FILE* f, bool value);

	static bool saveFloat(FILE* f, float value);

	static bool saveInt(FILE* f, boost::int32_t value);

	static bool saveUInt(FILE* f, boost::uint32_t value);

	static bool saveChar(FILE* f, char value);

	static bool saveString(FILE* f, const char* value);

};

#endif /* PRIMITIVESAVER_H_ */
