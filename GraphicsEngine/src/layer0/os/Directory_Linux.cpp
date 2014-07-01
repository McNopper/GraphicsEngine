/*
 * Directory_Linux.cpp
 *
 *  Created on: 01.07.2014
 *      Author: b48616
 */

#include <sys/stat.h>

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
	return mkdir(name.c_str(), 0777) == 0;
}
