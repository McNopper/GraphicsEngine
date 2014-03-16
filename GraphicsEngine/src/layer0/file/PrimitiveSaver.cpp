/*
 * PrimitiveSaver.cpp
 *
 *  Created on: 13.03.2014
 *      Author: nopper
 */

#include "PrimitiveSaver.h"

using namespace boost;

bool PrimitiveSaver::saveBool(FILE* f, bool value)
{
	if (!f)
	{
		return false;
	}

	if (fprintf(f, "%s\n\n", (value ? "true" : "false")) < 0)
	{
		return false;
	}

	return true;
}

bool PrimitiveSaver::saveFloat(FILE* f, float value)
{
	if (!f)
	{
		return false;
	}

	if (fprintf(f, "%f\n\n", value) < 0)
	{
		return false;
	}

	return true;
}

bool PrimitiveSaver::saveInt(FILE* f, int32_t value)
{
	if (!f)
	{
		return false;
	}

	if (fprintf(f, "%d\n\n", value) < 0)
	{
		return false;
	}

	return true;
}

bool PrimitiveSaver::saveUInt(FILE* f, uint32_t value)
{
	if (!f)
	{
		return false;
	}

	if (fprintf(f, "%u\n\n", value) < 0)
	{
		return false;
	}

	return true;
}

bool PrimitiveSaver::saveChar(FILE* f, char value)
{
	if (!f)
	{
		return false;
	}

	if (fprintf(f, "%c\n\n", value) < 0)
	{
		return false;
	}

	return true;
}

bool PrimitiveSaver::saveString(FILE* f, const char* value)
{
	if (!f || !value)
	{
		return false;
	}

	if (fprintf(f, "%s\n\n", value) < 0)
	{
		return false;
	}

	return true;
}
