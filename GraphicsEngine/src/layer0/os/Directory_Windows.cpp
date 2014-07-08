/*
 * Directory_Windows.cpp
 *
 *  Created on: 01.07.2014
 *      Author: nopper
 */

#include <direct.h>

#include "Directory.h"

using namespace std;

Directory::Directory()
{
}

Directory::~Directory()
{
}

bool Directory::create(const string& name)
{
	return _mkdir(name.c_str()) == 0;
}
